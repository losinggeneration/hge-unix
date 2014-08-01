#include <string>

#include "hge.h"

#include "hge_lua.h"

void register_resource(lua_State *L);
void register_ini(lua_State *L);
void register_random(lua_State *L);
void register_timer(lua_State *L);
void register_effect(lua_State *L);
void register_music(lua_State *L);
void register_stream(lua_State *L);
void register_channel(lua_State *L);
void register_input(lua_State *L);
void register_gfx(lua_State *L);
void register_target(lua_State *L);
void register_texture(lua_State *L);

HTEXTURE *texture_check(lua_State *L);

void add_meta_function(lua_State *L, const char *metatable, const char *metafunction, lua_CFunction f);

#define DEBUG_STACK(L) do { printf("stack: %s:%d => %d\n", __FILE__, __LINE__, lua_gettop(L)); } while(0)
#define DEBUG_ARGS(L, fn) do { \
	printf("%s(", fn); \
	for(int i = 1; i <= lua_gettop(L); i++) { \
		printf("%s", lua_typename(L, lua_type(L, i))); \
		if(i != lua_gettop(L)) { \
			printf(", "); \
		} \
	} \
	printf(")\n"); \
} while(0)

#define STRINGIFY(x) #x

#define add_garbage(L, m, f) add_meta_function(L, m, "__gc", f)
#define add_index(L, m, f) add_meta_function(L, m, "__index", f)
#define add_newindex(L, m, f) add_meta_function(L, m, "__newindex", f)
#define add_tostring(L, m, f) add_meta_function(L, m, "__tostring", f)

#define REGISTER_HGE_USERDATA(name) do { \
	HGE **h = (HGE **)lua_newuserdata(L, sizeof(HGE **)); \
	*h = hgeCreate(HGE_VERSION); \
	luaL_newmetatable(L, STRINGIFY(hge.name)); \
	lua_pushvalue(L, -1); \
	lua_setfield(L, -2, "__index"); \
	add_garbage(L, STRINGIFY(hge.name), system_free); \
	luaL_register(L, NULL, name##_reg); \
	lua_setmetatable(L, -2); \
	lua_setfield(L, -2, STRINGIFY(name)); \
} while(0)

#define CHECK_USERDATA_TYPE(name) do { \
	if(lua_isuserdata(L, 1) == 0) { \
		const char *t = lua_tostring(L, 1); \
		if(t == NULL || std::string(t) != name##_TYPE) { \
			error(L, "Expected type " name##_TYPE); \
			return NULL; \
		} \
	} \
} while(0)

#define CHECK_USERDATA(name) do { \
	CHECK_USERDATA_TYPE(name); \
	return (name *)lua_touserdata(L, 1); \
} while(0)

inline void error(lua_State *L, const char *msg) {
	lua_pushstring(L, msg);
	lua_error(L);
}

inline void add_function(lua_State *L, const char *name, lua_CFunction f) {
	lua_pushstring(L, name);
	lua_pushcfunction(L, f);
	lua_settable(L, -3);
}

inline void add_meta_function(lua_State *L, const char *metatable, const char *metafunction, lua_CFunction f) {
	luaL_newmetatable(L, metatable);
	add_function(L, metafunction, f);
	lua_setmetatable(L, -2);
}


lua_State *global_state;

/* These are the callbacks. These call the Lua registry functions defined as hge.func_name */
bool hge_func(const char *f) {
	std::string fn = std::string() + "hge." + f + "func";
	lua_getfield(global_state, LUA_REGISTRYINDEX, fn.c_str());

	if(!lua_isfunction(global_state, -1)) {
		return false;
	}

	lua_call(global_state, 0, 1);

	bool is_nil = lua_isnoneornil(global_state, -1);
	if(!lua_isboolean(global_state, -1) && !is_nil) {
		std::string err = std::string() + "Expected a boolean to be returned from " + f + " function";
		error(global_state, err.c_str());
		return true;
	}

	if(is_nil) {
		return false;
	}

	return lua_toboolean(global_state, -1);
}

bool hge_framefunc() {
	return hge_func("frame");
}

bool hge_renderfunc() {
	return hge_func("render");
}

bool hge_focuslostfunc() {
	return hge_func("focuslost");
}

bool hge_focusgainfunc() {
	return hge_func("focusgain");
}

bool hge_gfxrestorefunc() {
	return hge_func("gfxrestore");
}

bool hge_exitfunc() {
	return hge_func("exit");
}

inline void add_constant(lua_State *L, const char *name, int value) {
	lua_pushstring(L, name);
	lua_pushnumber(L, value);
	lua_settable(L, -3);
}

