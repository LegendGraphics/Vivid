
#include "scripting/lua_utils.h"
#include "base/director.h"


lua_State* L = luaL_newstate();

static int s_function_ref_id = 0;

void tableDump(lua_State *L)
{
    lua_pushnil(L);  
    while(lua_next(L, -2))  
    {    
        lua_pop(L, 1);
    }
}

void stackDump (lua_State *L)
{
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {

          case LUA_TSTRING:  /* strings */
              printf("`%s'", lua_tostring(L, i));
              break;

          case LUA_TBOOLEAN:  /* booleans */
              printf(lua_toboolean(L, i) ? "true" : "false");
              break;

          case LUA_TNUMBER:  /* numbers */
              printf("%g", lua_tonumber(L, i));
              break;

          default:  /* other values */
              printf("%s", lua_typename(L, t));
              break;

        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}

void errorTrace(lua_State *L, char *msg)
{
    fprintf(stderr, "\nFATAL ERROR:\n  %s: %s\n\n",
        msg, lua_tostring(L, -1));
}

void lua_init(lua_State* L)
{
    lua_getglobal(L, "init");
    lua_call(L, 0, 0);
}

void lua_update(lua_State* L)
{
    lua_getglobal(L, "update");
    lua_call(L, 0, 0);
}

void updateScriptLogic()
{
    lua_update(L);
}

void toluafix_get_function_by_refid(lua_State* L, int refid)
{
    lua_pushstring(L, TOLUA_REFID_FUNCTION_MAPPING);
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: ... refid_fun */
    lua_pushinteger(L, refid);                                  /* stack: ... refid_fun refid */
    lua_rawget(L, -2);                                          /* stack: ... refid_fun fun */
    lua_remove(L, -2);                                          /* stack: ... fun */
}


int toluafix_ref_function(lua_State* L, int lo, int def)
{
    // function at lo
    if (!lua_isfunction(L, lo)) return 0;

    s_function_ref_id++;

    lua_pushstring(L, TOLUA_REFID_FUNCTION_MAPPING);
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: fun ... refid_fun */
    lua_pushinteger(L, s_function_ref_id);                      /* stack: fun ... refid_fun refid */
    lua_pushvalue(L, lo);                                       /* stack: fun ... refid_fun refid fun */

    lua_rawset(L, -3);                  /* refid_fun[refid] = fun, stack: fun ... refid_ptr */
    lua_pop(L, 1);                                              /* stack: fun ... */

    return s_function_ref_id;
}

bool toluafix_push_function_by_handler(lua_State* L, int callback_handler)
{
    toluafix_get_function_by_refid(L, callback_handler);                  /* L: ... func */
    if (!lua_isfunction(L, -1))
    {
        TE_LOG("[LUA ERROR] function refid '%d' does not reference a Lua function", callback_handler);
        lua_pop(L, 1);
        return false;
    }
    return true;
}

int toluafix_execute_function_by_handler(lua_State* L, int callback_handler, int nargs)
{
    int ret = 0;
    if (toluafix_push_function_by_handler(L, callback_handler))                                /* L: ... arg1 arg2 ... func */
    {
        if (nargs > 0)
        {
            lua_insert(L, -(nargs + 1));                        /* L: ... func arg1 arg2 ... */
        }
        ret = toluafix_execute_function(L, nargs);
    }
    lua_settop(L, 0);
    return ret;
}

int toluafix_execute_function(lua_State* L, int nargs)
{
    int functionIndex = -(nargs + 1);
    if (!lua_isfunction(L, functionIndex))
    {
        TE_LOG("value at stack [%d] is not function", functionIndex);
        lua_pop(L, nargs + 1); // remove function and arguments
        return 0;
    }

    int traceback = 0;
    lua_getglobal(L, "__G__TRACKBACK__");                         /* L: ... func arg1 arg2 ... G */
    if (!lua_isfunction(L, -1))
    {
        lua_pop(L, 1);                                            /* L: ... func arg1 arg2 ... */
    }
    else
    {
        lua_insert(L, functionIndex - 1);                         /* L: ... G func arg1 arg2 ... */
        traceback = functionIndex - 1;
    }

    int error = 0;
    //++m_callFromLua;
    error = lua_pcall(L, nargs, 1, traceback);                  /* L: ... [G] ret */
    //--m_callFromLua;
    if (error)
    {
        if (traceback == 0)
        {
            TE_LOG("[LUA ERROR] %s", lua_tostring(L, - 1));        /* L: ... error */
            lua_pop(L, 1); // remove error message from stack
        }
        else                                                            /* L: ... G error */
        {
            lua_pop(L, 2); // remove __G__TRACKBACK__ and error message from stack
        }
        return 0;
    }

    // get return value
    int ret = 0;
    if (lua_isnumber(L, -1))
    {
        ret = lua_tointeger(L, -1);
    }
    else if (lua_isboolean(L, -1))
    {
        ret = lua_toboolean(L, -1);
    }
    // remove return value from stack
    lua_pop(L, 1);                                                /* L: ... [G] */

    if (traceback)
    {
        lua_pop(L, 1); // remove __G__TRACKBACK__ from stack      /* L: ... */
    }

    return ret;
}

void toluafix_open(lua_State* L)
{
    lua_pushstring(L, TOLUA_REFID_FUNCTION_MAPPING);
    lua_newtable(L);
    lua_rawset(L, LUA_REGISTRYINDEX);
}

int toluafix_isfunction(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
    if (lua_gettop(L) >= abs(lo) && lua_isfunction(L, lo))
    {
        return 1;
    }
    err->index = lo;
    err->array = 0;
    err->type = "[not function]";
    return 0;
}