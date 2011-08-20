#include <cstdio>

#include "hge.h"
#include "lua.hpp"

HGE *hge = 0;

void bind_to_lua(lua_State *L) {
	void bind_lua_hgeRect(lua_State *L);
	void bind_lua_hgeStrings(lua_State *L);
	void bind_lua_hgeVector(lua_State *L);

	bind_lua_hgeRect(L);
	bind_lua_hgeStrings(L);
	bind_lua_hgeVector(L);
}

bool FrameFunction() {
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;

	return  false;
}

int main(int argc, char *argv[]) {
	lua_State *L = luaL_newstate();
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunction);
	hge->System_SetState(HGE_TITLE, "HGE Scripting Example");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, true);

	luaL_openlibs(L);
	bind_to_lua(L);

	if(luaL_dofile(L, "hge_script.lua")) {
		fprintf(stderr, "%s\n", lua_tolstring(L, 1, NULL));
	}

	if(hge->System_Initiate()) {
		hge->System_Start();
	}
	else {
		fprintf(stderr, "Unable to initialize HGE: %s\n", hge->System_GetErrorMessage());
	}

	lua_close(L);
	hge->System_Shutdown();
	hge->Release();
	return 0;
}