void add_hge_constants(lua_State *L) {
	lua_pushstring(L, "bool");
	lua_newtable(L);
	add_constant(L, "windowed", HGE_WINDOWED);
	add_constant(L, "zbuffer", HGE_ZBUFFER);
	add_constant(L, "texture_filter", HGE_TEXTUREFILTER);
	add_constant(L, "sound", HGE_USESOUND);
	add_constant(L, "dont_suspend", HGE_DONTSUSPEND);
	add_constant(L, "hide_mouse", HGE_HIDEMOUSE);
	add_constant(L, "show_splash", HGE_SHOWSPLASH);
	lua_settable(L, -3);

	lua_pushstring(L, "func");
	lua_newtable(L);
	add_constant(L, "frame", HGE_FRAMEFUNC);
	add_constant(L, "render", HGE_RENDERFUNC);
	add_constant(L, "focus_lost", HGE_FOCUSLOSTFUNC);
	add_constant(L, "focus_gain", HGE_FOCUSGAINFUNC);
	add_constant(L, "gfx_restore", HGE_GFXRESTOREFUNC);
	add_constant(L, "exit", HGE_EXITFUNC);
	lua_settable(L, -3);

	lua_pushstring(L, "hwnd");
	lua_newtable(L);
	add_constant(L, "hwnd", HGE_HWND);
	add_constant(L, "parent", HGE_HWNDPARENT);
	lua_settable(L, -3);

	lua_pushstring(L, "int");
	lua_newtable(L);
	add_constant(L, "screen_width", HGE_SCREENWIDTH);
	add_constant(L, "screen_height", HGE_SCREENHEIGHT);
	add_constant(L, "screen_bpp", HGE_SCREENBPP);
	add_constant(L, "sample_rate", HGE_SAMPLERATE);
	add_constant(L, "fx_volume", HGE_FXVOLUME);
	add_constant(L, "music_volume", HGE_MUSVOLUME);
	add_constant(L, "stream_volume", HGE_STREAMVOLUME);
	add_constant(L, "fps", HGE_FPS);
	add_constant(L, "power_status", HGE_POWERSTATUS);
	add_constant(L, "orig_screen_width", HGE_ORIGSCREENWIDTH);
	add_constant(L, "orig_screen_height", HGE_ORIGSCREENHEIGHT);
	lua_settable(L, -3);

	lua_pushstring(L, "string");
	lua_newtable(L);
	add_constant(L, "icon", HGE_ICON);
	add_constant(L, "title", HGE_TITLE);
	add_constant(L, "ini_file", HGE_INIFILE);
	add_constant(L, "log_file", HGE_LOGFILE);
	lua_settable(L, -3);

	lua_pushstring(L, "fps");
	lua_newtable(L);
	add_constant(L, "unlimited", HGEFPS_UNLIMITED);
	add_constant(L, "vsync", HGEFPS_VSYNC);
	lua_settable(L, -3);

	lua_pushstring(L, "pwd");
	lua_newtable(L);
	add_constant(L, "ac", HGEPWR_AC);
	add_constant(L, "unsupported", HGEPWR_UNSUPPORTED);
	lua_settable(L, -3);
}

/* Check the first argument is full userdata and return it */
HGE *hge_param_userdata_check(lua_State *L) {
	CHECK_USERDATA_TYPE(HGE);
	return *((HGE **)lua_touserdata(L, 1));
}

/* check that the first argument is a userdata & make sure it's not free'd */
HGE *hge_check(lua_State *L) {
	HGE *h = hge_param_userdata_check(L);

	if(h == NULL) {
		error(L, "Cannot use a free'd " HGE_TYPE);
		return NULL;
	}

	return h;
}

/* void Release(); */
int system_free(lua_State *L) {
	HGE *h = hge_param_userdata_check(L);

	if(h != NULL) {
		h->Release();
		h = NULL;
	}

	return 0;
}

/* bool System_Initiate(); */
int system_initiate(lua_State *L) {
	HGE *h = hge_check(L);

	bool b = h->System_Initiate();

	lua_pushboolean(L, b);

	return 1;
}

/* void System_Shutdown(); */
int system_shutdown(lua_State *L) {
	HGE *h = hge_check(L);

	h->System_Shutdown();

	return 0;
}

/* bool System_Start(); */
int system_start(lua_State *L) {
	HGE *h = hge_check(L);

	bool b = h->System_Start();
	lua_pushboolean(L, b);

	return 1;
}

/* const char* System_GetErrorMessage(); */
int system_get_error_message(lua_State *L) {
	HGE *h = hge_check(L);

	const char *err = h->System_GetErrorMessage();
	lua_pushstring(L, err);

	return 1;
}

/* void System_Log(const char *format, ...); */
int system_log(lua_State *L) {
	HGE *h = hge_check(L);
	const char *fmt = lua_tostring(L, 2);
	int i;
	for(i = 3; i <= lua_gettop(L); i++);
	return 0;
}

/* bool System_Launch(const char *url); */
int system_launch(lua_State *L) {
	HGE *h = hge_check(L);

	const char *url = lua_tostring(L, 2);
	h->System_Launch(url);

	return 0;
}

/* void System_Snapshot(const char *filename); */
int system_snapshot(lua_State *L) {
	HGE *h = hge_check(L);

	const char *filename = lua_tostring(L, 2);
	h->System_Snapshot(filename);

	return 0;
}

/* void System_SetStateFunc(HGE->FuncState_t state, HGE->Callback value); */
void system_set_state_func(lua_State *L, HGE *h) {
	if(!lua_isnumber(L, 2)) {
		DEBUG_ARGS(L, "set_state_func");
		error(L, "Expected second argument to be a number");
		return;
	}

	bool is_nil = lua_isnoneornil(L, 3);
	if(!lua_isfunction(L, 3) && !is_nil) {
		DEBUG_ARGS(L, "set_state_func");
		error(L, "Expected callback to be a function or nil");
		return;
	}

	std::string func_name;
	hgeCallback cb;

	hgeFuncState state = (hgeFuncState)lua_tointeger(L, 2);
	switch(state) {
		case HGE_FRAMEFUNC:
			func_name = "hge.framefunc";
			cb = hge_framefunc;
			break;
		case HGE_RENDERFUNC:
			func_name = "hge.renderfunc";
			cb = hge_renderfunc;
			break;
		case HGE_FOCUSLOSTFUNC:
			func_name = "hge.focuslostfunc";
			cb = hge_focuslostfunc;
			break;
		case HGE_FOCUSGAINFUNC:
			func_name = "hge.focusgainfunc";
			cb = hge_focusgainfunc;
			break;
		case HGE_GFXRESTOREFUNC:
			func_name = "hge.gfxrestorefunc";
			cb = hge_gfxrestorefunc;
			break;
		case HGE_EXITFUNC:
			func_name = "hge.exitfunc";
			cb = hge_exitfunc;
			break;
		default:
			error(L, "function callback not implemented");
			return;
	}

	// make sure the function is on the top of the stack
	lua_pushvalue(L, 3);
	lua_setfield(L, LUA_REGISTRYINDEX, func_name.c_str());

	if(is_nil) {
		h->System_SetState(state, NULL);
	} else {
		h->System_SetState(state, cb);
	}
}

