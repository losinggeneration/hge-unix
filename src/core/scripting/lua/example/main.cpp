#include <cstdio>

#include "hge.h"
#include "lua.hpp"

HGE *hge = 0;

bool FrameFunction() {
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;

	return  false;
}

int main(int argc, char *argv[]) {
	lua_State *L;
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunction);
	hge->System_SetState(HGE_TITLE, "HGE Scripting Example");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, true);



	if(hge->System_Initiate()) {
		hge->System_Start();
	}
	else {
		fprintf(stderr, "Unable to initialize HGE: %s\n", hge->System_GetErrorMessage());
	}

	hge->System_Shutdown();
	hge->Release();
	return 0;
}