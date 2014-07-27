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

#define DEBUG_STACK(L) do { printf("stack: %s:%d => %d\n", __FILE__, __LINE__, lua_gettop(L)); } while(0)

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

#define add_garbage(L, m, f) add_meta_function(L, m, "__gc", f)
#define add_index(L, m, f) add_meta_function(L, m, "__index", f)
#define add_newindex(L, m, f) add_meta_function(L, m, "__newindex", f)
#define add_tostring(L, m, f) add_meta_function(L, m, "__tostring", f)

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
	add_constant(L, "texturefilter", HGE_TEXTUREFILTER);
	add_constant(L, "usesound", HGE_USESOUND);
	add_constant(L, "dontsuspend", HGE_DONTSUSPEND);
	add_constant(L, "hidemouse", HGE_HIDEMOUSE);
	add_constant(L, "showsplash", HGE_SHOWSPLASH);
	lua_settable(L, -3);

	lua_pushstring(L, "func");
	lua_newtable(L);
	add_constant(L, "framefunc", HGE_FRAMEFUNC);
	add_constant(L, "renderfunc", HGE_RENDERFUNC);
	add_constant(L, "focuslostfunc", HGE_FOCUSLOSTFUNC);
	add_constant(L, "focusgainfunc", HGE_FOCUSGAINFUNC);
	add_constant(L, "gfxrestorefunc", HGE_GFXRESTOREFUNC);
	add_constant(L, "exitfunc", HGE_EXITFUNC);
	lua_settable(L, -3);

	lua_pushstring(L, "hwnd");
	lua_newtable(L);
	add_constant(L, "hwnd", HGE_HWND);
	add_constant(L, "hwndparent", HGE_HWNDPARENT);
	lua_settable(L, -3);

	lua_pushstring(L, "int");
	lua_newtable(L);
	add_constant(L, "screenwidth", HGE_SCREENWIDTH);
	add_constant(L, "screenheight", HGE_SCREENHEIGHT);
	add_constant(L, "screenbpp", HGE_SCREENBPP);
	add_constant(L, "samplerate", HGE_SAMPLERATE);
	add_constant(L, "fxvolume", HGE_FXVOLUME);
	add_constant(L, "musvolume", HGE_MUSVOLUME);
	add_constant(L, "streamvolume", HGE_STREAMVOLUME);
	add_constant(L, "fps", HGE_FPS);
	add_constant(L, "powerstatus", HGE_POWERSTATUS);
	add_constant(L, "origscreenwidth", HGE_ORIGSCREENWIDTH);
	add_constant(L, "origscreenheight", HGE_ORIGSCREENHEIGHT);
	lua_settable(L, -3);

	lua_pushstring(L, "string");
	lua_newtable(L);
	add_constant(L, "icon", HGE_ICON);
	add_constant(L, "title", HGE_TITLE);
	add_constant(L, "inifile", HGE_INIFILE);
	add_constant(L, "logfile", HGE_LOGFILE);
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

/* Check the first argument is userdata and return it */
HGE *hge_param_check(lua_State *L) {
	if(lua_isuserdata(L, 1) == 0) {
		error(L, "Expected type(hge)");
		return NULL;
	}

	return *((HGE **)lua_touserdata(L, 1));
}

/* check that the first argument is a userdata & make sure it's not free'd */
HGE *hge_check(lua_State *L) {
	HGE *h = hge_param_check(L);

	if(h == NULL) {
		error(L, "Cannot use a free'd type(hge)");
		return NULL;
	}

	return h;
}

/* void HGE->Release(); */
int system_release(lua_State *L) {
	HGE *h = hge_param_check(L);

	if(h != NULL) {
		h->Release();
		h = NULL;
	}
	return 0;
}

/* bool HGE->System_Initiate(); */
int system_initiate(lua_State *L) {
	HGE *h = hge_check(L);

	bool b = h->System_Initiate();

	lua_pushboolean(L, b);

	return 1;
}

/* void HGE->System_Shutdown(); */
int system_shutdown(lua_State *L) {
	HGE *h = hge_check(L);

	h->System_Shutdown();

	return 0;
}

/* bool HGE->System_Start(); */
int system_start(lua_State *L) {
	HGE *h = hge_check(L);

	bool b = h->System_Start();
	lua_pushboolean(L, b);

	return 1;
}

/* const char* HGE->System_GetErrorMessage(); */
int system_get_error_message(lua_State *L) {
	HGE *h = hge_check(L);

	const char *err = h->System_GetErrorMessage();
	lua_pushstring(L, err);

	return 1;
}