/* Callback HGE->System_GetStateFunc(HGE->FuncState_t state); */
void system_get_state_func(lua_State *L, HGE *h) {
	std::string func_name;
	hgeFuncState state = (hgeFuncState)lua_tointeger(L, 2);
	switch(state) {
		case HGE_FRAMEFUNC:
			func_name = "hge.framefunc";
			break;
		case HGE_RENDERFUNC:
			func_name = "hge.renderfunc";
			break;
		case HGE_FOCUSLOSTFUNC:
			func_name = "hge.focuslostfunc";
			break;
		case HGE_FOCUSGAINFUNC:
			func_name = "hge.focusgainfunc";
			break;
		case HGE_GFXRESTOREFUNC:
			func_name = "hge.gfxrestorefunc";
			break;
		case HGE_EXITFUNC:
			func_name = "hge.exitfunc";
			break;
		default:
			error(L, "function callback not implemented");
			return;
	}

	lua_getfield(L, LUA_REGISTRYINDEX, func_name.c_str());
}

int system_set_state(lua_State *L) {
	HGE *h = hge_check(L);

	if(lua_gettop(L) != 3 || !lua_isnumber(L, 2)) {
		DEBUG_ARGS(L, "got: set_state");
		error(L, "Expected three arguments: type(hge), number(state), value");
	}

	int state = lua_tointeger(L, 2);

	switch(lua_type(L, 3)) {
		case LUA_TNUMBER:
			{
				hgeIntState is = (hgeIntState)state;
				if(is != state) {
					error(L, "Invalid int state");
				}

				lua_Integer i = lua_tointeger(L, 3);

				h->System_SetState(is, (int)i);
			}
			break;
		case LUA_TSTRING:
			{
				hgeStringState ss = (hgeStringState)state;
				if(ss != state) {
					error(L, "Invalid string state");
				}

				const char *s = lua_tostring(L, 3);

				h->System_SetState(ss, s);
			}
			break;
		case LUA_TBOOLEAN:
			{
				hgeBoolState bs = (hgeBoolState)state;
				if(bs != state) {
					error(L, "Invalid bool state");
				}

				bool b = lua_toboolean(L, 3);

				h->System_SetState(bs, b);
			}
			break;
		case LUA_TFUNCTION:
			system_set_state_func(L, h);
			break;
		default:
			error(L, "Unsupported typed passed as third argument to set_state");
			break;
	}

	return 0;
}

int system_get_state(lua_State *L) {
	HGE *h = hge_check(L);

	if(lua_gettop(L) != 2 || !lua_isnumber(L, 2)) {
		error(L, "A state constant must be specified");
	}

	int state = lua_tonumber(L, 2);

	switch(state) {
		case HGE_WINDOWED:
		case HGE_ZBUFFER:
		case HGE_TEXTUREFILTER:
		case HGE_USESOUND:
		case HGE_DONTSUSPEND:
		case HGE_HIDEMOUSE:
		case HGE_SHOWSPLASH:
			lua_pushboolean(L, h->System_GetState((hgeBoolState)state));
			break;

		case HGE_SCREENWIDTH:
		case HGE_SCREENHEIGHT:
		case HGE_SCREENBPP:
		case HGE_SAMPLERATE:
		case HGE_FXVOLUME:
		case HGE_MUSVOLUME:
		case HGE_STREAMVOLUME:
		case HGE_FPS:
		case HGE_POWERSTATUS:
		case HGE_ORIGSCREENWIDTH:
		case HGE_ORIGSCREENHEIGHT:
			lua_pushinteger(L, h->System_GetState((hgeIntState)state));
			break;

		case HGE_ICON:
		case HGE_TITLE:
		case HGE_INIFILE:
		case HGE_LOGFILE:
			lua_pushstring(L, h->System_GetState((hgeStringState)state));
			break;

		case HGE_FRAMEFUNC:
		case HGE_RENDERFUNC:
		case HGE_FOCUSLOSTFUNC:
		case HGE_FOCUSGAINFUNC:
		case HGE_GFXRESTOREFUNC:
		case HGE_EXITFUNC:
			system_get_state_func(L, h);
			break;
		default:
			error(L, "Unsupported type for get_state");
			break;
	}

	return 1;
}

luaL_Reg hge_reg[] = {
	{ "initiate", system_initiate },
	{ "shutdown", system_shutdown },
	{ "start", system_start },
	{ "get_error_message", system_get_error_message },
	{ "log", system_log },
	{ "launch", system_launch },
	{ "snapshot", system_snapshot },
	{ "set_state", system_set_state },
	{ "get_state", system_get_state },
	NULL,
};

int hge_tostring(lua_State *L) {
	lua_pushstring(L, HGE_TYPE);

	return 1;
}

/* t* HGE->Create(int ver); */
int hge_create(lua_State *L) {
	HGE **hge = (HGE **) lua_newuserdata(L, sizeof(HGE **));
	*hge = hgeCreate(HGE_VERSION);

	add_garbage(L, "hge.hge", system_free);
	add_tostring(L, "hge.hge", hge_tostring);

	luaL_newmetatable(L, "hge.hge");

	register_resource(L);
	register_ini(L);
	register_random(L);
	register_timer(L);
	register_effect(L);
	register_music(L);
	register_stream(L);
	register_channel(L);
	register_input(L);
	register_gfx(L);
	register_target(L);
	register_texture(L);

	lua_setmetatable(L, -2);

	return 1;
}

void register_hge(lua_State *L) {
	// required for the callback functions
	global_state = L;

	lua_newtable(L);
	// Add the new function to the table
	add_function(L, "new", hge_create);

	// Setup the hge metatable for the userdata
	luaL_newmetatable(L, "hge.hge");
	// push the metatable
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index"); // metatable[__index] = metatable
	luaL_register(L, NULL, hge_reg);

	/*
	register_resource(L);
	register_ini(L);
	register_random(L);
	register_timer(L);
	register_effect(L);
	register_music(L);
	register_stream(L);
	register_channel(L);
	register_input(L);
	register_gfx(L);
	register_target(L);
	register_texture(L);
	*/

	lua_setmetatable(L, -2); // setmetatable(hge, metatable)

	add_hge_constants(L);
	// Pop's the hge table off the stack
	lua_setglobal(L, "hge");
}

/* void Resource_Free(void *res); */
int resource_free(lua_State *L) {
	return 0;
}

/* bool Resource_AttachPack(const char *filename, const char *password); */
int resource_attach_pack(lua_State *L) {
	return 0;
}

