--
-- Haaf's Game Engine 1.8
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- System layer API
--

array.pushBack(gen_lua.enum_types, 'hgeBoolState', 'hgeFuncState', 'hgeHwndState', 'hgeInputEvent', 'hgeIntState', 'hgeStringState')
array.pushBack(gen_lua.number_types, 'HTEXTURE', 'HTARGET', 'HEFFECT', 'HMUSIC', 'HSTREAM', 'HCHANNEL')

bindhge = {
	classes = {
		{
			name = 'hge.Vertex',
			className = 'hgeVertex',
-- 			ctors = {
-- 				'()',
-- 			},
			properties = {[[
				float x;
				float y;
				float z;
				DWORD col;
				float tx;
				float ty;
			]]},
		},
		{
			name = 'hge.Triple',
			className = 'hgeTriple',
-- 			ctors = {
-- 				'()',
-- 			},
-- 			properties = {[[
-- 				hgeVertex v[3];
-- 				HTEXTURE tex;
-- 				int blend;
-- 			]]},
		},
		{
			name = 'hge.Quad',
			className = 'hgeQuad',
-- 			ctors = {
-- 				'()',
-- 			},
-- 			properties = {[[
-- 				hgeVertex v[4];
-- 				HTEXTURE tex;
-- 				int blend;
-- 			]]},
		},
		{
			name = 'hge.InputEvent',
			className = 'hgeInputEvent',
-- 			ctors = {
-- 				'()',
-- 			},
			properties = {[[
				int type;
				int key;
				int flags;
				int chr;
				int wheel;
				float x;
				float y;
			]]},
		},
		{
			name = 'hge.abstract',
			className = 'HGE',
			memberFunctions = {
				{ rename = 'release', 'void Release();' },

				{ rename = 'system_initiate', 'bool System_Initiate();' },
				{ rename = 'system_shutdown', 'void System_Shutdown();' },
				{ rename = 'system_start', 'bool System_Start();' },
				{ rename = 'system_geterrormessage', 'const char* System_GetErrorMessage();' },
-- 				{ rename = 'system_log', 'void System_Log(const char *format, ...);' },
				{ rename = 'system_launch', 'bool System_Launch(const char *url);' },
				{ rename = 'system_snapshot', 'void System_Snapshot(const char *filename);' },

				{ rename = 'system_set_bool_state', 'void System_SetState(hgeBoolState state, bool value);' },
-- 				{ rename = 'system_set_func_state', 'void System_SetState(hgeFuncState state, hgeCallback value);' },
-- 				{ rename = 'system_set_hwnd_state', 'void System_SetState(hgeHwndState state, HWND value);' },
				{ rename = 'system_set_int_state', 'void System_SetState(hgeIntState state, int value);' },
				{ rename = 'system_set_string_state', 'void System_SetState(hgeStringState state, const char *value);' },
				{ rename = 'system_get_bool_state', 'bool System_GetState(hgeBoolState state);' },
-- 				{ rename = 'system_get_func_state', 'hgeCallback System_GetState(hgeFuncState state);' },
-- 				{ rename = 'system_get_hwnd_state', 'HWND System_GetState(hgeHwndState state);' },
				{ rename = 'system_get_int_state', 'int System_GetState(hgeIntState state);' },
				{ rename = 'system_get_string_state', 'const char* System_GetState(hgeStringState state);' },

-- 				{ rename = 'resource_load', 'void* Resource_Load(const char *filename, DWORD *size);' },
-- 				{ rename = 'resource_free', 'void Resource_Free(void * res);' },
				{ rename = 'resource_attachpack', 'bool Resource_AttachPack(const char *filename, const char *password);' },
				{ rename = 'resource_removepack', 'void Resource_RemovePack(const char *filename);' },
				{ rename = 'resource_removeallpacks', 'void Resource_RemoveAllPacks();' },
				{ rename = 'resource_makepath', 'char * Resource_MakePath(const char * filename);' },
				{ rename = 'resource_enumfiles', 'char * Resource_EnumFiles(const char * wildcard);' },
				{ rename = 'resource_enumfolders', 'char * Resource_EnumFolders(const char * wildcard);' },

				{ rename = 'ini_setint', 'void Ini_SetInt(const char *section, const char *name, int value);' },
				{ rename = 'ini_getint', 'int Ini_GetInt(const char *section, const char *name, int def_val);' },
				{ rename = 'ini_setfloat', 'void Ini_SetFloat(const char *section, const char *name, float value);' },
				{ rename = 'ini_getfloat', 'float Ini_GetFloat(const char *section, const char *name, float def_val);' },
				{ rename = 'ini_setstring', 'void Ini_SetString(const char *section, const char *name, const char *value);' },
				{ rename = 'ini_getstring', 'char * Ini_GetString(const char *section, const char *name, const char *def_val);' },

				{ rename = 'random_seed', 'void Random_Seed(int seed);' },
				{ rename = 'random_int', 'int Random_Int(int min, int max);' },
				{ rename = 'random_float', 'float Random_Float(float min, float max);' },

				{ rename = 'timer_gettime', 'float Timer_GetTime();' },
				{ rename = 'timer_getdelta', 'float Timer_GetDelta();' },
				{ rename = 'timer_getfps', 'int Timer_GetFPS();' },

				{ rename = 'effect_load', 'HEFFECT Effect_Load(const char *filename, DWORD size);' },
				{ rename = 'effect_free', 'void Effect_Free(HEFFECT eff);' },
				{ rename = 'effect_play', 'HCHANNEL Effect_Play(HEFFECT eff);' },
				{ rename = 'effect_playex', 'HCHANNEL Effect_PlayEx(HEFFECT eff, int volume, int pan, float pitch, bool loop);' },

				{ rename = 'music_load', 'HMUSIC Music_Load(const char *filename, DWORD size);' },
				{ rename = 'music_free', 'void Music_Free(HMUSIC mus);' },
				{ rename = 'music_play', 'HCHANNEL Music_Play(HMUSIC mus, bool loop, int volume, int order, int row);' },
				{ rename = 'music_setamplification', 'void Music_SetAmplification(HMUSIC music, int ampl);' },
				{ rename = 'music_getamplification', 'int Music_GetAmplification(HMUSIC music);' },
				{ rename = 'music_getlength', 'int Music_GetLength(HMUSIC music);' },
				{ rename = 'music_setpos', 'void Music_SetPos(HMUSIC music, int order, int row);' },
-- 				{ rename = 'music_getpos', 'bool Music_GetPos(HMUSIC music, int *order, int *row);' },
				{ rename = 'music_setinstrvolume', 'void Music_SetInstrVolume(HMUSIC music, int instr, int volume);' },
				{ rename = 'music_getinstrvolume', 'int Music_GetInstrVolume(HMUSIC music, int instr);' },
				{ rename = 'music_setchannelvolume', 'void Music_SetChannelVolume(HMUSIC music, int channel, int volume);' },
				{ rename = 'music_getchannelvolume', 'int Music_GetChannelVolume(HMUSIC music, int channel);' },

				{ rename = 'stream_load', 'HSTREAM Stream_Load(const char *filename, DWORD size);' },
				{ rename = 'stream_free', 'void Stream_Free(HSTREAM stream);' },
				{ rename = 'stream_play', 'HCHANNEL Stream_Play(HSTREAM stream, bool loop, int volume);' },

				{ rename = 'channel_setpanning', 'void Channel_SetPanning(HCHANNEL chn, int pan);' },
				{ rename = 'channel_setvolume', 'void Channel_SetVolume(HCHANNEL chn, int volume);' },
				{ rename = 'channel_setpitch', 'void Channel_SetPitch(HCHANNEL chn, float pitch);' },
				{ rename = 'channel_pause', 'void Channel_Pause(HCHANNEL chn);' },
				{ rename = 'channel_resume', 'void Channel_Resume(HCHANNEL chn);' },
				{ rename = 'channel_stop', 'void Channel_Stop(HCHANNEL chn);' },
				{ rename = 'channel_pauseall', 'void Channel_PauseAll();' },
				{ rename = 'channel_resumeall', 'void Channel_ResumeAll();' },
				{ rename = 'channel_stopall', 'void Channel_StopAll();' },
				{ rename = 'channel_isplaying', 'bool Channel_IsPlaying(HCHANNEL chn);' },
				{ rename = 'channel_getlength', 'float Channel_GetLength(HCHANNEL chn);' },
				{ rename = 'channel_getpos', 'float Channel_GetPos(HCHANNEL chn);' },
				{ rename = 'channel_setpos', 'void Channel_SetPos(HCHANNEL chn, float fSeconds);' },
				{ rename = 'channel_slideto', 'void Channel_SlideTo(HCHANNEL channel, float time, int volume, int pan, float pitch);' },
				{ rename = 'channel_issliding', 'bool Channel_IsSliding(HCHANNEL channel);' },

-- 				{ rename = 'input_getmousepos', 'void Input_GetMousePos(float *x, float *y);' },
				{ rename = 'input_setmousepos', 'void Input_SetMousePos(float x, float y);' },
				{ rename = 'input_getmousewheel', 'int Input_GetMouseWheel();' },
				{ rename = 'input_ismouseover', 'bool Input_IsMouseOver();' },
				{ rename = 'input_keydown', 'bool Input_KeyDown(int key);' },
				{ rename = 'input_keyup', 'bool Input_KeyUp(int key);' },
				{ rename = 'input_getkeystate', 'bool Input_GetKeyState(int key);' },
				{ rename = 'input_getkeyname', 'const char* Input_GetKeyName(int key);' },
				{ rename = 'input_getkey', 'int Input_GetKey();' },
				{ rename = 'input_getchar', 'int Input_GetChar();' },
				{ rename = 'input_getevent', 'bool Input_GetEvent(hgeInputEvent *event);' },

				{ rename = 'gfx_beginscene', 'bool Gfx_BeginScene(HTARGET target);' },
				{ rename = 'gfx_endscene', 'void Gfx_EndScene();' },
				{ rename = 'gfx_clear', 'void Gfx_Clear(DWORD color);' },
				{ rename = 'gfx_renderline', 'void Gfx_RenderLine(float x1, float y1, float x2, float y2, DWORD color, float z);' },
				{ rename = 'gfx_rendertriple', 'void Gfx_RenderTriple(const hgeTriple *triple);' },
				{ rename = 'gfx_renderquad', 'void Gfx_RenderQuad(const hgeQuad *quad);' },
-- 				{ rename = 'gfx_startbatch', 'hgeVertex* Gfx_StartBatch(int prim_type, HTEXTURE tex, int blend, int *max_prim);' },
				{ rename = 'gfx_finishbatch', 'void Gfx_FinishBatch(int nprim);' },
				{ rename = 'gfx_setclipping', 'void Gfx_SetClipping(int x, int y, int w, int h);' },
				{ rename = 'gfx_settransform', 'void Gfx_SetTransform(float x, float y, float dx, float dy, float rot, float hscale, float vscale);' },

				{ rename = 'target_create', 'HTARGET Target_Create(int width, int height, bool zbuffer);' },
				{ rename = 'target_free', 'void Target_Free(HTARGET target);' },
				{ rename = 'target_gettexture', 'HTEXTURE Target_GetTexture(HTARGET target);' },

				{ rename = 'texture_create', 'HTEXTURE Texture_Create(int width, int height);' },
				{ rename = 'texture_load', 'HTEXTURE Texture_Load(const char *filename, DWORD size, bool bMipmap);' },
				{ rename = 'texture_free', 'void Texture_Free(HTEXTURE tex);' },
				{ rename = 'texture_getwidth', 'int Texture_GetWidth(HTEXTURE tex, bool bOriginal);' },
				{ rename = 'texture_getheight', 'int Texture_GetHeight(HTEXTURE tex, bool bOriginal);' },
-- 				{ rename = 'texture_lock', 'DWORD * Texture_Lock(HTEXTURE tex, bool bReadOnly, int left, int top, int width, int height);' },
				{ rename = 'textureunlock', 'void Texture_Unlock(HTEXTURE tex);' },
			},
		},
		{
			name = 'hge.HGE',
			className = 'HGE_Impl',
			inheritsFrom = 'HGE',
			staticMemberFunctions = {
				{ rename = 'create', 'HGE * hgeCreate(int ver);' },
			},
			enums = {
				-- enum hgeBoolState
				{ 'HGE_WINDOWED', '(int)HGE_WINDOWED' },
				{ 'HGE_ZBUFFER', '(int)HGE_ZBUFFER' },
				{ 'HGE_TEXTUREFILTER', '(int)HGE_TEXTUREFILTER' },
				{ 'HGE_USESOUND', '(int)HGE_USESOUND' },
				{ 'HGE_DONTSUSPEND', '(int)HGE_DONTSUSPEND' },
				{ 'HGE_HIDEMOUSE', '(int)HGE_HIDEMOUSE' },
				{ 'HGE_SHOWSPLASH', '(int)HGE_SHOWSPLASH' },
				{ 'HGEBOOLSTATE_FORCE_DWORD', '(int)HGEBOOLSTATE_FORCE_DWORD' },

				-- enum hgeFuncState
				{ 'HGE_FRAMEFUNC', '(int)HGE_FRAMEFUNC' },
				{ 'HGE_RENDERFUNC', '(int)HGE_RENDERFUNC' },
				{ 'HGE_FOCUSLOSTFUNC', '(int)HGE_FOCUSLOSTFUNC' },
				{ 'HGE_FOCUSGAINFUNC', '(int)HGE_FOCUSGAINFUNC' },
				{ 'HGE_GFXRESTOREFUNC', '(int)HGE_GFXRESTOREFUNC' },
				{ 'HGE_EXITFUNC', '(int)HGE_EXITFUNC' },

				{ 'HGEFUNCSTATE_FORCE_DWORD', '(int)HGEFUNCSTATE_FORCE_DWORD' },

				-- enum hgeHwndState
				{ 'HGE_HWND', '(int)HGE_HWND' },
				{ 'HGE_HWNDPARENT', '(int)HGE_HWNDPARENT' },

				{ 'HGEHWNDSTATE_FORCE_DWORD', '(int)HGEHWNDSTATE_FORCE_DWORD' },

				-- enum hgeIntState
				{ 'HGE_SCREENWIDTH', '(int)HGE_SCREENWIDTH' },
				{ 'HGE_SCREENHEIGHT', '(int)HGE_SCREENHEIGHT' },
				{ 'HGE_SCREENBPP', '(int)HGE_SCREENBPP' },

				{ 'HGE_SAMPLERATE', '(int)HGE_SAMPLERATE' },
				{ 'HGE_FXVOLUME', '(int)HGE_FXVOLUME' },
				{ 'HGE_MUSVOLUME', '(int)HGE_MUSVOLUME' },
				{ 'HGE_STREAMVOLUME', '(int)HGE_STREAMVOLUME' },

				{ 'HGE_FPS', '(int)HGE_FPS' },

				{ 'HGE_POWERSTATUS', '(int)HGE_POWERSTATUS' },

				{ 'HGE_ORIGSCREENWIDTH', '(int)HGE_ORIGSCREENWIDTH' },
				{ 'HGE_ORIGSCREENHEIGHT', '(int)HGE_ORIGSCREENHEIGHT' },

				{ 'HGEINTSTATE_FORCE_DWORD', '(int)HGEINTSTATE_FORCE_DWORD' },

				-- enum hgeStringState
				{ 'HGE_ICON', '(int)HGE_ICON' },
				{ 'HGE_TITLE', '(int)HGE_TITLE' },

				{ 'HGE_INIFILE', '(int)HGE_INIFILE' },
				{ 'HGE_LOGFILE', '(int)HGE_LOGFILE' },

				{ 'HGESTRINGSTATE_FORCE_DWORD', '(int)HGESTRINGSTATE_FORCE_DWORD' },

				-- HGE Blending constants (defines)
				{ 'BLEND_COLORADD', '(int)BLEND_COLORADD' },
				{ 'BLEND_COLORMUL', '(int)BLEND_COLORMUL' },
				{ 'BLEND_ALPHABLEND', '(int)BLEND_ALPHABLEND' },
				{ 'BLEND_ALPHAADD', '(int)BLEND_ALPHAADD' },
				{ 'BLEND_ZWRITE', '(int)BLEND_ZWRITE' },
				{ 'BLEND_NOZWRITE', '(int)BLEND_NOZWRITE' },

				{ 'BLEND_DEFAULT', '(int)BLEND_DEFAULT' },
				{ 'BLEND_DEFAULT_Z', '(int)BLEND_DEFAULT_Z' },

				-- defines for HGEK
				{ 'HGEK_LBUTTON', '(int)HGEK_LBUTTON' },
				{ 'HGEK_RBUTTON', '(int)HGEK_RBUTTON' },
				{ 'HGEK_MBUTTON', '(int)HGEK_MBUTTON' },

				{ 'HGEK_ESCAPE', '(int)HGEK_ESCAPE' },
				{ 'HGEK_BACKSPACE', '(int)HGEK_BACKSPACE' },
				{ 'HGEK_TAB', '(int)HGEK_TAB' },
				{ 'HGEK_ENTER', '(int)HGEK_ENTER' },
				{ 'HGEK_SPACE', '(int)HGEK_SPACE' },

				{ 'HGEK_SHIFT', '(int)HGEK_SHIFT' },
				{ 'HGEK_CTRL', '(int)HGEK_CTRL' },
				{ 'HGEK_ALT', '(int)HGEK_ALT' },

				{ 'HGEK_LWIN', '(int)HGEK_LWIN' },
				{ 'HGEK_RWIN', '(int)HGEK_RWIN' },
				{ 'HGEK_APPS', '(int)HGEK_APPS' },

				{ 'HGEK_PAUSE', '(int)HGEK_PAUSE' },
				{ 'HGEK_CAPSLOCK', '(int)HGEK_CAPSLOCK' },
				{ 'HGEK_NUMLOCK', '(int)HGEK_NUMLOCK' },
				{ 'HGEK_SCROLLLOCK', '(int)HGEK_SCROLLLOCK' },

				{ 'HGEK_PGUP', '(int)HGEK_PGUP' },
				{ 'HGEK_PGDN', '(int)HGEK_PGDN' },
				{ 'HGEK_HOME', '(int)HGEK_HOME' },
				{ 'HGEK_END', '(int)HGEK_END' },
				{ 'HGEK_INSERT', '(int)HGEK_INSERT' },
				{ 'HGEK_DELETE', '(int)HGEK_DELETE' },

				{ 'HGEK_LEFT', '(int)HGEK_LEFT' },
				{ 'HGEK_UP', '(int)HGEK_UP' },
				{ 'HGEK_RIGHT', '(int)HGEK_RIGHT' },
				{ 'HGEK_DOWN', '(int)HGEK_DOWN' },

				{ 'HGEK_0', '(int)HGEK_0' },
				{ 'HGEK_1', '(int)HGEK_1' },
				{ 'HGEK_2', '(int)HGEK_2' },
				{ 'HGEK_3', '(int)HGEK_3' },
				{ 'HGEK_4', '(int)HGEK_4' },
				{ 'HGEK_5', '(int)HGEK_5' },
				{ 'HGEK_6', '(int)HGEK_6' },
				{ 'HGEK_7', '(int)HGEK_7' },
				{ 'HGEK_8', '(int)HGEK_8' },
				{ 'HGEK_9', '(int)HGEK_9' },

				{ 'HGEK_A', '(int)HGEK_A' },
				{ 'HGEK_B', '(int)HGEK_B' },
				{ 'HGEK_C', '(int)HGEK_C' },
				{ 'HGEK_D', '(int)HGEK_D' },
				{ 'HGEK_E', '(int)HGEK_E' },
				{ 'HGEK_F', '(int)HGEK_F' },
				{ 'HGEK_G', '(int)HGEK_G' },
				{ 'HGEK_H', '(int)HGEK_H' },
				{ 'HGEK_I', '(int)HGEK_I' },
				{ 'HGEK_J', '(int)HGEK_J' },
				{ 'HGEK_K', '(int)HGEK_K' },
				{ 'HGEK_L', '(int)HGEK_L' },
				{ 'HGEK_M', '(int)HGEK_M' },
				{ 'HGEK_N', '(int)HGEK_N' },
				{ 'HGEK_O', '(int)HGEK_O' },
				{ 'HGEK_P', '(int)HGEK_P' },
				{ 'HGEK_Q', '(int)HGEK_Q' },
				{ 'HGEK_R', '(int)HGEK_R' },
				{ 'HGEK_S', '(int)HGEK_S' },
				{ 'HGEK_T', '(int)HGEK_T' },
				{ 'HGEK_U', '(int)HGEK_U' },
				{ 'HGEK_V', '(int)HGEK_V' },
				{ 'HGEK_W', '(int)HGEK_W' },
				{ 'HGEK_X', '(int)HGEK_X' },
				{ 'HGEK_Y', '(int)HGEK_Y' },
				{ 'HGEK_Z', '(int)HGEK_Z' },

				{ 'HGEK_GRAVE', '(int)HGEK_GRAVE' },
				{ 'HGEK_MINUS', '(int)HGEK_MINUS' },
				{ 'HGEK_EQUALS', '(int)HGEK_EQUALS' },
				{ 'HGEK_BACKSLASH', '(int)HGEK_BACKSLASH' },
				{ 'HGEK_LBRACKET', '(int)HGEK_LBRACKET' },
				{ 'HGEK_RBRACKET', '(int)HGEK_RBRACKET' },
				{ 'HGEK_SEMICOLON', '(int)HGEK_SEMICOLON' },
				{ 'HGEK_APOSTROPHE', '(int)HGEK_APOSTROPHE' },
				{ 'HGEK_COMMA', '(int)HGEK_COMMA' },
				{ 'HGEK_PERIOD', '(int)HGEK_PERIOD' },
				{ 'HGEK_SLASH', '(int)HGEK_SLASH' },

				{ 'HGEK_NUMPAD0', '(int)HGEK_NUMPAD0' },
				{ 'HGEK_NUMPAD1', '(int)HGEK_NUMPAD1' },
				{ 'HGEK_NUMPAD2', '(int)HGEK_NUMPAD2' },
				{ 'HGEK_NUMPAD3', '(int)HGEK_NUMPAD3' },
				{ 'HGEK_NUMPAD4', '(int)HGEK_NUMPAD4' },
				{ 'HGEK_NUMPAD5', '(int)HGEK_NUMPAD5' },
				{ 'HGEK_NUMPAD6', '(int)HGEK_NUMPAD6' },
				{ 'HGEK_NUMPAD7', '(int)HGEK_NUMPAD7' },
				{ 'HGEK_NUMPAD8', '(int)HGEK_NUMPAD8' },
				{ 'HGEK_NUMPAD9', '(int)HGEK_NUMPAD9' },

				{ 'HGEK_MULTIPLY', '(int)HGEK_MULTIPLY' },
				{ 'HGEK_DIVIDE', '(int)HGEK_DIVIDE' },
				{ 'HGEK_ADD', '(int)HGEK_ADD' },
				{ 'HGEK_SUBTRACT', '(int)HGEK_SUBTRACT' },
				{ 'HGEK_DECIMAL', '(int)HGEK_DECIMAL' },

				{ 'HGEK_F1', '(int)HGEK_F1' },
				{ 'HGEK_F2', '(int)HGEK_F2' },
				{ 'HGEK_F3', '(int)HGEK_F3' },
				{ 'HGEK_F4', '(int)HGEK_F4' },
				{ 'HGEK_F5', '(int)HGEK_F5' },
				{ 'HGEK_F6', '(int)HGEK_F6' },
				{ 'HGEK_F7', '(int)HGEK_F7' },
				{ 'HGEK_F8', '(int)HGEK_F8' },
				{ 'HGEK_F9', '(int)HGEK_F9' },
				{ 'HGEK_F10', '(int)HGEK_F10' },
				{ 'HGEK_F11', '(int)HGEK_F11' },
				{ 'HGEK_F12', '(int)HGEK_F12' },
			},
		},
	},
	modules = {
	}
}

