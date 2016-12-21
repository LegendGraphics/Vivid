//#ifndef SCRIPTING_LUA_UTILS_H
//#define SCRIPTING_LUA_UTILS_H
//
//extern "C" 
//{
//#include "luaconf.h"
//#include "lua.h"
//#include "lauxlib.h"
//#include "lualib.h"
//}
//
//#include "tolua++.h"
//
//// global variable lua_state
//extern lua_State* L;
//
//extern int tolua_tiny_engine_open(lua_State* tolua_S);
//
//// print info
//extern void tableDump(lua_State* L);
//
//extern void stackDump (lua_State* L); 
//
//extern void errorTrace(lua_State* L, char *msg);
//
//
//// init and update by script
//extern void lua_init(lua_State* L);
//
//extern void lua_update(lua_State* L);
//
//extern void updateScriptLogic();
//
//
//// for lua callback binding
//#define TOLUA_REFID_FUNCTION_MAPPING "toluafix_refid_function_mapping"
//
//extern int toluafix_ref_function(lua_State* L, int lo, int def);
//
//extern void toluafix_get_function_by_refid(lua_State* L, int refid);
//
//extern bool toluafix_push_function_by_handler(lua_State* L, int callback_handler);
//
//extern int toluafix_execute_function_by_handler(lua_State* L, int callback_handler, int nargs);
//
//extern int toluafix_execute_function(lua_State* L, int nargs);
//
//extern void toluafix_open(lua_State* L);
//
//extern int toluafix_isfunction(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
//
//#endif // SCRIPTING_LUA_UTILS_H