/* void Resource_RemovePack(const char *filename); */
int resource_remove_pack(lua_State *L) {
	return 0;
}

/* void Resource_RemoveAllPacks(); */
int resource_remove_all_packs(lua_State *L) {
	return 0;
}

/* char* Resource_MakePath(const char *filename); */
int resource_make_path(lua_State *L) {
	return 0;
}

/* char* Resource_EnumFiles(const char *wildcard); */
int resource_enum_files(lua_State *L) {
	return 0;
}

/* char* Resource_EnumFolders(const char *wildcard); */
int resource_enum_folders(lua_State *L) {
	return 0;
}

luaL_Reg resource_reg[] = {
	{ "free", resource_free },
	{ "attach_pack", resource_attach_pack },
	{ "remove_pack", resource_remove_pack },
	{ "remove_all_packs", resource_remove_all_packs },
	{ "make_path" , resource_make_path },
	{ "enume_files", resource_enum_files },
	{ "enum_folders", resource_enum_folders },
	NULL,
};

/* void* Resource_Load(const char *filename, DWORD *size); */
int resource_load(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, resource_reg);

	add_garbage(L, "hge.resource", resource_free);

	return 1;
}

void register_resource(lua_State *L) {
	lua_pushstring(L, "resource");
	lua_newtable(L);

	add_function(L, "new", resource_load);

	lua_settable(L, -3);
}

/* void Ini_SetInt(const char *section, const char *name, int value); */
/* void Ini_SetFloat(const char *section, const char *name, float value); */
/* void Ini_SetString(const char *section, const char *name, const char *value); */
int ini_set(lua_State *L) {
	HGE *h = hge_check(L);
	if(!lua_isstring(L, 2) || !lua_isstring(L, 3)) {
		DEBUG_ARGS(L, "ini:set");
		error(L, "Expected section, name, value");
		return 0;
	}

	const char *section = lua_tostring(L, 2);
	const char *name = lua_tostring(L, 3);
	switch(lua_type(L, 4)) {
		case LUA_TNUMBER:
			{
				bool is_int = true;
				if(lua_isboolean(L, 5)) {
					is_int = lua_toboolean(L, 5);
				}
				if(is_int) {
					h->Ini_SetInt(section, name, lua_tointeger(L, 4));
				} else {
					h->Ini_SetFloat(section, name, lua_tonumber(L, 4));
				}
			}
			break;

		case LUA_TSTRING:
			h->Ini_SetString(section, name, lua_tostring(L, 4));
			break;

		default:
			DEBUG_ARGS(L, "ini:set");
			error(L, "Expected string, string, (number|string), [bool:is_int=true]");
			return 0;
	}

	return 0;
}

/* int Ini_GetInt(const char *section, const char *name, int def_val); */
/* float Ini_GetFloat(const char *section, const char *name, float def_val); */
/* char* Ini_GetString(const char *section, const char *name, const char *def_val); */
int ini_get(lua_State *L) {
	HGE *h = hge_check(L);

	if(!lua_isstring(L, 2) || !lua_isstring(L, 3)) {
		DEBUG_ARGS(L, "ini:get");
		error(L, "Expected section, name, default_value");
		return 0;
	}

	const char *section = lua_tostring(L, 2);
	const char *name = lua_tostring(L, 3);
	switch(lua_type(L, 4)) {
		case LUA_TNUMBER:
			{
				bool is_int = true;
				if(lua_isboolean(L, 5)) {
					is_int = lua_toboolean(L, 5);
				}
				if(is_int) {
					lua_pushinteger(L, h->Ini_GetInt(section, name, lua_tointeger(L, 4)));
				} else {
					lua_pushnumber(L, h->Ini_GetFloat(section, name, lua_tonumber(L, 4)));
				}
			}
			break;

		case LUA_TSTRING:
			lua_pushstring(L, h->Ini_GetString(section, name, lua_tostring(L, 4)));
			break;

		default:
			DEBUG_ARGS(L, "ini:get");
			error(L, "Expected string, string, (number|string), [bool:is_int=true]");
			return 0;
	}

	return 1;
}

luaL_Reg ini_reg[] = {
	{ "get", ini_get},
	{ "set", ini_set},
	NULL,
};

void register_ini(lua_State *L) {
	REGISTER_HGE_USERDATA(ini);
}

/* void Random_Seed(int seed=0); */
int random_seed(lua_State *L) {
	HGE *h = hge_check(L);

	int seed = 0;
	if(lua_isnumber(L, 2)) {
		seed = lua_tointeger(L, 2);
	}

	h->Random_Seed(seed);

	return 0;
}

/* int Random_Int(int min, int max); */
int random_int(lua_State *L) {
	HGE *h = hge_check(L);

	if(!lua_isnumber(L, 2) || !lua_isnumber(L, 3)) {
		error(L, "Expected min & max to be integers");
		return 0;
	}

	int min, max;
	min = lua_tointeger(L, 2);
	max = lua_tointeger(L, 3);
	int i = h->Random_Int(min, max);
	lua_pushinteger(L, i);

	return 1;
}

/* float Random_Float(float min, float max); */
int random_float(lua_State *L) {
	HGE *h = hge_check(L);

	if(!lua_isnumber(L, 2) || !lua_isnumber(L, 3)) {
		error(L, "Expected min & max to be floats");
		return 0;
	}

	float min, max;
	min = lua_tonumber(L, 2);
	max = lua_tonumber(L, 3);
	float i = h->Random_Float(min, max);
	lua_pushnumber(L, i);

	return 1;
}

luaL_Reg random_reg[] = {
	{ "seed", random_seed },
	{ "int", random_int },
	{ "float", random_float },
	NULL,
};

void register_random(lua_State *L) {
	REGISTER_HGE_USERDATA(random);
}

/* float Timer_GetTime(); */
int timer_get_time(lua_State *L) {
	HGE *h = hge_check(L);

	lua_pushnumber(L, h->Timer_GetTime());

	return 1;
}