--[[
#define HGE_VERSION 0x181

/*
** Common math constants
*/
#ifndef M_PI
#define M_PI	3.14159265358979323846f
#endif
#ifndef M_PI_2
#define M_PI_2	1.57079632679489661923f
#endif
#ifndef M_PI_4
#define M_PI_4	0.785398163397448309616f
#endif
#ifndef M_1_PI
#define M_1_PI	0.318309886183790671538f
#endif
#ifndef M_2_PI
#define M_2_PI	0.636619772367581343076f
#endif

/*
** Hardware color macros
*/
#define ARGB(a,r,g,b)	((DWORD(a)<<24) + (DWORD(r)<<16) + (DWORD(g)<<8) + DWORD(b))
#define GETA(col)		((col)>>24)
#define GETR(col)		(((col)>>16) & 0xFF)
#define GETG(col)		(((col)>>8) & 0xFF)
#define GETB(col)		((col) & 0xFF)
#define SETA(col,a)		(((col) & 0x00FFFFFF) + (DWORD(a)<<24))
#define SETR(col,r)		(((col) & 0xFF00FFFF) + (DWORD(r)<<16))
#define SETG(col,g)		(((col) & 0xFFFF00FF) + (DWORD(g)<<8))
#define SETB(col,b)		(((col) & 0xFFFFFF00) + DWORD(b))

/*
** Callback protoype used by HGE
*/
typedef bool (*hgeCallback)();

/*
** HGE_FPS system state special constants
*/
#define HGEFPS_UNLIMITED	0
#define HGEFPS_VSYNC		-1

/*
** HGE_POWERSTATUS system state special constants
*/
#define HGEPWR_AC			-1
#define HGEPWR_UNSUPPORTED	-2

/*
** HGE Primitive type constants
*/
#define HGEPRIM_LINES		2
#define HGEPRIM_TRIPLES		3
#define HGEPRIM_QUADS		4

/*
** HGE Input Event type constants
*/
#define INPUT_KEYDOWN		1
#define INPUT_KEYUP			2
#define INPUT_MBUTTONDOWN	3
#define INPUT_MBUTTONUP		4
#define INPUT_MOUSEMOVE		5
#define INPUT_MOUSEWHEEL	6

/*
** HGE Input Event flags
*/
#define HGEINP_SHIFT		1
#define HGEINP_CTRL			2
#define HGEINP_ALT			4
#define HGEINP_CAPSLOCK		8
#define HGEINP_SCROLLLOCK	16
#define HGEINP_NUMLOCK		32
#define HGEINP_REPEAT		64

extern "C" { EXPORT HGE * CALL hgeCreate(int ver); }

--]]
