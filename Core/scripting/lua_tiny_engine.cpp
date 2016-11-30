/*
** Lua binding: tiny_engine
** Generated automatically by tolua++-1.0.92 on 11/04/16 15:09:11.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_tiny_engine_open (lua_State* tolua_S);

#include "lua_tiny_engine.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_UIImage (lua_State* tolua_S)
{
 UIImage* self = (UIImage*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Scene (lua_State* tolua_S)
{
 Scene* self = (Scene*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Animation (lua_State* tolua_S)
{
 Animation* self = (Animation*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIWidget (lua_State* tolua_S)
{
 UIWidget* self = (UIWidget*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Event (lua_State* tolua_S)
{
 Event* self = (Event*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIButton (lua_State* tolua_S)
{
 UIButton* self = (UIButton*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Sprite (lua_State* tolua_S)
{
 Sprite* self = (Sprite*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Camera (lua_State* tolua_S)
{
 Camera* self = (Camera*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_MouseEvent (lua_State* tolua_S)
{
 MouseEvent* self = (MouseEvent*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIPanel (lua_State* tolua_S)
{
 UIPanel* self = (UIPanel*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_EventListener (lua_State* tolua_S)
{
 EventListener* self = (EventListener*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Vec2 (lua_State* tolua_S)
{
 Vec2* self = (Vec2*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Size (lua_State* tolua_S)
{
 Size* self = (Size*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"UIImage");
 tolua_usertype(tolua_S,"Transform");
 tolua_usertype(tolua_S,"NodeVisitor");
 tolua_usertype(tolua_S,"UIWidget");
 tolua_usertype(tolua_S,"Camera::ViewBoundary");
 tolua_usertype(tolua_S,"Image");
 tolua_usertype(tolua_S,"Scheduler");
 tolua_usertype(tolua_S,"Renderer");
 tolua_usertype(tolua_S,"LUA_CALLBACK");
 tolua_usertype(tolua_S,"Node");
 tolua_usertype(tolua_S,"Size");
 tolua_usertype(tolua_S,"Director");
 tolua_usertype(tolua_S,"Scene");
 tolua_usertype(tolua_S,"Animation");
 tolua_usertype(tolua_S,"Event");
 tolua_usertype(tolua_S,"UIButton");
 tolua_usertype(tolua_S,"EventDispatcher");
 tolua_usertype(tolua_S,"Camera");
 tolua_usertype(tolua_S,"MouseEvent");
 tolua_usertype(tolua_S,"EventListener");
 tolua_usertype(tolua_S,"UIPanel");
 tolua_usertype(tolua_S,"Ref");
 tolua_usertype(tolua_S,"Vec2");
 tolua_usertype(tolua_S,"Sprite");
}

/* method: getInstance of class  Director */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Director_getInstance00
static int tolua_tiny_engine_Director_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Director",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Director* tolua_ret = (Director*)  Director::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Director");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWindowSize of class  Director */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Director_setWindowSize00
static int tolua_tiny_engine_Director_setWindowSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Director",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Director* self = (Director*)  tolua_tousertype(tolua_S,1,0);
  float window_width = ((float)  tolua_tonumber(tolua_S,2,0));
  float window_height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWindowSize'", NULL);