/* float Timer_GetDelta(); */
int timer_get_delta(lua_State *L) {
	HGE *h = hge_check(L);

	lua_pushnumber(L, h->Timer_GetDelta());

	return 1;
}

/* int Timer_GetFPS(); */
int timer_get_fps(lua_State *L) {
	HGE *h = hge_check(L);

	lua_pushnumber(L, h->Timer_GetFPS());

	return 1;
}

luaL_Reg timer_reg[] = {
	{ "time", timer_get_time },
	{ "delta", timer_get_delta },
	{ "fps", timer_get_fps },
	NULL,
};

void register_timer(lua_State *L) {
	REGISTER_HGE_USERDATA(timer);
}

/* void Effect_Free(HEFFECT eff); */
int effect_free(lua_State *L) {
	return 0;
}

/* HCHANNEL Effect_Play(HEFFECT eff); */
int effect_play(lua_State *L) {
	return 0;
}

/* HCHANNEL Effect_PlayEx(HEFFECT eff, int volume, int pan, float pitch, bool loop); */
int effect_play_ex(lua_State *L) {
	return 0;
}

luaL_Reg effect_reg[] = {
	{ "free", effect_free },
	{ "play", effect_play },
	{ "play_ex", effect_play_ex },
	NULL,
};

/* HEFFECT Effect_Load(const char *filename, DWORD size); */
int effect_load(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, effect_reg);

	add_garbage(L, "hge.effect", effect_free);

	return 1;
}

void register_effect(lua_State *L) {
	lua_pushstring(L, "effect");
	lua_newtable(L);

	add_function(L, "new", effect_load);

	lua_settable(L, -3);
}

/* void Music_Free(HMUSIC mus); */
int music_free(lua_State *L) {
	return 0;
}

/* HCHANNEL Music_Play(HMUSIC mus, bool loop, int volume, int order, int row); */
int music_play(lua_State *L) {
	return 0;
}

/* void Music_SetAmplification(HMUSIC music, int ampl); */
int music_set_amplification(lua_State *L) {
	return 0;
}

/* int Music_GetAmplification(HMUSIC music); */
int music_get_amplification(lua_State *L) {
	return 0;
}

/* int Music_GetLength(HMUSIC music); */
int music_get_length(lua_State *L) {
	return 0;
}

/* void Music_SetPos(HMUSIC music, int order, int row); */
int music_set_pos(lua_State *L) {
	return 0;
}

/* bool Music_GetPos(HMUSIC music, int *order, int *row); */
int music_get_pos(lua_State *L) {
	return 0;
}

/* void Music_SetInstrVolume(HMUSIC music, int instr, int volume); */
int music_set_instr_volume(lua_State *L) {
	return 0;
}

/* int Music_GetInstrVolume(HMUSIC music, int instr); */
int music_get_instr_volume(lua_State *L) {
	return 0;
}

/* void Music_SetChannelVolume(HMUSIC music, int channel, int volume); */
int music_set_channel_volume(lua_State *L) {
	return 0;
}

/* int Music_GetChannelVolume(HMUSIC music, int channel); */
int music_get_channel_volume(lua_State *L) {
	return 0;
}

luaL_Reg music_reg[] = {
	{ "free", music_free },
	{ "play", music_play },
	{ "set_amplification", music_set_amplification },
	{ "get_amplification", music_get_amplification },
	{ "get_length", music_get_length },
	{ "set_pos", music_set_pos },
	{ "get_pos", music_get_pos },
	{ "set_instr_volume", music_set_instr_volume },
	{ "get_instr_volume", music_get_instr_volume },
	{ "set_channel_volume", music_set_channel_volume },
	{ "get_channel_volume", music_get_channel_volume },
	NULL,
};

/* HMUSIC Music_Load(const char *filename, DWORD size); */
int music_load(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, music_reg);

	add_garbage(L, "hge.music", music_free);

	return 1;
}

void register_music(lua_State *L) {
	lua_pushstring(L, "music");
	lua_newtable(L);

	add_function(L, "new", music_load);

	lua_settable(L, -3);
}

/* void Stream_Free(HSTREAM stream); */
int stream_free(lua_State *L) {
	return 0;
}

/* HCHANNEL Stream_Play(HSTREAM stream, bool loop, int volume); */
int stream_play(lua_State *L) {
	return 0;
}

luaL_Reg stream_reg[] = {
	{ "free", stream_free },
	{ "play", stream_play },
	NULL,
};

/* HSTREAM Stream_Load(const char *filename, DWORD size); */
int stream_load(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, stream_reg);

	add_garbage(L, "hge.stream", stream_free);

	return 1;
}

void register_stream(lua_State *L) {
	lua_pushstring(L, "stream");
	lua_newtable(L);

	add_function(L, "new", stream_load);
	lua_settable(L, -3);
}

/* void Channel_SetPanning(HCHANNEL chn, int pan); */
int channel_set_panning(lua_State *L) {
	return 0;
}

/* void Channel_SetVolume(HCHANNEL chn, int volume); */
int channel_set_volume(lua_State *L) {
	return 0;
}

/* void Channel_SetPitch(HCHANNEL chn, float pitch); */
int channel_set_pitch(lua_State *L) {
	return 0;
}

/* void Channel_Pause(HCHANNEL chn); */
int channel_pause(lua_State *L) {
	return 0;
}

/* void Channel_Resume(HCHANNEL chn); */
int channel_resume(lua_State *L) {
	return 0;
}

/* void Channel_Stop(HCHANNEL chn); */
int channel_stop(lua_State *L) {
	return 0;
}

/* void Channel_PauseAll(); */
int channel_pause_all(lua_State *L) {
	return 0;
}

/* void Channel_ResumeAll(); */
int channel_resume_all(lua_State *L) {
	return 0;
}

/* void Channel_StopAll(); */
int channel_stop_all(lua_State *L) {
	return 0;
}

/* bool Channel_IsPlaying(HCHANNEL chn); */
int channel_is_playing(lua_State *L) {
	return 0;
}

/* float Channel_GetLength(HCHANNEL chn); */
int channel_get_length(lua_State *L) {
	return 0;
}

