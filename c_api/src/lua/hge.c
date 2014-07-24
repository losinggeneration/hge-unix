#include "hge_c.h"

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

inline void add_function(lua_State *L, const char *name, lua_CFunction f) {
	lua_pushstring(L, name);
	lua_pushcfunction(L, f);
	lua_settable(L, -3);
}

inline void add_garbage(lua_State *L, lua_CFunction f) {
	if(lua_getmetatable(L, -3) == 0) {
		lua_newtable(L);
	}

	add_function(L, "__gc", f);

	lua_setmetatable(L, -2);
}

/* void HGE_Release(HGE_t *hge); */
int system_release(lua_State *L) {
	printf("free: system_release\n");
	return 0;
}

/* BOOL HGE_System_Initiate(HGE_t *hge); */
int system_initiate(lua_State *L) {
	return 0;
}

/* void HGE_System_Shutdown(HGE_t *hge); */
int system_shutdown(lua_State *L) {
	return 0;
}

/* BOOL HGE_System_Start(HGE_t *hge); */
int system_start(lua_State *L) {
	return 0;
}

/* const char* HGE_System_GetErrorMessage(HGE_t *hge); */
int system_get_error_message(lua_State *L) {
	return 0;
}

/* void HGE_System_Log(HGE_t *hge, const char *format, ...); */
int system_log(lua_State *L) {
	return 0;
}

/* BOOL HGE_System_Launch(HGE_t *hge, const char *url); */
int system_launch(lua_State *L) {
	return 0;
}

/* void HGE_System_Snapshot(HGE_t *hge, const char *filename); */
int system_snapshot(lua_State *L) {
	return 0;
}

/* void HGE_System_SetStateBool(HGE_t *hge, HGE_BoolState_t state, BOOL value); */
int system_set_state_bool(lua_State *L) {
	return 0;
}

/* void HGE_System_SetStateFunc(HGE_t *hge, HGE_FuncState_t state, HGE_Callback value); */
int system_set_state_func(lua_State *L) {
	return 0;
}

/* void HGE_System_SetStateHwnd(HGE_t *hge, HGE_HwndState_t state, HWND value); */
int system_set_state_hwnd(lua_State *L) {
	return 0;
}

/* void HGE_System_SetStateInt (HGE_t *hge, HGE_IntState_t state, int value); */
int system_set_state_int(lua_State *L) {
	return 0;
}

/* void HGE_System_SetStateString(HGE_t *hge, HGE_StringState_t state, const char *value); */
int system_set_state_string(lua_State *L) {
	return 0;
}

/* BOOL HGE_System_GetStateBool(HGE_t *hge, HGE_BoolState_t state); */
int system_get_state_bool(lua_State *L) {
	return 0;
}

/* HGE_Callback HGE_System_GetStateFunc(HGE_t *hge, HGE_FuncState_t state); */
int system_get_state_func(lua_State *L) {
	return 0;
}

/* HWND HGE_System_GetStateHwnd(HGE_t *hge, HGE_HwndState_t state); */
int system_get_state_hwnd(lua_State *L) {
	return 0;
}

/* int HGE_System_GetStateInt(HGE_t *hge, HGE_IntState_t state); */
int system_get_state_int(lua_State *L) {
	return 0;
}

/* const char* HGE_System_GetStateString(HGE_t *hge, HGE_StringState_t state); */
int system_get_state_string(lua_State *L) {
	return 0;
}

luaL_Reg hge_reg[] = {
	{ "free", system_release },
	{ "shutdown", system_shutdown },
	{ "start", system_start },
	{ "get_error_message", system_get_error_message },
	{ "log", system_log },
	{ "launch", system_launch },
	{ "snapshot", system_snapshot },
	{ "set_state_bool", system_set_state_bool },
	{ "set_state_func", system_set_state_func },
	{ "set_state_hwnd", system_set_state_hwnd },
	{ "set_state_int", system_set_state_int },
	{ "get_state_bool", system_get_state_bool },
	{ "get_state_func", system_get_state_func },
	{ "get_state_hwnd", system_get_state_hwnd },
	{ "get_state_int", system_get_state_int },
	{ "get_state_string", system_get_state_string },
	NULL,
};