/* void HGE->System_Log(const char *format, ...); */
int system_log(lua_State *L) {
	HGE *h = hge_check(L);
	const char *fmt = lua_tostring(L, 2);
	int i;
	for(i = 3; i <= lua_gettop(L); i++);
	return 0;
}

/* bool HGE->System_Launch(const char *url); */
int system_launch(lua_State *L) {
	HGE *h = hge_check(L);

	const char *url = lua_tostring(L, 2);
	h->System_Launch(url);

	return 0;
}

/* void HGE->System_Snapshot(const char *filename); */
int system_snapshot(lua_State *L) {
	HGE *h = hge_check(L);

	const char *filename = lua_tostring(L, 2);
	h->System_Snapshot(filename);

	return 0;
}

/* void HGE->System_SetStateFunc(HGE->FuncState_t state, HGE->Callback value); */
int system_set_state_func(lua_State *L) {
	HGE *h = hge_check(L);
	return 0;
}

/* HGE->Callback HGE->System_GetStateFunc(HGE->FuncState_t state); */
int system_get_state_func(lua_State *L) {
	HGE *h = hge_check(L);
	return 0;
}

int system_set_state(lua_State *L) {
	HGE *h = hge_check(L);

	if(lua_gettop(L) != 3 || !lua_isnumber(L, 2)) {
		error(L, "Expected three arguments: type(hge), number(state), boolean(value)");
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

		default:
			error(L, "Unsupported type for get_state");
	}

	return 1;
}

luaL_Reg hge_reg[] = {
	{ "free", system_release },
	{ "initiate", system_initiate },
	{ "shutdown", system_shutdown },
	{ "start", system_start },
	{ "get_error_message", system_get_error_message },
	{ "log", system_log },
	{ "launch", system_launch },
	{ "snapshot", system_snapshot },
	{ "set_state", system_set_state },
	{ "get_state", system_get_state },
	{ "set_state_func", system_set_state_func },
	{ "get_state_func", system_get_state_func },
	NULL,
};

int hge_tostring(lua_State *L) {
	hge_check(L);
	lua_pushstring(L, "type(hge)");
	return 1;
}

/* HGE->t* HGE->Create(int ver); */
int hge_create(lua_State *L) {
	HGE **hge = (HGE **) lua_newuserdata(L, sizeof(HGE **));
	*hge = hgeCreate(HGE_VERSION);

	add_garbage(L, "hge.hge", system_release);
	add_tostring(L, "hge.hge", hge_tostring);

	return 1;
}

void register_hge(lua_State *L) {
	lua_newtable(L);
	// Add the new function to the table
	add_function(L, "new", hge_create);

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

	// Setup the hge metatable for the userdata
	luaL_newmetatable(L, "hge.hge");
	lua_pushstring(L, "__index");
	// push the metatable
	lua_pushvalue(L, -2);
	lua_settable(L, -3); // metatable[__index] = metatable
	luaL_register(L, NULL, hge_reg);

	lua_setmetatable(L, -2); // setmetatable(hge, metatable)

	add_hge_constants(L);
	// Pop's the hge table off the stack
	lua_setglobal(L, "hge");
}

/* void HGE->Resource_Free(void *res); */
int resource_free(lua_State *L) {
	return 0;
}

/* bool HGE->Resource_AttachPack(const char *filename, const char *password); */
int resource_attach_pack(lua_State *L) {
	return 0;
}

/* void HGE->Resource_RemovePack(const char *filename); */
int resource_remove_pack(lua_State *L) {
	return 0;
}

/* void HGE->Resource_RemoveAllPacks(); */
int resource_remove_all_packs(lua_State *L) {
	return 0;
}

/* char* HGE->Resource_MakePath(const char *filename); */
int resource_make_path(lua_State *L) {
	return 0;
}

/* char* HGE->Resource_EnumFiles(const char *wildcard); */
int resource_enum_files(lua_State *L) {
	return 0;
}

/* char* HGE->Resource_EnumFolders(const char *wildcard); */
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

/* void* HGE->Resource_Load(const char *filename, DWORD *size); */
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

/* void HGE->Ini_SetInt(const char *section, const char *name, int value); */
int ini_set_int(lua_State *L) {
	return 0;
}

/* int HGE->Ini_GetInt(const char *section, const char *name, int def_val); */
int ini_get_int(lua_State *L) {
	return 0;
}