/* float Channel_GetPos(HCHANNEL chn); */
int channel_get_pos(lua_State *L) {
	return 0;
}

/* void Channel_SetPos(HCHANNEL chn, float fSeconds); */
int channel_set_pos(lua_State *L) {
	return 0;
}

/* void Channel_SlideTo(HCHANNEL channel, float time, int volume, int pan, float pitch); */
int channel_slide_to(lua_State *L) {
	return 0;
}

/* bool Channel_IsSliding(HCHANNEL channel); */
int channel_is_sliding(lua_State *L) {
	return 0;
}

luaL_Reg channel_reg[] = {
	{ "set_panning", channel_set_panning },
	{ "set_volume", channel_set_volume },
	{ "set_pitch", channel_set_pitch },
	{ "pause", channel_pause },
	{ "resume", channel_resume },
	{ "stop", channel_stop },
	{ "pause_all", channel_pause_all },
	{ "resume_all", channel_resume_all },
	{ "stop_all", channel_stop_all },
	{ "is_playing", channel_is_playing },
	{ "get_length", channel_get_length },
	{ "get_pos", channel_get_pos },
	{ "set_pos", channel_set_pos },
	{ "slide_to", channel_slide_to },
	{ "is_sliding", channel_is_sliding },
	NULL,
};

void register_channel(lua_State *L) {
	lua_pushstring(L, "channel");
	lua_newtable(L);
	luaL_register(L, NULL, channel_reg);
	lua_settable(L, -3);
}

/* void Input_GetMousePos(float *x, float *y); */
int input_get_mouse_pos(lua_State *L) {
	HGE *h = hge_check(L);

	float x, y;
	h->Input_GetMousePos(&x, &y);

	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	return 2;
}

/* void Input_SetMousePos(float x, float y); */
int input_set_mouse_pos(lua_State *L) {
	HGE *h = hge_check(L);

	if(!lua_isnumber(L, 2) || !lua_isnumber(L, 3)) {
		DEBUG_ARGS(L, "set_mouse_pos");
		error(L, "Expected x, y");
		return 0;
	}

	float x, y;
	x = lua_tonumber(L, 2);
	y = lua_tonumber(L, 3);
	h->Input_SetMousePos(x, y);

	return 0;
}

/* int Input_GetMouseWheel(); */
int input_get_mouse_wheel(lua_State *L) {
	HGE *h = hge_check(L);

	lua_pushinteger(L, h->Input_GetMouseWheel());

	return 1;
}

/* bool Input_IsMouseOver(); */
int input_is_mouse_over(lua_State *L) {
	HGE *h = hge_check(L);

	lua_pushboolean(L, h->Input_IsMouseOver());

	return 1;
}

/* bool Input_KeyDown(int key); */
int input_key_down(lua_State *L) {
	HGE *h = hge_check(L);

	if(!lua_isnumber(L, 2)) {
		DEBUG_ARGS(L, "key_down");
		error(L, "Expected integer key");
		return 0;
	}

	int key = lua_tointeger(L, 2);
	lua_pushboolean(L, h->Input_KeyDown(key));

	return 1;
}

/* bool Input_KeyUp(int key); */
int input_key_up(lua_State *L) {
	HGE *h = hge_check(L);

	if(!lua_isnumber(L, 2)) {
		DEBUG_ARGS(L, "key_up");
		error(L, "Expected integer key");
		return 0;
	}

	int key = lua_tointeger(L, 2);
	lua_pushboolean(L, h->Input_KeyUp(key));

	return 1;
}

/* bool Input_GetKeyState(int key); */
int input_get_key_state(lua_State *L) {
	HGE *h = hge_check(L);

	if(!lua_isnumber(L, 2)) {
		DEBUG_ARGS(L, "get_key_state");
		error(L, "Expected integer key");
		return 0;
	}

	int key = lua_tointeger(L, 2);
	lua_pushboolean(L, h->Input_GetKeyState(key));

	return 1;
}

/* const char* Input_GetKeyName(int key); */
int input_get_key_name(lua_State *L) {
	HGE *h = hge_check(L);

	if(!lua_isnumber(L, 2)) {
		DEBUG_ARGS(L, "get_key_name");
		error(L, "Expected integer key");
		return 0;
	}

	int key = lua_tointeger(L, 2);
	lua_pushstring(L, h->Input_GetKeyName(key));

	return 1;
}

/* int Input_GetKey(); */
int input_get_key(lua_State *L) {
	HGE *h = hge_check(L);

	lua_pushnumber(L, h->Input_GetKey());

	return 1;
}

/* int Input_GetChar(); */
int input_get_char(lua_State *L) {
	HGE *h = hge_check(L);

	lua_pushnumber(L, h->Input_GetChar());

	return 1;
}

/* bool Input_GetEvent(HGE->InputEvent_t *event); */
int input_get_event(lua_State *L) {
	HGE *h = hge_check(L);

	hgeInputEvent e;
	bool r = h->Input_GetEvent(&e);
	lua_pushboolean(L, r);
	if(r) {
		lua_newtable(L);
		lua_pushinteger(L, e.type);
		lua_setfield(L, -2, "type");
		lua_pushinteger(L, e.key);
		lua_setfield(L, -2, "key");
		lua_pushinteger(L, e.flags);
		lua_setfield(L, -2, "flags");
		lua_pushinteger(L, e.chr);
		lua_setfield(L, -2, "character");
		lua_pushinteger(L, e.wheel);
		lua_setfield(L, -2, "wheel");
		lua_pushnumber(L, e.x);
		lua_setfield(L, -2, "x");
		lua_pushnumber(L, e.y);
		lua_setfield(L, -2, "y");
		return 2;
	}

	return 1;
}

luaL_Reg input_reg[] = {
	{ "get_mouse_pos", input_get_mouse_pos },
	{ "set_mouse_pos", input_set_mouse_pos },
	{ "get_mouse_wheel", input_get_mouse_wheel },
	{ "is_mouse_over", input_is_mouse_over },
	{ "key_down", input_key_down },
	{ "key_up", input_key_up },
	{ "get_key_state", input_get_key_state },
	{ "get_key_name", input_get_key_name },
	{ "get_key", input_get_key },
	{ "get_char", input_get_char },
	{ "get_event", input_get_event },
	NULL,
};