/* HGE_t* HGE_Create(int ver); */
int hge_create(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, hge_reg);

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

	add_garbage(L, system_release);

	return 1;
}

void register_hge(lua_State *L) {
	lua_newtable(L);

	// Add the new function to the table
	add_function(L, "new", hge_create);

	// Pop's the hge table off the stack
	lua_setglobal(L, "hge");
}

/* void HGE_Resource_Free(HGE_t *hge, void *res); */
int resource_free(lua_State *L) {
	return 0;
}

/* BOOL HGE_Resource_AttachPack(HGE_t *hge, const char *filename, const char *password); */
int resource_attach_pack(lua_State *L) {
	return 0;
}

/* void HGE_Resource_RemovePack(HGE_t *hge, const char *filename); */
int resource_remove_pack(lua_State *L) {
	return 0;
}

/* void HGE_Resource_RemoveAllPacks(HGE_t *hge); */
int resource_remove_all_packs(lua_State *L) {
	return 0;
}

/* char* HGE_Resource_MakePath(HGE_t *hge, const char *filename); */
int resource_make_path(lua_State *L) {
	return 0;
}

/* char* HGE_Resource_EnumFiles(HGE_t *hge, const char *wildcard); */
int resource_enum_files(lua_State *L) {
	return 0;
}

/* char* HGE_Resource_EnumFolders(HGE_t *hge, const char *wildcard); */
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

/* void* HGE_Resource_Load(HGE_t *hge, const char *filename, DWORD *size); */
int resource_load(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, resource_reg);

	add_garbage(L, resource_free);

	return 1;
}

void register_resource(lua_State *L) {
	lua_pushstring(L, "resource");
	lua_newtable(L);

	add_function(L, "new", resource_load);

	lua_settable(L, -3);
}

/* void HGE_Ini_SetInt(HGE_t *hge, const char *section, const char *name, int value); */
int ini_set_int(lua_State *L) {
	return 0;
}

/* int HGE_Ini_GetInt(HGE_t *hge, const char *section, const char *name, int def_val); */
int ini_get_int(lua_State *L) {
	return 0;
}

/* void HGE_Ini_SetFloat(HGE_t *hge, const char *section, const char *name, float value); */
int ini_set_float(lua_State *L) {
	return 0;
}

/* float HGE_Ini_GetFloat(HGE_t *hge, const char *section, const char *name, float def_val); */
int ini_get_float(lua_State *L) {
	return 0;
}

/* void HGE_Ini_SetString(HGE_t *hge, const char *section, const char *name, const char *value); */
int ini_set_string(lua_State *L) {
	return 0;
}

/* char* HGE_Ini_GetString(HGE_t *hge, const char *section, const char *name, const char *def_val); */
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

/* void HGE_Random_Seed(HGE_t *hge, int seed); */
int random_seed(lua_State *L) {
	return 0;
}

/* int HGE_Random_Int(HGE_t *hge, int min, int max); */
int random_int(lua_State *L) {
	return 0;
}

/* float HGE_Random_Float(HGE_t *hge, float min, float max); */
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

/* float HGE_Timer_GetTime(HGE_t *hge); */
int timer_get_time(lua_State *L) {
	return 0;
}

/* float HGE_Timer_GetDelta(HGE_t *hge); */
int timer_get_delta(lua_State *L) {
	return 0;
}

/* int HGE_Timer_GetFPS(HGE_t *hge); */
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

/* void HGE_Effect_Free(HGE_t *hge, HEFFECT eff); */
int effect_free(lua_State *L) {
	return 0;
}