#endif
  {
   self->setWindowSize(window_width,window_height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWindowSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWindowSize of class  Director */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Director_getWindowSize00
static int tolua_tiny_engine_Director_getWindowSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Director",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Director* self = (const Director*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWindowSize'", NULL);
#endif
  {
   const Size& tolua_ret = (const Size&)  self->getWindowSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Size");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWindowSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActiveScene of class  Director */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Director_setActiveScene00
static int tolua_tiny_engine_Director_setActiveScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Director",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Director* self = (Director*)  tolua_tousertype(tolua_S,1,0);
  Scene* active_scene = ((Scene*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActiveScene'", NULL);
#endif
  {
   self->setActiveScene(active_scene);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActiveScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActiveScene of class  Director */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Director_getActiveScene00
static int tolua_tiny_engine_Director_getActiveScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Director",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Director* self = (Director*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActiveScene'", NULL);
#endif
  {
   Scene* tolua_ret = (Scene*)  self->getActiveScene();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Scene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActiveScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScheduler of class  Director */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Director_getScheduler00
static int tolua_tiny_engine_Director_getScheduler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Director",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Director* self = (Director*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScheduler'", NULL);
#endif
  {
   Scheduler* tolua_ret = (Scheduler*)  self->getScheduler();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Scheduler");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScheduler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEventDispatcher of class  Director */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Director_getEventDispatcher00
static int tolua_tiny_engine_Director_getEventDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Director",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Director* self = (Director*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEventDispatcher'", NULL);
#endif
  {
   EventDispatcher* tolua_ret = (EventDispatcher*)  self->getEventDispatcher();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"EventDispatcher");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEventDispatcher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDeltaTime of class  Director */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Director_getDeltaTime00
static int tolua_tiny_engine_Director_getDeltaTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Director",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Director* self = (const Director*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDeltaTime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getDeltaTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDeltaTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: start of class  Director */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Director_start00
static int tolua_tiny_engine_Director_start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Director",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Director* self = (Director*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'start'", NULL);
#endif
  {
   self->start();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: left of class  ViewBoundary */
#ifndef TOLUA_DISABLE_tolua_get_Camera__ViewBoundary_left
static int tolua_get_Camera__ViewBoundary_left(lua_State* tolua_S)
{
  Camera::ViewBoundary* self = (Camera::ViewBoundary*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'left'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->left);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: left of class  ViewBoundary */
#ifndef TOLUA_DISABLE_tolua_set_Camera__ViewBoundary_left
static int tolua_set_Camera__ViewBoundary_left(lua_State* tolua_S)
{
  Camera::ViewBoundary* self = (Camera::ViewBoundary*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'left'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->left = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: right of class  ViewBoundary */
#ifndef TOLUA_DISABLE_tolua_get_Camera__ViewBoundary_right
static int tolua_get_Camera__ViewBoundary_right(lua_State* tolua_S)
{
  Camera::ViewBoundary* self = (Camera::ViewBoundary*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'right'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->right);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: right of class  ViewBoundary */
#ifndef TOLUA_DISABLE_tolua_set_Camera__ViewBoundary_right
static int tolua_set_Camera__ViewBoundary_right(lua_State* tolua_S)
{
  Camera::ViewBoundary* self = (Camera::ViewBoundary*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'right'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->right = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: top of class  ViewBoundary */
#ifndef TOLUA_DISABLE_tolua_get_Camera__ViewBoundary_top
static int tolua_get_Camera__ViewBoundary_top(lua_State* tolua_S)
{
  Camera::ViewBoundary* self = (Camera::ViewBoundary*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'top'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->top);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: top of class  ViewBoundary */
#ifndef TOLUA_DISABLE_tolua_set_Camera__ViewBoundary_top
static int tolua_set_Camera__ViewBoundary_top(lua_State* tolua_S)
{
  Camera::ViewBoundary* self = (Camera::ViewBoundary*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'top'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->top = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bottom of class  ViewBoundary */
#ifndef TOLUA_DISABLE_tolua_get_Camera__ViewBoundary_bottom
static int tolua_get_Camera__ViewBoundary_bottom(lua_State* tolua_S)
{
  Camera::ViewBoundary* self = (Camera::ViewBoundary*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bottom'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->bottom);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bottom of class  ViewBoundary */
#ifndef TOLUA_DISABLE_tolua_set_Camera__ViewBoundary_bottom
static int tolua_set_Camera__ViewBoundary_bottom(lua_State* tolua_S)
{
  Camera::ViewBoundary* self = (Camera::ViewBoundary*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bottom'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bottom = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_new00
static int tolua_tiny_engine_Camera_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Camera* tolua_ret = (Camera*)  Mtolua_new((Camera)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Camera");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_new00_local
static int tolua_tiny_engine_Camera_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Camera* tolua_ret = (Camera*)  Mtolua_new((Camera)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Camera");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_delete00
static int tolua_tiny_engine_Camera_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setViewPort of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_setViewPort00
static int tolua_tiny_engine_Camera_setViewPort00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewPort'", NULL);
#endif
  {
   self->setViewPort(width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setViewPort'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_setPosition00
static int tolua_tiny_engine_Camera_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_getPosition00
static int tolua_tiny_engine_Camera_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'", NULL);
#endif
  {
   Vec2& tolua_ret = (Vec2&)  self->getPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Vec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setViewTransform of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_setViewTransform00
static int tolua_tiny_engine_Camera_setViewTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Transform",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  const Transform* view_transform = ((const Transform*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewTransform'", NULL);
#endif
  {
   self->setViewTransform(*view_transform);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setViewTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getViewTransform of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_getViewTransform00
static int tolua_tiny_engine_Camera_getViewTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getViewTransform'", NULL);
#endif
  {
   const Transform& tolua_ret = (const Transform&)  self->getViewTransform();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Transform");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getViewTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOrthoTransform of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_setOrthoTransform00
static int tolua_tiny_engine_Camera_setOrthoTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Transform",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  const Transform* ortho_transform = ((const Transform*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOrthoTransform'", NULL);
#endif
  {
   self->setOrthoTransform(*ortho_transform);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOrthoTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOrthoTransform of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_getOrthoTransform00
static int tolua_tiny_engine_Camera_getOrthoTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOrthoTransform'", NULL);
#endif
  {
   const Transform& tolua_ret = (const Transform&)  self->getOrthoTransform();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Transform");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOrthoTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateViewBoundary of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_updateViewBoundary00
static int tolua_tiny_engine_Camera_updateViewBoundary00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateViewBoundary'", NULL);
#endif
  {
   self->updateViewBoundary();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateViewBoundary'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getViewBoundary of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_getViewBoundary00
static int tolua_tiny_engine_Camera_getViewBoundary00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getViewBoundary'", NULL);
#endif
  {
   const Camera::ViewBoundary& tolua_ret = (const Camera::ViewBoundary&)  self->getViewBoundary();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Camera::ViewBoundary");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getViewBoundary'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: convertScreenToWorld of class  Camera */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Camera_convertScreenToWorld00
static int tolua_tiny_engine_Camera_convertScreenToWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'convertScreenToWorld'", NULL);
#endif
  {
   Vec2 tolua_ret = (Vec2)  self->convertScreenToWorld(x,y);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'convertScreenToWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Scene */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Scene_new00
static int tolua_tiny_engine_Scene_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Scene* tolua_ret = (Scene*)  Mtolua_new((Scene)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Scene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Scene */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Scene_new00_local
static int tolua_tiny_engine_Scene_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Scene* tolua_ret = (Scene*)  Mtolua_new((Scene)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Scene");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Scene */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Scene_new01
static int tolua_tiny_engine_Scene_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string scene_folder = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  int row = ((int)  tolua_tonumber(tolua_S,3,0));
  int col = ((int)  tolua_tonumber(tolua_S,4,0));
  const std::string block_file = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  int brow = ((int)  tolua_tonumber(tolua_S,6,0));
  int bcol = ((int)  tolua_tonumber(tolua_S,7,0));
  {
   Scene* tolua_ret = (Scene*)  Mtolua_new((Scene)(scene_folder,row,col,block_file,brow,bcol));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Scene");
   tolua_pushcppstring(tolua_S,(const char*)scene_folder);
   tolua_pushcppstring(tolua_S,(const char*)block_file);
  }
 }
 return 3;
tolua_lerror:
 return tolua_tiny_engine_Scene_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Scene */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Scene_new01_local
static int tolua_tiny_engine_Scene_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string scene_folder = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  int row = ((int)  tolua_tonumber(tolua_S,3,0));
  int col = ((int)  tolua_tonumber(tolua_S,4,0));
  const std::string block_file = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  int brow = ((int)  tolua_tonumber(tolua_S,6,0));
  int bcol = ((int)  tolua_tonumber(tolua_S,7,0));
  {
   Scene* tolua_ret = (Scene*)  Mtolua_new((Scene)(scene_folder,row,col,block_file,brow,bcol));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Scene");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushcppstring(tolua_S,(const char*)scene_folder);
   tolua_pushcppstring(tolua_S,(const char*)block_file);
  }
 }
 return 3;
tolua_lerror:
 return tolua_tiny_engine_Scene_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Scene */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Scene_delete00
static int tolua_tiny_engine_Scene_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: accept of class  Scene */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Scene_accept00
static int tolua_tiny_engine_Scene_accept00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"NodeVisitor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  NodeVisitor* node_visitor = ((NodeVisitor*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'accept'", NULL);
#endif
  {
   self->accept(node_visitor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'accept'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  Scene */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Scene_draw00
static int tolua_tiny_engine_Scene_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  Renderer* renderer = ((Renderer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'", NULL);
#endif
  {
   self->draw(renderer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActiveCamera of class  Scene */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Scene_setActiveCamera00
static int tolua_tiny_engine_Scene_setActiveCamera00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  Camera* camera = ((Camera*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActiveCamera'", NULL);
#endif
  {
   self->setActiveCamera(camera);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActiveCamera'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActiveCamera of class  Scene */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Scene_getActiveCamera00
static int tolua_tiny_engine_Scene_getActiveCamera00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActiveCamera'", NULL);
#endif
  {
   Camera* tolua_ret = (Camera*)  self->getActiveCamera();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Camera");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActiveCamera'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBlocked of class  Scene */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Scene_isBlocked00
static int tolua_tiny_engine_Scene_isBlocked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBlocked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBlocked(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBlocked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  Scene */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Scene_addChild00
static int tolua_tiny_engine_Scene_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  Node* child = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_new00
static int tolua_tiny_engine_Sprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Sprite* tolua_ret = (Sprite*)  Mtolua_new((Sprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_new00_local
static int tolua_tiny_engine_Sprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Sprite* tolua_ret = (Sprite*)  Mtolua_new((Sprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Sprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_delete00
static int tolua_tiny_engine_Sprite_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: accept of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_accept00
static int tolua_tiny_engine_Sprite_accept00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"NodeVisitor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  NodeVisitor* node_visitor = ((NodeVisitor*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'accept'", NULL);
#endif
  {
   self->accept(node_visitor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'accept'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_draw00
static int tolua_tiny_engine_Sprite_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  Renderer* renderer = ((Renderer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'", NULL);
#endif
  {
   self->draw(renderer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadTexture of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_loadTexture00
static int tolua_tiny_engine_Sprite_loadTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string image_file = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTexture'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->loadTexture(image_file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)image_file);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadTexture of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_loadTexture01
static int tolua_tiny_engine_Sprite_loadTexture01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Image",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  Image* image = ((Image*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTexture'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->loadTexture(image);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_tiny_engine_Sprite_loadTexture00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_update00
static int tolua_tiny_engine_Sprite_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  float delta_time = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(delta_time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerAnimation of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_registerAnimation00
static int tolua_tiny_engine_Sprite_registerAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string anim_name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  Animation* animation = ((Animation*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerAnimation'", NULL);
#endif
  {
   self->registerAnimation(anim_name,animation);
   tolua_pushcppstring(tolua_S,(const char*)anim_name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_play00
static int tolua_tiny_engine_Sprite_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string anim_name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play(anim_name);
   tolua_pushcppstring(tolua_S,(const char*)anim_name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_stop00
static int tolua_tiny_engine_Sprite_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string anim_name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   self->stop(anim_name);
   tolua_pushcppstring(tolua_S,(const char*)anim_name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addEventListener of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_addEventListener00
static int tolua_tiny_engine_Sprite_addEventListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_CALLBACK",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  EventType event_type = ((EventType) (int)  tolua_tonumber(tolua_S,2,0));
  LUA_CALLBACK callback = (toluafix_ref_function(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addEventListener'", NULL);
#endif
  {
   self->addEventListener(event_type,callback);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addEventListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeEventListener of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_removeEventListener00
static int tolua_tiny_engine_Sprite_removeEventListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  EventType event_type = ((EventType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeEventListener'", NULL);
#endif
  {
   self->removeEventListener(event_type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeEventListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_setPosition00
static int tolua_tiny_engine_Sprite_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_getPosition00
static int tolua_tiny_engine_Sprite_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'", NULL);
#endif
  {
   Vec2& tolua_ret = (Vec2&)  self->getPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Vec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: schedule of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_schedule00
static int tolua_tiny_engine_Sprite_schedule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'schedule'", NULL);
#endif
  {
   self->schedule(key);
   tolua_pushcppstring(tolua_S,(const char*)key);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'schedule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentSize of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_setContentSize00
static int tolua_tiny_engine_Sprite_setContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentSize'", NULL);
#endif
  {
   self->setContentSize(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUI of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Sprite_setUI00
static int tolua_tiny_engine_Sprite_setUI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  bool ui = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUI'", NULL);
#endif
  {
   self->setUI(ui);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Animation */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Animation_new00
static int tolua_tiny_engine_Animation_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Animation* tolua_ret = (Animation*)  Mtolua_new((Animation)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Animation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Animation */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Animation_new00_local
static int tolua_tiny_engine_Animation_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Animation* tolua_ret = (Animation*)  Mtolua_new((Animation)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Animation");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Animation */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Animation_new01
static int tolua_tiny_engine_Animation_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string animation_folder = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   Animation* tolua_ret = (Animation*)  Mtolua_new((Animation)(animation_folder));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Animation");
   tolua_pushcppstring(tolua_S,(const char*)animation_folder);
  }
 }
 return 2;
tolua_lerror:
 return tolua_tiny_engine_Animation_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Animation */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Animation_new01_local
static int tolua_tiny_engine_Animation_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string animation_folder = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   Animation* tolua_ret = (Animation*)  Mtolua_new((Animation)(animation_folder));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Animation");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushcppstring(tolua_S,(const char*)animation_folder);
  }
 }
 return 2;
tolua_lerror:
 return tolua_tiny_engine_Animation_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Animation */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Animation_delete00
static int tolua_tiny_engine_Animation_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: bindSprite of class  Animation */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Animation_bindSprite00
static int tolua_tiny_engine_Animation_bindSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
  Sprite* sprite = ((Sprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'bindSprite'", NULL);
#endif
  {
   self->bindSprite(sprite);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bindSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDuration of class  Animation */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Animation_setDuration00
static int tolua_tiny_engine_Animation_setDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDuration'", NULL);
#endif
  {
   self->setDuration(duration);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  Animation */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Animation_update00
static int tolua_tiny_engine_Animation_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
  float delta_time = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(delta_time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2_new00
static int tolua_tiny_engine_Vec2_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Vec2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Vec2* tolua_ret = (Vec2*)  Mtolua_new((Vec2)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Vec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2_new00_local
static int tolua_tiny_engine_Vec2_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Vec2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Vec2* tolua_ret = (Vec2*)  Mtolua_new((Vec2)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2_new01
static int tolua_tiny_engine_Vec2_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Vec2",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Vec2* v = ((const Vec2*)  tolua_tousertype(tolua_S,2,0));
  {
   Vec2* tolua_ret = (Vec2*)  Mtolua_new((Vec2)(*v));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Vec2");
  }
 }
 return 1;
tolua_lerror:
 return tolua_tiny_engine_Vec2_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2_new01_local
static int tolua_tiny_engine_Vec2_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Vec2",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Vec2* v = ((const Vec2*)  tolua_tousertype(tolua_S,2,0));
  {
   Vec2* tolua_ret = (Vec2*)  Mtolua_new((Vec2)(*v));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_tiny_engine_Vec2_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2_new02
static int tolua_tiny_engine_Vec2_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Vec2",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   Vec2* tolua_ret = (Vec2*)  Mtolua_new((Vec2)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Vec2");
  }
 }
 return 1;
tolua_lerror:
 return tolua_tiny_engine_Vec2_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2_new02_local
static int tolua_tiny_engine_Vec2_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Vec2",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   Vec2* tolua_ret = (Vec2*)  Mtolua_new((Vec2)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_tiny_engine_Vec2_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2_delete00
static int tolua_tiny_engine_Vec2_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Vec2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Vec2* self = (Vec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2__add00
static int tolua_tiny_engine_Vec2__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Vec2",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Vec2* self = (const Vec2*)  tolua_tousertype(tolua_S,1,0);
  const Vec2* v = ((const Vec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   Vec2 tolua_ret = (Vec2)  self->operator+(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2__sub00
static int tolua_tiny_engine_Vec2__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Vec2",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Vec2* self = (const Vec2*)  tolua_tousertype(tolua_S,1,0);
  const Vec2* v = ((const Vec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   Vec2 tolua_ret = (Vec2)  self->operator-(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2__mul00
static int tolua_tiny_engine_Vec2__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Vec2",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Vec2* self = (const Vec2*)  tolua_tousertype(tolua_S,1,0);
  float s = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   Vec2 tolua_ret = (Vec2)  self->operator*(s);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2__div00
static int tolua_tiny_engine_Vec2__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Vec2",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Vec2* self = (const Vec2*)  tolua_tousertype(tolua_S,1,0);
  float s = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   Vec2 tolua_ret = (Vec2)  self->operator/(s);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2__eq00
static int tolua_tiny_engine_Vec2__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Vec2",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Vec2* self = (Vec2*)  tolua_tousertype(tolua_S,1,0);
  const Vec2* v = ((const Vec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*v);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: x of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2_x00
static int tolua_tiny_engine_Vec2_x00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Vec2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Vec2* self = (Vec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'x'", NULL);
#endif
  {
   float tolua_ret = (float)  self->x();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'x'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: y of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2_y00
static int tolua_tiny_engine_Vec2_y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Vec2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Vec2* self = (Vec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'y'", NULL);
#endif
  {
   float tolua_ret = (float)  self->y();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'y'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: normalize of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2_normalize00
static int tolua_tiny_engine_Vec2_normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Vec2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Vec2* self = (Vec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'normalize'", NULL);
#endif
  {
   Vec2 tolua_ret = (Vec2)  self->normalize();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dot of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2_dot00
static int tolua_tiny_engine_Vec2_dot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Vec2",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Vec2* self = (Vec2*)  tolua_tousertype(tolua_S,1,0);
  const Vec2* v = ((const Vec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dot'", NULL);
#endif
  {
   float tolua_ret = (float)  self->dot(*v);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: length of class  Vec2 */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Vec2_length00
static int tolua_tiny_engine_Vec2_length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Vec2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Vec2* self = (Vec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'length'", NULL);
#endif
  {
   float tolua_ret = (float)  self->length();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Event */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Event_new00
static int tolua_tiny_engine_Event_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Event",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Event* tolua_ret = (Event*)  Mtolua_new((Event)(key));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Event");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Event */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Event_new00_local
static int tolua_tiny_engine_Event_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Event",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Event* tolua_ret = (Event*)  Mtolua_new((Event)(key));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Event");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Event */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Event_delete00
static int tolua_tiny_engine_Event_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Event",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Event* self = (Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getKey of class  Event */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Event_getKey00
static int tolua_tiny_engine_Event_getKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Event",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Event* self = (Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getKey'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getKey();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  MouseEvent */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_MouseEvent_new00
static int tolua_tiny_engine_MouseEvent_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MouseEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
  float x = ((float)  tolua_tonumber(tolua_S,3,0));
  float y = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   MouseEvent* tolua_ret = (MouseEvent*)  Mtolua_new((MouseEvent)(key,x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MouseEvent");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  MouseEvent */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_MouseEvent_new00_local
static int tolua_tiny_engine_MouseEvent_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MouseEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
  float x = ((float)  tolua_tonumber(tolua_S,3,0));
  float y = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   MouseEvent* tolua_ret = (MouseEvent*)  Mtolua_new((MouseEvent)(key,x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MouseEvent");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  MouseEvent */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_MouseEvent_delete00
static int tolua_tiny_engine_MouseEvent_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MouseEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MouseEvent* self = (MouseEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getKey of class  MouseEvent */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_MouseEvent_getKey00
static int tolua_tiny_engine_MouseEvent_getKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MouseEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MouseEvent* self = (MouseEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getKey'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getKey();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getX of class  MouseEvent */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_MouseEvent_getX00
static int tolua_tiny_engine_MouseEvent_getX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MouseEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MouseEvent* self = (MouseEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getY of class  MouseEvent */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_MouseEvent_getY00
static int tolua_tiny_engine_MouseEvent_getY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MouseEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MouseEvent* self = (MouseEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  EventListener */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_EventListener_new00
static int tolua_tiny_engine_EventListener_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EventListener",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const LUA_CALLBACK",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
  const LUA_CALLBACK callback = *((const LUA_CALLBACK*)  tolua_tousertype(tolua_S,3,0));
  {
   EventListener* tolua_ret = (EventListener*)  Mtolua_new((EventListener)(key,callback));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"EventListener");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  EventListener */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_EventListener_new00_local
static int tolua_tiny_engine_EventListener_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EventListener",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const LUA_CALLBACK",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
  const LUA_CALLBACK callback = *((const LUA_CALLBACK*)  tolua_tousertype(tolua_S,3,0));
  {
   EventListener* tolua_ret = (EventListener*)  Mtolua_new((EventListener)(key,callback));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"EventListener");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  EventListener */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_EventListener_delete00
static int tolua_tiny_engine_EventListener_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EventListener",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EventListener* self = (EventListener*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getKey of class  EventListener */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_EventListener_getKey00
static int tolua_tiny_engine_EventListener_getKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const EventListener",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const EventListener* self = (const EventListener*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getKey'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getKey();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLuaCallback of class  EventListener */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_EventListener_getLuaCallback00
static int tolua_tiny_engine_EventListener_getLuaCallback00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const EventListener",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const EventListener* self = (const EventListener*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLuaCallback'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getLuaCallback();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLuaCallback'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIWidget_new00
static int tolua_tiny_engine_UIWidget_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIWidget* tolua_ret = (UIWidget*)  Mtolua_new((UIWidget)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIWidget_new00_local
static int tolua_tiny_engine_UIWidget_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIWidget* tolua_ret = (UIWidget*)  Mtolua_new((UIWidget)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIWidget_delete00
static int tolua_tiny_engine_UIWidget_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isInWidget of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIWidget_isInWidget00
static int tolua_tiny_engine_UIWidget_isInWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isInWidget'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isInWidget(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isInWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWidgetName of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIWidget_setWidgetName00
static int tolua_tiny_engine_UIWidget_setWidgetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWidgetName'", NULL);
#endif
  {
   self->setWidgetName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWidgetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: seekWidgetByName of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIWidget_seekWidgetByName00
static int tolua_tiny_engine_UIWidget_seekWidgetByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'seekWidgetByName'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->seekWidgetByName(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seekWidgetByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIImage */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIImage_new00
static int tolua_tiny_engine_UIImage_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIImage* tolua_ret = (UIImage*)  Mtolua_new((UIImage)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIImage");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIImage */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIImage_new00_local
static int tolua_tiny_engine_UIImage_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIImage* tolua_ret = (UIImage*)  Mtolua_new((UIImage)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIImage");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIImage */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIImage_delete00
static int tolua_tiny_engine_UIImage_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImage* self = (UIImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setImage of class  UIImage */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIImage_setImage00
static int tolua_tiny_engine_UIImage_setImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImage",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImage* self = (UIImage*)  tolua_tousertype(tolua_S,1,0);
  const std::string image_file = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setImage'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setImage(image_file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)image_file);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  UIImage */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIImage_setPosition00
static int tolua_tiny_engine_UIImage_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImage",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImage* self = (UIImage*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  UIImage */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIImage_getPosition00
static int tolua_tiny_engine_UIImage_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImage* self = (UIImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'", NULL);
#endif
  {
   Vec2& tolua_ret = (Vec2&)  self->getPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Vec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentSize of class  UIImage */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIImage_setContentSize00
static int tolua_tiny_engine_UIImage_setContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImage",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImage* self = (UIImage*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentSize'", NULL);
#endif
  {
   self->setContentSize(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWidgetName of class  UIImage */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIImage_setWidgetName00
static int tolua_tiny_engine_UIImage_setWidgetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImage",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImage* self = (UIImage*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWidgetName'", NULL);
#endif
  {
   self->setWidgetName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWidgetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  UIImage */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIImage_addChild00
static int tolua_tiny_engine_UIImage_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImage",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImage* self = (UIImage*)  tolua_tousertype(tolua_S,1,0);
  Node* child = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addEventListener of class  UIImage */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIImage_addEventListener00
static int tolua_tiny_engine_UIImage_addEventListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImage",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_CALLBACK",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImage* self = (UIImage*)  tolua_tousertype(tolua_S,1,0);
  EventType event_type = ((EventType) (int)  tolua_tonumber(tolua_S,2,0));
  LUA_CALLBACK callback = (toluafix_ref_function(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addEventListener'", NULL);
#endif
  {
   self->addEventListener(event_type,callback);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addEventListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIButton_new00
static int tolua_tiny_engine_UIButton_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIButton* tolua_ret = (UIButton*)  Mtolua_new((UIButton)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIButton_new00_local
static int tolua_tiny_engine_UIButton_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIButton* tolua_ret = (UIButton*)  Mtolua_new((UIButton)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIButton");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIButton_delete00
static int tolua_tiny_engine_UIButton_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setImage of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIButton_setImage00
static int tolua_tiny_engine_UIButton_setImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const std::string image_file = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setImage'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setImage(image_file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)image_file);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIButton_setPosition00
static int tolua_tiny_engine_UIButton_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIButton_getPosition00
static int tolua_tiny_engine_UIButton_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'", NULL);
#endif
  {
   Vec2& tolua_ret = (Vec2&)  self->getPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Vec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentSize of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIButton_setContentSize00
static int tolua_tiny_engine_UIButton_setContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentSize'", NULL);
#endif
  {
   self->setContentSize(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWidgetName of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIButton_setWidgetName00
static int tolua_tiny_engine_UIButton_setWidgetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWidgetName'", NULL);
#endif
  {
   self->setWidgetName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWidgetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIButton_addChild00
static int tolua_tiny_engine_UIButton_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  Node* child = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isInWidget of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIButton_isInWidget00
static int tolua_tiny_engine_UIButton_isInWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isInWidget'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isInWidget(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isInWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addEventListener of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIButton_addEventListener00
static int tolua_tiny_engine_UIButton_addEventListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_CALLBACK",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  EventType event_type = ((EventType) (int)  tolua_tonumber(tolua_S,2,0));
  LUA_CALLBACK callback = (toluafix_ref_function(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addEventListener'", NULL);
#endif
  {
   self->addEventListener(event_type,callback);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addEventListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIPanel */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIPanel_new00
static int tolua_tiny_engine_UIPanel_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIPanel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIPanel* tolua_ret = (UIPanel*)  Mtolua_new((UIPanel)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIPanel");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIPanel */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIPanel_new00_local
static int tolua_tiny_engine_UIPanel_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIPanel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIPanel* tolua_ret = (UIPanel*)  Mtolua_new((UIPanel)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIPanel");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIPanel */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIPanel_delete00
static int tolua_tiny_engine_UIPanel_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPanel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPanel* self = (UIPanel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setImage of class  UIPanel */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIPanel_setImage00
static int tolua_tiny_engine_UIPanel_setImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPanel",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPanel* self = (UIPanel*)  tolua_tousertype(tolua_S,1,0);
  const std::string image_file = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setImage'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setImage(image_file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)image_file);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  UIPanel */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIPanel_setPosition00
static int tolua_tiny_engine_UIPanel_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPanel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPanel* self = (UIPanel*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentSize of class  UIPanel */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIPanel_setContentSize00
static int tolua_tiny_engine_UIPanel_setContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPanel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPanel* self = (UIPanel*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentSize'", NULL);
#endif
  {
   self->setContentSize(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWidgetName of class  UIPanel */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIPanel_setWidgetName00
static int tolua_tiny_engine_UIPanel_setWidgetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPanel",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPanel* self = (UIPanel*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWidgetName'", NULL);
#endif
  {
   self->setWidgetName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWidgetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  UIPanel */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_UIPanel_addChild00
static int tolua_tiny_engine_UIPanel_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPanel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPanel* self = (UIPanel*)  tolua_tousertype(tolua_S,1,0);
  Node* child = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Size */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Size_new00
static int tolua_tiny_engine_Size_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Size",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Size* tolua_ret = (Size*)  Mtolua_new((Size)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Size");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Size */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Size_new00_local
static int tolua_tiny_engine_Size_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Size",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Size* tolua_ret = (Size*)  Mtolua_new((Size)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Size");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Size */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Size_new01
static int tolua_tiny_engine_Size_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Size",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float w = ((float)  tolua_tonumber(tolua_S,2,0));
  float h = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   Size* tolua_ret = (Size*)  Mtolua_new((Size)(w,h));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Size");
  }
 }
 return 1;
tolua_lerror:
 return tolua_tiny_engine_Size_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Size */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Size_new01_local
static int tolua_tiny_engine_Size_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Size",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float w = ((float)  tolua_tonumber(tolua_S,2,0));
  float h = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   Size* tolua_ret = (Size*)  Mtolua_new((Size)(w,h));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Size");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_tiny_engine_Size_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasZero of class  Size */
#ifndef TOLUA_DISABLE_tolua_tiny_engine_Size_hasZero00
static int tolua_tiny_engine_Size_hasZero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Size",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Size* self = (Size*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasZero'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hasZero();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasZero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: width of class  Size */
#ifndef TOLUA_DISABLE_tolua_get_Size_width
static int tolua_get_Size_width(lua_State* tolua_S)
{
  Size* self = (Size*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'width'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->width);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: width of class  Size */
#ifndef TOLUA_DISABLE_tolua_set_Size_width
static int tolua_set_Size_width(lua_State* tolua_S)
{
  Size* self = (Size*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'width'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->width = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: height of class  Size */
#ifndef TOLUA_DISABLE_tolua_get_Size_height
static int tolua_get_Size_height(lua_State* tolua_S)
{
  Size* self = (Size*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'height'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->height);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: height of class  Size */
#ifndef TOLUA_DISABLE_tolua_set_Size_height
static int tolua_set_Size_height(lua_State* tolua_S)
{
  Size* self = (Size*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'height'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->height = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_tiny_engine_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Director","Director","Ref",NULL);
  tolua_beginmodule(tolua_S,"Director");
   tolua_function(tolua_S,"getInstance",tolua_tiny_engine_Director_getInstance00);
   tolua_function(tolua_S,"setWindowSize",tolua_tiny_engine_Director_setWindowSize00);
   tolua_function(tolua_S,"getWindowSize",tolua_tiny_engine_Director_getWindowSize00);
   tolua_function(tolua_S,"setActiveScene",tolua_tiny_engine_Director_setActiveScene00);
   tolua_function(tolua_S,"getActiveScene",tolua_tiny_engine_Director_getActiveScene00);
   tolua_function(tolua_S,"getScheduler",tolua_tiny_engine_Director_getScheduler00);
   tolua_function(tolua_S,"getEventDispatcher",tolua_tiny_engine_Director_getEventDispatcher00);
   tolua_function(tolua_S,"getDeltaTime",tolua_tiny_engine_Director_getDeltaTime00);
   tolua_function(tolua_S,"start",tolua_tiny_engine_Director_start00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Camera","Camera","Node",tolua_collect_Camera);
  #else
  tolua_cclass(tolua_S,"Camera","Camera","Node",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Camera");
   tolua_cclass(tolua_S,"ViewBoundary","Camera::ViewBoundary","",NULL);
   tolua_beginmodule(tolua_S,"ViewBoundary");
    tolua_variable(tolua_S,"left",tolua_get_Camera__ViewBoundary_left,tolua_set_Camera__ViewBoundary_left);
    tolua_variable(tolua_S,"right",tolua_get_Camera__ViewBoundary_right,tolua_set_Camera__ViewBoundary_right);
    tolua_variable(tolua_S,"top",tolua_get_Camera__ViewBoundary_top,tolua_set_Camera__ViewBoundary_top);
    tolua_variable(tolua_S,"bottom",tolua_get_Camera__ViewBoundary_bottom,tolua_set_Camera__ViewBoundary_bottom);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"new",tolua_tiny_engine_Camera_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_Camera_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_Camera_new00_local);
   tolua_function(tolua_S,"delete",tolua_tiny_engine_Camera_delete00);
   tolua_function(tolua_S,"setViewPort",tolua_tiny_engine_Camera_setViewPort00);
   tolua_function(tolua_S,"setPosition",tolua_tiny_engine_Camera_setPosition00);
   tolua_function(tolua_S,"getPosition",tolua_tiny_engine_Camera_getPosition00);
   tolua_function(tolua_S,"setViewTransform",tolua_tiny_engine_Camera_setViewTransform00);
   tolua_function(tolua_S,"getViewTransform",tolua_tiny_engine_Camera_getViewTransform00);
   tolua_function(tolua_S,"setOrthoTransform",tolua_tiny_engine_Camera_setOrthoTransform00);
   tolua_function(tolua_S,"getOrthoTransform",tolua_tiny_engine_Camera_getOrthoTransform00);
   tolua_function(tolua_S,"updateViewBoundary",tolua_tiny_engine_Camera_updateViewBoundary00);
   tolua_function(tolua_S,"getViewBoundary",tolua_tiny_engine_Camera_getViewBoundary00);
   tolua_function(tolua_S,"convertScreenToWorld",tolua_tiny_engine_Camera_convertScreenToWorld00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Scene","Scene","Node",tolua_collect_Scene);
  #else
  tolua_cclass(tolua_S,"Scene","Scene","Node",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Scene");
   tolua_function(tolua_S,"new",tolua_tiny_engine_Scene_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_Scene_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_Scene_new00_local);
   tolua_function(tolua_S,"new",tolua_tiny_engine_Scene_new01);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_Scene_new01_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_Scene_new01_local);
   tolua_function(tolua_S,"delete",tolua_tiny_engine_Scene_delete00);
   tolua_function(tolua_S,"accept",tolua_tiny_engine_Scene_accept00);
   tolua_function(tolua_S,"draw",tolua_tiny_engine_Scene_draw00);
   tolua_function(tolua_S,"setActiveCamera",tolua_tiny_engine_Scene_setActiveCamera00);
   tolua_function(tolua_S,"getActiveCamera",tolua_tiny_engine_Scene_getActiveCamera00);
   tolua_function(tolua_S,"isBlocked",tolua_tiny_engine_Scene_isBlocked00);
   tolua_function(tolua_S,"addChild",tolua_tiny_engine_Scene_addChild00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Sprite","Sprite","Node",tolua_collect_Sprite);
  #else
  tolua_cclass(tolua_S,"Sprite","Sprite","Node",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Sprite");
   tolua_function(tolua_S,"new",tolua_tiny_engine_Sprite_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_Sprite_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_Sprite_new00_local);
   tolua_function(tolua_S,"delete",tolua_tiny_engine_Sprite_delete00);
   tolua_function(tolua_S,"accept",tolua_tiny_engine_Sprite_accept00);
   tolua_function(tolua_S,"draw",tolua_tiny_engine_Sprite_draw00);
   tolua_function(tolua_S,"loadTexture",tolua_tiny_engine_Sprite_loadTexture00);
   tolua_function(tolua_S,"loadTexture",tolua_tiny_engine_Sprite_loadTexture01);
   tolua_function(tolua_S,"update",tolua_tiny_engine_Sprite_update00);
   tolua_function(tolua_S,"registerAnimation",tolua_tiny_engine_Sprite_registerAnimation00);
   tolua_function(tolua_S,"play",tolua_tiny_engine_Sprite_play00);
   tolua_function(tolua_S,"stop",tolua_tiny_engine_Sprite_stop00);
   tolua_function(tolua_S,"addEventListener",tolua_tiny_engine_Sprite_addEventListener00);
   tolua_function(tolua_S,"removeEventListener",tolua_tiny_engine_Sprite_removeEventListener00);
   tolua_function(tolua_S,"setPosition",tolua_tiny_engine_Sprite_setPosition00);
   tolua_function(tolua_S,"getPosition",tolua_tiny_engine_Sprite_getPosition00);
   tolua_function(tolua_S,"schedule",tolua_tiny_engine_Sprite_schedule00);
   tolua_function(tolua_S,"setContentSize",tolua_tiny_engine_Sprite_setContentSize00);
   tolua_function(tolua_S,"setUI",tolua_tiny_engine_Sprite_setUI00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Animation","Animation","Ref",tolua_collect_Animation);
  #else
  tolua_cclass(tolua_S,"Animation","Animation","Ref",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Animation");
   tolua_function(tolua_S,"new",tolua_tiny_engine_Animation_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_Animation_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_Animation_new00_local);
   tolua_function(tolua_S,"new",tolua_tiny_engine_Animation_new01);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_Animation_new01_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_Animation_new01_local);
   tolua_function(tolua_S,"delete",tolua_tiny_engine_Animation_delete00);
   tolua_function(tolua_S,"bindSprite",tolua_tiny_engine_Animation_bindSprite00);
   tolua_function(tolua_S,"setDuration",tolua_tiny_engine_Animation_setDuration00);
   tolua_function(tolua_S,"update",tolua_tiny_engine_Animation_update00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Vec2","Vec2","",tolua_collect_Vec2);
  #else
  tolua_cclass(tolua_S,"Vec2","Vec2","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Vec2");
   tolua_function(tolua_S,"new",tolua_tiny_engine_Vec2_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_Vec2_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_Vec2_new00_local);
   tolua_function(tolua_S,"new",tolua_tiny_engine_Vec2_new01);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_Vec2_new01_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_Vec2_new01_local);
   tolua_function(tolua_S,"new",tolua_tiny_engine_Vec2_new02);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_Vec2_new02_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_Vec2_new02_local);
   tolua_function(tolua_S,"delete",tolua_tiny_engine_Vec2_delete00);
   tolua_function(tolua_S,".add",tolua_tiny_engine_Vec2__add00);
   tolua_function(tolua_S,".sub",tolua_tiny_engine_Vec2__sub00);
   tolua_function(tolua_S,".mul",tolua_tiny_engine_Vec2__mul00);
   tolua_function(tolua_S,".div",tolua_tiny_engine_Vec2__div00);
   tolua_function(tolua_S,".eq",tolua_tiny_engine_Vec2__eq00);
   tolua_function(tolua_S,"x",tolua_tiny_engine_Vec2_x00);
   tolua_function(tolua_S,"y",tolua_tiny_engine_Vec2_y00);
   tolua_function(tolua_S,"normalize",tolua_tiny_engine_Vec2_normalize00);
   tolua_function(tolua_S,"dot",tolua_tiny_engine_Vec2_dot00);
   tolua_function(tolua_S,"length",tolua_tiny_engine_Vec2_length00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"TE_MOUSE_LEFT_DOWN",TE_MOUSE_LEFT_DOWN);
  tolua_constant(tolua_S,"TE_MOUSE_LEFT_UP",TE_MOUSE_LEFT_UP);
  tolua_constant(tolua_S,"TE_MOUSE_RIGHT_DOWN",TE_MOUSE_RIGHT_DOWN);
  tolua_constant(tolua_S,"TE_MOUSE_RIGHT_UP",TE_MOUSE_RIGHT_UP);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Event","Event","Ref",tolua_collect_Event);
  #else
  tolua_cclass(tolua_S,"Event","Event","Ref",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Event");
   tolua_function(tolua_S,"new",tolua_tiny_engine_Event_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_Event_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_Event_new00_local);
   tolua_function(tolua_S,"delete",tolua_tiny_engine_Event_delete00);
   tolua_function(tolua_S,"getKey",tolua_tiny_engine_Event_getKey00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"MouseEvent","MouseEvent","Event",tolua_collect_MouseEvent);
  #else
  tolua_cclass(tolua_S,"MouseEvent","MouseEvent","Event",NULL);
  #endif
  tolua_beginmodule(tolua_S,"MouseEvent");
   tolua_function(tolua_S,"new",tolua_tiny_engine_MouseEvent_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_MouseEvent_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_MouseEvent_new00_local);
   tolua_function(tolua_S,"delete",tolua_tiny_engine_MouseEvent_delete00);
   tolua_function(tolua_S,"getKey",tolua_tiny_engine_MouseEvent_getKey00);
   tolua_function(tolua_S,"getX",tolua_tiny_engine_MouseEvent_getX00);
   tolua_function(tolua_S,"getY",tolua_tiny_engine_MouseEvent_getY00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"EventListener","EventListener","Ref",tolua_collect_EventListener);
  #else
  tolua_cclass(tolua_S,"EventListener","EventListener","Ref",NULL);
  #endif
  tolua_beginmodule(tolua_S,"EventListener");
   tolua_function(tolua_S,"new",tolua_tiny_engine_EventListener_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_EventListener_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_EventListener_new00_local);
   tolua_function(tolua_S,"delete",tolua_tiny_engine_EventListener_delete00);
   tolua_function(tolua_S,"getKey",tolua_tiny_engine_EventListener_getKey00);
   tolua_function(tolua_S,"getLuaCallback",tolua_tiny_engine_EventListener_getLuaCallback00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIWidget","UIWidget","Node",tolua_collect_UIWidget);
  #else
  tolua_cclass(tolua_S,"UIWidget","UIWidget","Node",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIWidget");
   tolua_function(tolua_S,"new",tolua_tiny_engine_UIWidget_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_UIWidget_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_UIWidget_new00_local);
   tolua_function(tolua_S,"delete",tolua_tiny_engine_UIWidget_delete00);
   tolua_function(tolua_S,"isInWidget",tolua_tiny_engine_UIWidget_isInWidget00);
   tolua_function(tolua_S,"setWidgetName",tolua_tiny_engine_UIWidget_setWidgetName00);
   tolua_function(tolua_S,"seekWidgetByName",tolua_tiny_engine_UIWidget_seekWidgetByName00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIImage","UIImage","UIWidget",tolua_collect_UIImage);
  #else
  tolua_cclass(tolua_S,"UIImage","UIImage","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIImage");
   tolua_function(tolua_S,"new",tolua_tiny_engine_UIImage_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_UIImage_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_UIImage_new00_local);
   tolua_function(tolua_S,"delete",tolua_tiny_engine_UIImage_delete00);
   tolua_function(tolua_S,"setImage",tolua_tiny_engine_UIImage_setImage00);
   tolua_function(tolua_S,"setPosition",tolua_tiny_engine_UIImage_setPosition00);
   tolua_function(tolua_S,"getPosition",tolua_tiny_engine_UIImage_getPosition00);
   tolua_function(tolua_S,"setContentSize",tolua_tiny_engine_UIImage_setContentSize00);
   tolua_function(tolua_S,"setWidgetName",tolua_tiny_engine_UIImage_setWidgetName00);
   tolua_function(tolua_S,"addChild",tolua_tiny_engine_UIImage_addChild00);
   tolua_function(tolua_S,"addEventListener",tolua_tiny_engine_UIImage_addEventListener00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIButton","UIButton","UIWidget",tolua_collect_UIButton);
  #else
  tolua_cclass(tolua_S,"UIButton","UIButton","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIButton");
   tolua_function(tolua_S,"new",tolua_tiny_engine_UIButton_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_UIButton_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_UIButton_new00_local);
   tolua_function(tolua_S,"delete",tolua_tiny_engine_UIButton_delete00);
   tolua_function(tolua_S,"setImage",tolua_tiny_engine_UIButton_setImage00);
   tolua_function(tolua_S,"setPosition",tolua_tiny_engine_UIButton_setPosition00);
   tolua_function(tolua_S,"getPosition",tolua_tiny_engine_UIButton_getPosition00);
   tolua_function(tolua_S,"setContentSize",tolua_tiny_engine_UIButton_setContentSize00);
   tolua_function(tolua_S,"setWidgetName",tolua_tiny_engine_UIButton_setWidgetName00);
   tolua_function(tolua_S,"addChild",tolua_tiny_engine_UIButton_addChild00);
   tolua_function(tolua_S,"isInWidget",tolua_tiny_engine_UIButton_isInWidget00);
   tolua_function(tolua_S,"addEventListener",tolua_tiny_engine_UIButton_addEventListener00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIPanel","UIPanel","UIWidget",tolua_collect_UIPanel);
  #else
  tolua_cclass(tolua_S,"UIPanel","UIPanel","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIPanel");
   tolua_function(tolua_S,"new",tolua_tiny_engine_UIPanel_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_UIPanel_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_UIPanel_new00_local);
   tolua_function(tolua_S,"delete",tolua_tiny_engine_UIPanel_delete00);
   tolua_function(tolua_S,"setImage",tolua_tiny_engine_UIPanel_setImage00);
   tolua_function(tolua_S,"setPosition",tolua_tiny_engine_UIPanel_setPosition00);
   tolua_function(tolua_S,"setContentSize",tolua_tiny_engine_UIPanel_setContentSize00);
   tolua_function(tolua_S,"setWidgetName",tolua_tiny_engine_UIPanel_setWidgetName00);
   tolua_function(tolua_S,"addChild",tolua_tiny_engine_UIPanel_addChild00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Size","Size","",tolua_collect_Size);
  #else
  tolua_cclass(tolua_S,"Size","Size","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Size");
   tolua_function(tolua_S,"new",tolua_tiny_engine_Size_new00);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_Size_new00_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_Size_new00_local);
   tolua_function(tolua_S,"new",tolua_tiny_engine_Size_new01);
   tolua_function(tolua_S,"new_local",tolua_tiny_engine_Size_new01_local);
   tolua_function(tolua_S,".call",tolua_tiny_engine_Size_new01_local);
   tolua_function(tolua_S,"hasZero",tolua_tiny_engine_Size_hasZero00);
   tolua_variable(tolua_S,"width",tolua_get_Size_width,tolua_set_Size_width);
   tolua_variable(tolua_S,"height",tolua_get_Size_height,tolua_set_Size_height);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_tiny_engine (lua_State* tolua_S) {
 return tolua_tiny_engine_open(tolua_S);
};
#endif