void register_input(lua_State *L) {
	REGISTER_HGE_USERDATA(input);
}

/* bool Gfx_BeginScene(HTARGET target = 0); */
int gfx_begin_scene(lua_State *L) {
	HGE *h = hge_check(L);

	lua_settop(L, 2);
	HTARGET *target = texture_check(L);

	lua_pushboolean(L, h->Gfx_BeginScene(*target));

	return 1;
}

/* void Gfx_EndScene(); */
int gfx_end_scene(lua_State *L) {
	HGE *h = hge_check(L);

	h->Gfx_EndScene();

	return 0;
}

/* void Gfx_Clear(DWORD color); */
int gfx_clear(lua_State *L) {
	HGE *h = hge_check(L);

	DWORD color = 0;
	if(lua_isnumber(L, 2)) {
		color = lua_tointeger(L, 2);
	}

	h->Gfx_Clear(color);

	return 0;
}


/* void Gfx_RenderLine(float x1, float y1, float x2, float y2, DWORD color=0xFFFFFFFF, float z=0.5f); */
int gfx_render_line(lua_State *L) {
	HGE *h = hge_check(L);

	float p[4], z = 0.5f;
	DWORD color = 0xFFFFFFFF;

	if(lua_gettop(L) < 5) {
		DEBUG_ARGS(L, "render_line");
		error(L, "Expected x1, y1, x2, y2");
		return 0;
	}

	for(int i = 0; i < 4 && i <= lua_gettop(L); i++) {
		if(!lua_isnumber(L, 2+i)) {
			DEBUG_ARGS(L, "render_line");
			error(L, "Expected x1, y1, x2, y2");
			return 0;
		}

		p[i] = lua_tonumber(L, 2+i);
	}
	if(lua_isnumber(L, 6)) {
		color = lua_tointeger(L, 6);
	}
	if(lua_isnumber(L, 7)) {
		z = lua_tonumber(L, 7);
	}

	h->Gfx_RenderLine(p[0], p[1], p[2], p[3], color, z);

	return 0;
}

/* void Gfx_RenderTriple(const HGE->Triple_t *triple); */
int gfx_render_triple(lua_State *L) {
	return 0;
}

/* void Gfx_RenderQuad(const HGE->Quad_t *quad); */
int gfx_render_quad(lua_State *L) {
	return 0;
}

/* Vertex_t* HGE->Gfx_StartBatch(int prim_type, HTEXTURE tex, int blend, int *max_prim); */
int gfx_start_batch(lua_State *L) {
	return 0;
}

/* void Gfx_FinishBatch(int nprim); */
int gfx_finish_batch(lua_State *L) {
	HGE *h = hge_check(L);

	if(!lua_tonumber(L, 2)) {
		DEBUG_ARGS(L, "finish_batch");
		error(L, "Expected nprim");
		return 0;
	}

	int nprim = lua_tointeger(L, 2);
	h->Gfx_FinishBatch(nprim);

	return 0;
}

/* void Gfx_SetClipping(int x, int y, int w, int h); */
int gfx_set_clipping(lua_State *L) {
	HGE *h = hge_check(L);

	int r[4];
	if(lua_gettop(L) < 5) {
		DEBUG_ARGS(L, "set_clipping");
		error(L, "Expected x, y, w, h");
		return 0;
	}

	for(int i = 0; i < 4 && i <= lua_gettop(L); i++) {
		if(!lua_isnumber(L, 2+i)) {
			DEBUG_ARGS(L, "set_clipping");
			error(L, "Expected x, y, w, h");
			return 0;
		}
		r[i] = lua_tointeger(L, 2+i);
	}

	h->Gfx_SetClipping(r[0], r[1], r[2], r[3]);

	return 0;
}

/* void Gfx_SetTransform(float x, float y, float dx, float dy, float rot, float hscale, float vscale); */
int gfx_set_transform(lua_State *L) {
	HGE *h = hge_check(L);

	float t[7];
	for(int i = 0; i < 7 && i <= lua_gettop(L); i++) {
		if(lua_isnumber(L, 2+i)) {
			t[i] = lua_tonumber(L, 2+i);
		} else {
			t[i] = 0;
		}
	}

	h->Gfx_SetTransform(t[0], t[1], t[2], t[3], t[4], t[5], t[6]);

	return 0;
}

luaL_Reg gfx_reg[] = {
	{ "begin_scene", gfx_begin_scene },
	{ "end_scene", gfx_end_scene },
	{ "clear", gfx_clear },
	{ "render_line", gfx_render_line },
	{ "render_triple", gfx_render_triple },
	{ "render_quad", gfx_render_quad },
	{ "start_batch", gfx_start_batch },
	{ "finish_batch", gfx_finish_batch },
	{ "set_clipping", gfx_set_clipping },
	{ "set_transform", gfx_set_transform },
	NULL,
};

void register_gfx(lua_State *L) {
	REGISTER_HGE_USERDATA(gfx);
}

HTARGET *target_check(lua_State *L) {
	CHECK_USERDATA(HTARGET);
}

/* void Target_Free(HTARGET target); */
int target_free(lua_State *L) {
	HTARGET *target = target_check(L);

	HGE *h = hgeCreate(HGE_VERSION);
	h->Target_Free(*target);

	return 0;
}

/* HTEXTURE Target_GetTexture(HTARGET target); */
int target_get_texture(lua_State *L) {
	HTARGET *target = target_check(L);

	HGE *h = hgeCreate(HGE_VERSION);
	HTEXTURE tex = h->Target_GetTexture(*target);

	lua_pushlightuserdata(L, &tex);
	luaL_newmetatable(L, "hge.texture_instance");
	lua_setmetatable(L, -2);

	return 1;
}

luaL_Reg target_interface_reg[] = {
	{ "get_texture", target_get_texture },
	NULL,
};