/* HCHANNEL HGE_Effect_Play(HGE_t *hge, HEFFECT eff); */
int effect_play(lua_State *L) {
	return 0;
}

/* HCHANNEL HGE_Effect_PlayEx(HGE_t *hge, HEFFECT eff, int volume, int pan, float pitch, BOOL loop); */
int effect_play_ex(lua_State *L) {
	return 0;
}

luaL_Reg effect_reg[] = {
	{ "free", effect_free },
	{ "play", effect_play },
	{ "play_ex", effect_play_ex },
	NULL,
};

/* HEFFECT HGE_Effect_Load(HGE_t *hge, const char *filename, DWORD size); */
int effect_load(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, effect_reg);

	add_garbage(L, effect_free);

	return 1;
}

void register_effect(lua_State *L) {
	lua_pushstring(L, "effect");
	lua_newtable(L);

	add_function(L, "new", effect_load);

	lua_settable(L, -3);
}

/* void HGE_Music_Free(HGE_t *hge, HMUSIC mus); */
int music_free(lua_State *L) {
	return 0;
}

/* HCHANNEL HGE_Music_Play(HGE_t *hge, HMUSIC mus, BOOL loop, int volume, int order, int row); */
int music_play(lua_State *L) {
	return 0;
}

/* void HGE_Music_SetAmplification(HGE_t *hge, HMUSIC music, int ampl); */
int music_set_amplification(lua_State *L) {
	return 0;
}

/* int HGE_Music_GetAmplification(HGE_t *hge, HMUSIC music); */
int music_get_amplification(lua_State *L) {
	return 0;
}

/* int HGE_Music_GetLength(HGE_t *hge, HMUSIC music); */
int music_get_length(lua_State *L) {
	return 0;
}

/* void HGE_Music_SetPos(HGE_t *hge, HMUSIC music, int order, int row); */
int music_set_pos(lua_State *L) {
	return 0;
}

/* BOOL HGE_Music_GetPos(HGE_t *hge, HMUSIC music, int *order, int *row); */
int music_get_pos(lua_State *L) {
	return 0;
}

/* void HGE_Music_SetInstrVolume(HGE_t *hge, HMUSIC music, int instr, int volume); */
int music_set_instr_volume(lua_State *L) {
	return 0;
}

/* int HGE_Music_GetInstrVolume(HGE_t *hge, HMUSIC music, int instr); */
int music_get_instr_volume(lua_State *L) {
	return 0;
}

/* void HGE_Music_SetChannelVolume(HGE_t *hge, HMUSIC music, int channel, int volume); */
int music_set_channel_volume(lua_State *L) {
	return 0;
}

/* int HGE_Music_GetChannelVolume(HGE_t *hge, HMUSIC music, int channel); */
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

/* HMUSIC HGE_Music_Load(HGE_t *hge, const char *filename, DWORD size); */
int music_load(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, music_reg);

	add_garbage(L, music_free);

	return 1;
}

void register_music(lua_State *L) {
	lua_pushstring(L, "music");
	lua_newtable(L);

	add_function(L, "new", music_load);

	lua_settable(L, -3);
}

/* void HGE_Stream_Free(HGE_t *hge, HSTREAM stream); */
int stream_free(lua_State *L) {
	return 0;
}

/* HCHANNEL HGE_Stream_Play(HGE_t *hge, HSTREAM stream, BOOL loop, int volume); */
int stream_play(lua_State *L) {
	return 0;
}

luaL_Reg stream_reg[] = {
	{ "free", stream_free },
	{ "play", stream_play },
	NULL,
};

/* HSTREAM HGE_Stream_Load(HGE_t *hge, const char *filename, DWORD size); */
int stream_load(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, stream_reg);

	add_garbage(L, stream_free);

	return 1;
}

void register_stream(lua_State *L) {
	lua_pushstring(L, "stream");
	lua_newtable(L);

	add_function(L, "new", stream_load);
	lua_settable(L, -3);
}