/* void HGE->Ini_SetFloat(const char *section, const char *name, float value); */
int ini_set_float(lua_State *L) {
	return 0;
}

/* float HGE->Ini_GetFloat(const char *section, const char *name, float def_val); */
int ini_get_float(lua_State *L) {
	return 0;
}

/* void HGE->Ini_SetString(const char *section, const char *name, const char *value); */
int ini_set_string(lua_State *L) {
	return 0;
}

/* char* HGE->Ini_GetString(const char *section, const char *name, const char *def_val); */
int ini_get_string(lua_State *L) {
	return 0;
}

luaL_Reg ini_reg[] = {
	{ "get_int", ini_get_int},
	{ "get_float", ini_get_float},
	{ "get_string", ini_get_string},
	{ "set_int", ini_set_int},
	{ "set_float", ini_set_float},
	{ "set_string", ini_set_string},
	NULL,
};

void register_ini(lua_State *L) {
	lua_pushstring(L, "ini");
	lua_newtable(L);

	luaL_register(L, NULL, ini_reg);

	lua_settable(L, -3);
}

/* void HGE->Random_Seed(int seed); */
int random_seed(lua_State *L) {
	return 0;
}

/* int HGE->Random_Int(int min, int max); */
int random_int(lua_State *L) {
	return 0;
}

/* float HGE->Random_Float(float min, float max); */
int random_float(lua_State *L) {
	return 0;
}

luaL_Reg random_reg[] = {
	{ "seed", random_seed },
	{ "int", random_int },
	{ "float", random_float },
	NULL,
};

void register_random(lua_State *L) {
	lua_pushstring(L, "random");
	lua_newtable(L);

	luaL_register(L, NULL, random_reg);

	lua_settable(L, -3);
}

/* float HGE->Timer_GetTime(); */
int timer_get_time(lua_State *L) {
	return 0;
}

/* float HGE->Timer_GetDelta(); */
int timer_get_delta(lua_State *L) {
	return 0;
}

/* int HGE->Timer_GetFPS(); */
int timer_get_fps(lua_State *L) {
	return 0;
}

luaL_Reg timer_reg[] = {
	{ "get_time", timer_get_time },
	{ "get_delta", timer_get_delta },
	{ "get_fps", timer_get_fps },
	NULL,
};

void register_timer(lua_State *L) {
	lua_pushstring(L, "timer");
	lua_newtable(L);
	luaL_register(L, NULL, timer_reg);
	lua_settable(L, -3);
}

/* void HGE->Effect_Free(HEFFECT eff); */
int effect_free(lua_State *L) {
	return 0;
}

/* HCHANNEL HGE->Effect_Play(HEFFECT eff); */
int effect_play(lua_State *L) {
	return 0;
}

/* HCHANNEL HGE->Effect_PlayEx(HEFFECT eff, int volume, int pan, float pitch, bool loop); */
int effect_play_ex(lua_State *L) {
	return 0;
}

luaL_Reg effect_reg[] = {
	{ "free", effect_free },
	{ "play", effect_play },
	{ "play_ex", effect_play_ex },
	NULL,
};

/* HEFFECT HGE->Effect_Load(const char *filename, DWORD size); */
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

/* void HGE->Music_Free(HMUSIC mus); */
int music_free(lua_State *L) {
	return 0;
}

/* HCHANNEL HGE->Music_Play(HMUSIC mus, bool loop, int volume, int order, int row); */
int music_play(lua_State *L) {
	return 0;
}

/* void HGE->Music_SetAmplification(HMUSIC music, int ampl); */
int music_set_amplification(lua_State *L) {
	return 0;
}

/* int HGE->Music_GetAmplification(HMUSIC music); */
int music_get_amplification(lua_State *L) {
	return 0;
}

/* int HGE->Music_GetLength(HMUSIC music); */
int music_get_length(lua_State *L) {
	return 0;
}

/* void HGE->Music_SetPos(HMUSIC music, int order, int row); */
int music_set_pos(lua_State *L) {
	return 0;
}

/* bool HGE->Music_GetPos(HMUSIC music, int *order, int *row); */
int music_get_pos(lua_State *L) {
	return 0;
}

/* void HGE->Music_SetInstrVolume(HMUSIC music, int instr, int volume); */
int music_set_instr_volume(lua_State *L) {
	return 0;
}

/* int HGE->Music_GetInstrVolume(HMUSIC music, int instr); */
int music_get_instr_volume(lua_State *L) {
	return 0;
}