/* HTARGET Target_Create(int width, int height, bool zbuffer); */
int target_create(lua_State *L) {
	HGE *h = hge_check(L);

	if(!lua_isnumber(L, 2) || !lua_isnumber(L, 3) || !lua_isboolean(L, 4)) {
		DEBUG_ARGS(L, "target.new");
		error(L, "Expected width, height, zbuffer");
		return 0;
	}

	int width = lua_tointeger(L, 2);
	int height = lua_tointeger(L, 3);
	bool zbuffer = lua_toboolean(L, 4);

	HTARGET *target = (HTARGET *)lua_newuserdata(L, sizeof(HTARGET *));
	*target = h->Target_Create(width, height, zbuffer);

	luaL_newmetatable(L, "hge.target");
	lua_setmetatable(L, -2);

	return 1;
}

luaL_Reg target_reg[] = {
	{ "new", target_create },
	NULL,
};

int target_tostring(lua_State *L) {
	lua_pushstring(L, HTARGET_TYPE);

	return 1;
}

void register_target(lua_State *L) {
	REGISTER_HGE_USERDATA(target);

	// Setup the target metatable
	luaL_newmetatable(L, "hge.target");
	lua_pushvalue(L, -1);
	lua_setfield(L, -1, "__index");

	luaL_register(L, NULL, target_interface_reg);

	add_garbage(L, "hge.target", target_free);
	add_tostring(L, "hge.target", target_tostring);

	lua_pop(L, 1);
}

inline HTEXTURE *texture_check(lua_State *L) {
	CHECK_USERDATA(HTEXTURE);
	if(!lua_isuserdata(L, 1)) {
		error(L, "Expected userdata of type " HTEXTURE_TYPE);
		return NULL;
	}
	HTEXTURE *tex = (HTEXTURE *)lua_touserdata(L, 1);
	if(tex == NULL) {
		error(L, "Unable to get userdata of type " HTEXTURE_TYPE);
		return NULL;
	}

	return tex;
}

int texture_tostring(lua_State *L) {
	lua_pushstring(L, HTEXTURE_TYPE);
	return 1;
}

/* void Texture_Free(HTEXTURE tex); */
int texture_free(lua_State *L) {
	HGE *h = hgeCreate(HGE_VERSION);
	HTEXTURE *tex = texture_check(L);
	h->Texture_Free(*tex);
	h->Release();

	return 0;
}

/* int Texture_GetWidth(HTEXTURE tex, bool bOriginal); */
int texture_get_width(lua_State *L) {
	HTEXTURE *tex = texture_check(L);

	bool original = true;
	if(lua_isboolean(L, 2)) {
		original = lua_toboolean(L, 2);
	}

	HGE *h = hgeCreate(HGE_VERSION);
	lua_pushnumber(L, h->Texture_GetWidth(*tex, original));

	return 1;
}

/* int Texture_GetHeight(HTEXTURE tex, bool bOriginal); */
int texture_get_height(lua_State *L) {
	HTEXTURE *tex = texture_check(L);

	bool original = true;
	if(lua_isboolean(L, 2)) {
		original = lua_toboolean(L, 2);
	}

	HGE *h = hgeCreate(HGE_VERSION);
	lua_pushnumber(L, h->Texture_GetHeight(*tex, original));

	return 1;
}

/* DWORD* Texture_Lock(HTEXTURE tex, bool bReadOnly, int left, int top, int width, int height); */
int texture_lock(lua_State *L) {
	return 0;
}

/* void Texture_Unlock(HTEXTURE tex); */
int texture_unlock(lua_State *L) {
	HTEXTURE *tex = texture_check(L);
	HGE *h = hgeCreate(HGE_VERSION);

	h->Texture_Unlock(*tex);

	return 0;
}

luaL_Reg texture_instance_reg[] = {
	{ "get_width", texture_get_width },
	{ "get_height", texture_get_height },
	{ "lock", texture_lock },
	{ "unlock", texture_unlock },
	NULL,
};

/* Leaves an new texture instance table on the top of the stack */
HTEXTURE *texture_new(lua_State *L) {
	HTEXTURE *tex = (HTEXTURE *)lua_newuserdata(L, sizeof(HTEXTURE *));

	luaL_newmetatable(L, "hge.texture_instance");
	lua_setmetatable(L, -2);

	return tex;
}

/* HTEXTURE Texture_Create(int width, int height); */
int texture_create(lua_State *L) {
	HGE *h = hge_check(L);
	int width, height;

	if(!lua_isnumber(L, 2) || !lua_isnumber(L, 3)) {
		DEBUG_ARGS(L, "texture.new");
		error(L, "Expecetd width, height");
		return 0;
	}

	width = lua_tointeger(L, 2);
	height = lua_tointeger(L, 3);

	HTEXTURE *tex = texture_new(L);
	*tex = h->Texture_Create(width, height);

	return 1;
}

/* HTEXTURE Texture_Load(const char *filename, DWORD size, bool bMipmap); */
int texture_load(lua_State *L) {
	HGE *h = hge_check(L);

	if(!lua_isstring(L, 2) || !lua_isnumber(L, 3) || !lua_isboolean(L, 4)) {
		DEBUG_ARGS(L, "texture.load");
		error(L, "Expected filename, size, is_mipmap");
		return 0;
	}

	const char *filename = lua_tostring(L, 2);
	DWORD size = lua_tointeger(L, 3);
	bool mipmap = lua_toboolean(L, 4);

	HTEXTURE *tex = texture_new(L);
	*tex = h->Texture_Load(filename, size, mipmap);

	return 1;
}

luaL_Reg texture_reg[] = {
	{ "new", texture_create },
	{ "load", texture_load },
	NULL,
};

void register_texture(lua_State *L) {
	// Setup the texture_instance metatable
	luaL_newmetatable(L, "hge.texture_instance");
	lua_pushvalue(L, -1);
	lua_setfield(L, -1, "__index");

	add_garbage(L, "hge.texture_instance", texture_free);
	add_tostring(L, "hge.texture_instance", texture_tostring);

	luaL_register(L, NULL, texture_instance_reg);
	lua_pop(L, 1);

	REGISTER_HGE_USERDATA(texture);
}

extern "C" void luaopen_hge(lua_State *L) {
	register_hge(L);
}