/* void HGE_Channel_SetPanning(HGE_t *hge, HCHANNEL chn, int pan); */
int channel_set_panning(lua_State *L) {
	return 0;
}

/* void HGE_Channel_SetVolume(HGE_t *hge, HCHANNEL chn, int volume); */
int channel_set_volume(lua_State *L) {
	return 0;
}

/* void HGE_Channel_SetPitch(HGE_t *hge, HCHANNEL chn, float pitch); */
int channel_set_pitch(lua_State *L) {
	return 0;
}

/* void HGE_Channel_Pause(HGE_t *hge, HCHANNEL chn); */
int channel_pause(lua_State *L) {
	return 0;
}

/* void HGE_Channel_Resume(HGE_t *hge, HCHANNEL chn); */
int channel_resume(lua_State *L) {
	return 0;
}

/* void HGE_Channel_Stop(HGE_t *hge, HCHANNEL chn); */
int channel_stop(lua_State *L) {
	return 0;
}

/* void HGE_Channel_PauseAll(HGE_t *hge); */
int channel_pause_all(lua_State *L) {
	return 0;
}

/* void HGE_Channel_ResumeAll(HGE_t *hge); */
int channel_resume_all(lua_State *L) {
	return 0;
}

/* void HGE_Channel_StopAll(HGE_t *hge); */
int channel_stop_all(lua_State *L) {
	return 0;
}

/* BOOL HGE_Channel_IsPlaying(HGE_t *hge, HCHANNEL chn); */
int channel_is_playing(lua_State *L) {
	return 0;
}

/* float HGE_Channel_GetLength(HGE_t *hge, HCHANNEL chn); */
int channel_get_length(lua_State *L) {
	return 0;
}

/* float HGE_Channel_GetPos(HGE_t *hge, HCHANNEL chn); */
int channel_get_pos(lua_State *L) {
	return 0;
}

/* void HGE_Channel_SetPos(HGE_t *hge, HCHANNEL chn, float fSeconds); */
int channel_set_pos(lua_State *L) {
	return 0;
}

/* void HGE_Channel_SlideTo(HGE_t *hge, HCHANNEL channel, float time, int volume, int pan, float pitch); */
int channel_slide_to(lua_State *L) {
	return 0;
}

/* BOOL HGE_Channel_IsSliding(HGE_t *hge, HCHANNEL channel); */
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

/* void HGE_Input_GetMousePos(HGE_t *hge, float *x, float *y); */
int input_get_mouse_pos(lua_State *L) {
	return 0;
}

/* void HGE_Input_SetMousePos(HGE_t *hge, float x, float y); */
int input_set_mouse_pos(lua_State *L) {
	return 0;
}

/* int HGE_Input_GetMouseWheel(HGE_t *hge); */
int input_get_mouse_wheel(lua_State *L) {
	return 0;
}

/* BOOL HGE_Input_IsMouseOver(HGE_t *hge); */
int input_is_mouse_over(lua_State *L) {
	return 0;
}

/* BOOL HGE_Input_KeyDown(HGE_t *hge, int key); */
int input_key_down(lua_State *L) {
	return 0;
}

/* BOOL HGE_Input_KeyUp(HGE_t *hge, int key); */
int input_key_up(lua_State *L) {
	return 0;
}

/* BOOL HGE_Input_GetKeyState(HGE_t *hge, int key); */
int input_get_key_state(lua_State *L) {
	return 0;
}

/* const char* HGE_Input_GetKeyName(HGE_t *hge, int key); */
int input_get_key_name(lua_State *L) {
	return 0;
}

/* int HGE_Input_GetKey(HGE_t *hge); */
int input_get_key(lua_State *L) {
	return 0;
}

/* int HGE_Input_GetChar(HGE_t *hge); */
int input_get_char(lua_State *L) {
	return 0;
}