/* void HGE->Music_SetChannelVolume(HMUSIC music, int channel, int volume); */
int music_set_channel_volume(lua_State *L) {
	return 0;
}

/* int HGE->Music_GetChannelVolume(HMUSIC music, int channel); */
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

/* HMUSIC HGE->Music_Load(const char *filename, DWORD size); */
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

/* void HGE->Stream_Free(HSTREAM stream); */
int stream_free(lua_State *L) {
	return 0;
}

/* HCHANNEL HGE->Stream_Play(HSTREAM stream, bool loop, int volume); */
int stream_play(lua_State *L) {
	return 0;
}

luaL_Reg stream_reg[] = {
	{ "free", stream_free },
	{ "play", stream_play },
	NULL,
};

/* HSTREAM HGE->Stream_Load(const char *filename, DWORD size); */
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

/* void HGE->Channel_SetPanning(HCHANNEL chn, int pan); */
int channel_set_panning(lua_State *L) {
	return 0;
}

/* void HGE->Channel_SetVolume(HCHANNEL chn, int volume); */
int channel_set_volume(lua_State *L) {
	return 0;
}

/* void HGE->Channel_SetPitch(HCHANNEL chn, float pitch); */
int channel_set_pitch(lua_State *L) {
	return 0;
}

/* void HGE->Channel_Pause(HCHANNEL chn); */
int channel_pause(lua_State *L) {
	return 0;
}

/* void HGE->Channel_Resume(HCHANNEL chn); */
int channel_resume(lua_State *L) {
	return 0;
}

/* void HGE->Channel_Stop(HCHANNEL chn); */
int channel_stop(lua_State *L) {
	return 0;
}

/* void HGE->Channel_PauseAll(); */
int channel_pause_all(lua_State *L) {
	return 0;
}

/* void HGE->Channel_ResumeAll(); */
int channel_resume_all(lua_State *L) {
	return 0;
}

/* void HGE->Channel_StopAll(); */
int channel_stop_all(lua_State *L) {
	return 0;
}

/* bool HGE->Channel_IsPlaying(HCHANNEL chn); */
int channel_is_playing(lua_State *L) {
	return 0;
}

/* float HGE->Channel_GetLength(HCHANNEL chn); */
int channel_get_length(lua_State *L) {
	return 0;
}

/* float HGE->Channel_GetPos(HCHANNEL chn); */
int channel_get_pos(lua_State *L) {
	return 0;
}

/* void HGE->Channel_SetPos(HCHANNEL chn, float fSeconds); */
int channel_set_pos(lua_State *L) {
	return 0;
}

/* void HGE->Channel_SlideTo(HCHANNEL channel, float time, int volume, int pan, float pitch); */
int channel_slide_to(lua_State *L) {
	return 0;
}

/* bool HGE->Channel_IsSliding(HCHANNEL channel); */
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

/* void HGE->Input_GetMousePos(float *x, float *y); */
int input_get_mouse_pos(lua_State *L) {
	return 0;
}

/* void HGE->Input_SetMousePos(float x, float y); */
int input_set_mouse_pos(lua_State *L) {
	return 0;
}

/* int HGE->Input_GetMouseWheel(); */
int input_get_mouse_wheel(lua_State *L) {
	return 0;
}

/* bool HGE->Input_IsMouseOver(); */
int input_is_mouse_over(lua_State *L) {
	return 0;
}

/* bool HGE->Input_KeyDown(int key); */
int input_key_down(lua_State *L) {
	return 0;
}

/* bool HGE->Input_KeyUp(int key); */
int input_key_up(lua_State *L) {
	return 0;
}

/* bool HGE->Input_GetKeyState(int key); */
int input_get_key_state(lua_State *L) {
	return 0;
}

/* const char* HGE->Input_GetKeyName(int key); */
int input_get_key_name(lua_State *L) {
	return 0;
}

/* int HGE->Input_GetKey(); */
int input_get_key(lua_State *L) {
	return 0;
}

/* int HGE->Input_GetChar(); */
int input_get_char(lua_State *L) {
	return 0;
}

/* bool HGE->Input_GetEvent(HGE->InputEvent_t *event); */
int input_get_event(lua_State *L) {
	return 0;
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
	lua_pushstring(L, "input");
	lua_newtable(L);
	luaL_register(L, NULL, input_reg);
	lua_settable(L, -3);
}

