#include <cstdio>

#include "hge.h"
#include "lua.hpp"

HGE *hge = 0;
// Needed for the callbacks
lua_State *global_state;

void bind_to_lua(lua_State *L) {
	void bind_lua_hgeAnim(lua_State *L);
	void bind_lua_hgeColor(lua_State *L);
	void bind_lua_hgeDistort(lua_State *L);
	void bind_lua_hgeFont(lua_State *L);
	void bind_lua_hgeSprite(lua_State *L);
	void bind_lua_hgeRect(lua_State *L);
	void bind_lua_hgeStrings(lua_State *L);
	void bind_lua_hgeVector(lua_State *L);
	void bind_lua_hgeParticle(lua_State *L);
	void bind_lua_hgeGui(lua_State *L);
	void bind_lua_hgeGuiCtrls(lua_State *L);
	void bind_lua_hgeResource(lua_State *L);
	void bind_lua_hge(lua_State *L);

	bind_lua_hgeAnim(L);
	bind_lua_hgeColor(L);
	bind_lua_hgeDistort(L);
	bind_lua_hgeFont(L);
	bind_lua_hgeSprite(L);
	bind_lua_hgeRect(L);
	bind_lua_hgeStrings(L);
	bind_lua_hgeVector(L);
	bind_lua_hgeParticle(L);
// 	bind_lua_hgeGui(L);
	bind_lua_hgeGuiCtrls(L);
// 	bind_lua_hgeResource(L);
	bind_lua_hge(L);
}

bool callLuaFunction(const char *f) {
	lua_getfield(global_state, LUA_GLOBALSINDEX, f);
	lua_call(global_state, 0, 1);
	bool rv = lua_toboolean(global_state, -1);
	lua_pop(global_state, 1);
	return rv;
}

bool FrameFunc() {
	callLuaFunction("FrameFunc");

	return  false;
}

bool RenderFunc() {
	callLuaFunction("RenderFunc");

	return false;
}

int main(int argc, char *argv[]) {
	lua_State *L = global_state = luaL_newstate();

	luaL_openlibs(L);
	bind_to_lua(L);

	if(luaL_dofile(L, "hge_init.lua")) {
		fprintf(stderr, "%s\n", lua_tolstring(L, 1, NULL));
	}

	// get the instance of hge
	hge = hgeCreate(HGE_VERSION);
	if(hge) {
		// Still have to do the frame function in C/C++
		hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
		hge->System_SetState(HGE_RENDERFUNC, RenderFunc);

		if(luaL_dofile(L, "hge_script.lua")) {
			fprintf(stderr, "%s\n", lua_tolstring(L, 1, NULL));
		}
	}

	lua_close(L);

	return 0;
}