/* BOOL HGE_Input_GetEvent(HGE_t *hge, HGE_InputEvent_t *event); */
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

/* BOOL HGE_Gfx_BeginScene(HGE_t *hge, HTARGET target); */
int gfx_begin_scene(lua_State *L) {
	return 0;
}

/* void HGE_Gfx_EndScene(HGE_t *hge); */
int gfx_end_scene(lua_State *L) {
	return 0;
}

/* void HGE_Gfx_Clear(HGE_t *hge, DWORD color); */
int gfx_clear(lua_State *L) {
	return 0;
}

/* void HGE_Gfx_RenderLine(HGE_t *hge, float x1, float y1, float x2, float y2, DWORD color, float z); */
int gfx_render_line(lua_State *L) {
	return 0;
}

/* void HGE_Gfx_RenderTriple(HGE_t *hge, const HGE_Triple_t *triple); */
int gfx_render_triple(lua_State *L) {
	return 0;
}

/* void HGE_Gfx_RenderQuad(HGE_t *hge, const HGE_Quad_t *quad); */
int gfx_render_quad(lua_State *L) {
	return 0;
}

/* HGE_Vertex_t* HGE_Gfx_StartBatch(HGE_t *hge, int prim_type, HTEXTURE tex, int blend, int *max_prim); */
int gfx_start_batch(lua_State *L) {
	return 0;
}

/* void HGE_Gfx_FinishBatch(HGE_t *hge, int nprim); */
int gfx_finish_batch(lua_State *L) {
	return 0;
}

/* void HGE_Gfx_SetClipping(HGE_t *hge, int x, int y, int w, int h); */
int gfx_set_clipping(lua_State *L) {
	return 0;
}

/* void HGE_Gfx_SetTransform(HGE_t *hge, float x, float y, float dx, float dy, float rot, float hscale, float vscale); */
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

/* void HGE_Target_Free(HGE_t *hge, HTARGET target); */
int target_free(lua_State *L) {
	return 0;
}

/* HTEXTURE HGE_Target_GetTexture(HGE_t *hge, HTARGET target); */
int target_get_texture(lua_State *L) {
	return 0;
}

luaL_Reg target_reg[] = {
	{ "free", target_free },
	{ "get_texture", target_get_texture },
	NULL,
};

/* HTARGET HGE_Target_Create(HGE_t *hge, int width, int height, BOOL zbuffer); */
int target_create(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, target_reg);

	add_garbage(L, target_free);

	return 1;
}

void register_target(lua_State *L) {
	lua_pushstring(L, "target");
	lua_newtable(L);

	add_function(L, "new", target_create);

	lua_settable(L, -3);
}

/* void HGE_Texture_Free(HGE_t *hge, HTEXTURE tex); */
int texture_free(lua_State *L) {
	printf("freeing texture\n");
	return 0;
}

/* int HGE_Texture_GetWidth(HGE_t *hge, HTEXTURE tex, BOOL bOriginal); */
int texture_get_width(lua_State *L) {
	return 0;
}

/* int HGE_Texture_GetHeight(HGE_t *hge, HTEXTURE tex, BOOL bOriginal); */
int texture_get_height(lua_State *L) {
	return 0;
}

/* DWORD* HGE_Texture_Lock(HGE_t *hge, HTEXTURE tex, BOOL bReadOnly, int left, int top, int width, int height); */
int texture_lock(lua_State *L) {
	return 0;
}

/* void HGE_Texture_Unlock(HGE_t *hge, HTEXTURE tex); */
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

	add_garbage(L, texture_free);
}

/* HTEXTURE HGE_Texture_Create(HGE_t *hge, int width, int height); */
int texture_create(lua_State *L) {
	texture_new(L);

	return 1;
}

/* HTEXTURE HGE_Texture_Load(HGE_t *hge, const char *filename, DWORD size, BOOL bMipmap); */
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

void luaopen_hge(lua_State *L) {
	register_hge(L);
}