/* bool HGE->Gfx_BeginScene(HTARGET target); */
int gfx_begin_scene(lua_State *L) {
	return 0;
}

/* void HGE->Gfx_EndScene(); */
int gfx_end_scene(lua_State *L) {
	return 0;
}

/* void HGE->Gfx_Clear(DWORD color); */
int gfx_clear(lua_State *L) {
	return 0;
}

/* void HGE->Gfx_RenderLine(float x1, float y1, float x2, float y2, DWORD color, float z); */
int gfx_render_line(lua_State *L) {
	return 0;
}

/* void HGE->Gfx_RenderTriple(const HGE->Triple_t *triple); */
int gfx_render_triple(lua_State *L) {
	return 0;
}

/* void HGE->Gfx_RenderQuad(const HGE->Quad_t *quad); */
int gfx_render_quad(lua_State *L) {
	return 0;
}

/* HGE->Vertex_t* HGE->Gfx_StartBatch(int prim_type, HTEXTURE tex, int blend, int *max_prim); */
int gfx_start_batch(lua_State *L) {
	return 0;
}

/* void HGE->Gfx_FinishBatch(int nprim); */
int gfx_finish_batch(lua_State *L) {
	return 0;
}

/* void HGE->Gfx_SetClipping(int x, int y, int w, int h); */
int gfx_set_clipping(lua_State *L) {
	return 0;
}

/* void HGE->Gfx_SetTransform(float x, float y, float dx, float dy, float rot, float hscale, float vscale); */
int gfx_set_transform(lua_State *L) {
	return 0;
}

luaL_Reg gfx_reg[] = {
	{ "begin_cene", gfx_begin_scene },
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
	lua_pushstring(L, "gfx");
	lua_newtable(L);
	luaL_register(L, NULL, gfx_reg);
	lua_settable(L, -3);
}

/* void HGE->Target_Free(HTARGET target); */
int target_free(lua_State *L) {
	return 0;
}

/* HTEXTURE HGE->Target_GetTexture(HTARGET target); */
int target_get_texture(lua_State *L) {
	return 0;
}

luaL_Reg target_reg[] = {
	{ "free", target_free },
	{ "get_texture", target_get_texture },
	NULL,
};

/* HTARGET HGE->Target_Create(int width, int height, bool zbuffer); */
int target_create(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, target_reg);

	add_garbage(L, "hge.target", target_free);

	return 1;
}

void register_target(lua_State *L) {
	lua_pushstring(L, "target");
	lua_newtable(L);

	add_function(L, "new", target_create);

	lua_settable(L, -3);
}

/* void HGE->Texture_Free(HTEXTURE tex); */
int texture_free(lua_State *L) {
	return 0;
}

/* int HGE->Texture_GetWidth(HTEXTURE tex, bool bOriginal); */
int texture_get_width(lua_State *L) {
	return 0;
}

/* int HGE->Texture_GetHeight(HTEXTURE tex, bool bOriginal); */
int texture_get_height(lua_State *L) {
	return 0;
}

/* DWORD* HGE->Texture_Lock(HTEXTURE tex, bool bReadOnly, int left, int top, int width, int height); */
int texture_lock(lua_State *L) {
	return 0;
}

/* void HGE->Texture_Unlock(HTEXTURE tex); */
int texture_unlock(lua_State *L) {
	return 0;
}

luaL_Reg texture_instance_reg[] = {
	{ "free", texture_free },
	{ "get_width", texture_get_width },
	{ "get_height", texture_get_height },
	{ "lock", texture_lock },
	{ "unlock", texture_unlock },
	NULL,
};

/* Leaves an new texture instance table on the top of the stack */
void texture_new(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, texture_instance_reg);

	add_garbage(L, "hge.texture", texture_free);
}

/* HTEXTURE HGE->Texture_Create(int width, int height); */
int texture_create(lua_State *L) {
	texture_new(L);

	return 1;
}

/* HTEXTURE HGE->Texture_Load(const char *filename, DWORD size, bool bMipmap); */
int texture_load(lua_State *L) {
	texture_new(L);

	return 1;
}

luaL_Reg texture_reg[] = {
	{ "new", texture_create },
	{ "load", texture_load },
	NULL,
};

void register_texture(lua_State *L) {
	lua_pushstring(L, "texture");
	lua_newtable(L);

	luaL_register(L, NULL, texture_reg);

	lua_settable(L, -3);
}

extern "C" void luaopen_hge(lua_State *L) {
	register_hge(L);
}
