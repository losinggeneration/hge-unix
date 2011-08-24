--
-- Haaf's Game Engine 1.8
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- System layer API
--

array.pushBack(gen_lua.enum_types, 'hgeBoolState', 'hgeFuncState', 'hgeHwndState', 'hgeInputEvent', 'hgeIntState', 'hgeStringState')
array.pushBack(gen_lua.number_types, 'HWND')

bindhge = {
	classes = {
		{
			name = 'hge',
			className = 'HGE_Impl',
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
				{ rename = 'system_set_hwnd_state', 'void System_SetState(hgeHwndState state, HWND value);' },
				{ rename = 'system_set_int_state', 'void System_SetState(hgeIntState state, int value);' },
				{ rename = 'system_set_string_state', 'void System_SetState(hgeStringState state, const char *value);' },
				{ rename = 'system_get_bool_state', 'bool System_GetState(hgeBoolState state);' },
-- 				{ rename = 'system_get_func_state', 'hgeCallback System_GetState(hgeFuncState state);' },
				{ rename = 'system_get_hwnd_state', 'HWND System_GetState(hgeHwndState state);' },
				{ rename = 'system_get_int_state', 'int System_GetState(hgeIntState state);' },
				{ rename = 'system_get_string_state', 'const char* System_GetState(hgeStringState state);' },
--
-- 				{ rename = 'resource_load', 'void* Resource_Load(const char *filename, DWORD *size);' },
-- 				{ rename = 'resource_free', 'void Resource_Free(void *res);' },
-- 				{ rename = 'resource_attachpack', 'bool Resource_AttachPack(const char *filename, const char *password);' },
-- 				{ rename = 'resource_removepack', 'void Resource_RemovePack(const char *filename);' },
-- 				{ rename = 'resource_removeallpacks', 'void Resource_RemoveAllPacks();' },
-- 				{ rename = 'resource_makepath', 'char* Resource_MakePath(const char *filename);' },
-- 				{ rename = 'resource_enumfiles', 'char* Resource_EnumFiles(const char *wildcard);' },
-- 				{ rename = 'resource_enumfolders', 'char* Resource_EnumFolders(const char *wildcard);' },
--
-- 				{ rename = 'ini_setint', 'void Ini_SetInt(const char *section, const char *name, int value);' },
-- 				{ rename = 'ini_getint', 'int Ini_GetInt(const char *section, const char *name, int def_val);' },
-- 				{ rename = 'ini_setfloat', 'void Ini_SetFloat(const char *section, const char *name, float value);' },
-- 				{ rename = 'ini_getfloat', 'float Ini_GetFloat(const char *section, const char *name, float def_val);' },
-- 				{ rename = 'ini_setstring', 'void Ini_SetString(const char *section, const char *name, const char *value);' },
-- 				{ rename = 'ini_getstring', 'char* Ini_GetString(const char *section, const char *name, const char *def_val);' },
--
-- 				{ rename = 'random_seed', 'void Random_Seed(int seed);' },
-- 				{ rename = 'random_int', 'int Random_Int(int min, int max);' },
-- 				{ rename = 'random_float', 'float Random_Float(float min, float max);' },
--
-- 				{ rename = 'timer_gettime', 'float Timer_GetTime();' },
-- 				{ rename = 'timer_getdelta', 'float Timer_GetDelta();' },
-- 				{ rename = 'timer_getfps', 'int Timer_GetFPS();' },
--
-- 				{ rename = 'effect_load', 'HEFFECT Effect_Load(const char *filename, DWORD size);' },
-- 				{ rename = 'effect_free', 'void Effect_Free(HEFFECT eff);' },
-- 				{ rename = 'effect_play', 'HCHANNEL Effect_Play(HEFFECT eff);' },
-- 				{ rename = 'effect_playex', 'HCHANNEL Effect_PlayEx(HEFFECT eff, int volume, int pan, float pitch, bool loop);' },
--
-- 				{ rename = 'music_load', 'HMUSIC Music_Load(const char *filename, DWORD size);' },
-- 				{ rename = 'music_free', 'void Music_Free(HMUSIC mus);' },
-- 				{ rename = 'music_play', 'HCHANNEL Music_Play(HMUSIC mus, bool loop, int volume, int order, int row);' },
-- 				{ rename = 'music_setamplification', 'void Music_SetAmplification(HMUSIC music, int ampl);' },
-- 				{ rename = 'music_getamplification', 'int Music_GetAmplification(HMUSIC music);' },
-- 				{ rename = 'music_getlength', 'int Music_GetLength(HMUSIC music);' },
-- 				{ rename = 'music_setpos', 'void Music_SetPos(HMUSIC music, int order, int row);' },
-- 				{ rename = 'music_getpos', 'bool Music_GetPos(HMUSIC music, int *order, int *row);' },
-- 				{ rename = 'music_setinstrvolume', 'void Music_SetInstrVolume(HMUSIC music, int instr, int volume);' },
-- 				{ rename = 'music_getinstrvolume', 'int Music_GetInstrVolume(HMUSIC music, int instr);' },
-- 				{ rename = 'music_setchannelvolume', 'void Music_SetChannelVolume(HMUSIC music, int channel, int volume);' },
-- 				{ rename = 'music_getchannelvolume', 'int Music_GetChannelVolume(HMUSIC music, int channel);' },
--
-- 				{ rename = 'stream_load', 'HSTREAM Stream_Load(const char *filename, DWORD size);' },
-- 				{ rename = 'stream_free', 'void Stream_Free(HSTREAM stream);' },
-- 				{ rename = 'stream_play', 'HCHANNEL Stream_Play(HSTREAM stream, bool loop, int volume);' },
--
-- 				{ rename = 'channel_setpanning', 'void Channel_SetPanning(HCHANNEL chn, int pan);' },
-- 				{ rename = 'channel_setvolume', 'void Channel_SetVolume(HCHANNEL chn, int volume);' },
-- 				{ rename = 'channel_setpitch', 'void Channel_SetPitch(HCHANNEL chn, float pitch);' },
-- 				{ rename = 'channel_pause', 'void Channel_Pause(HCHANNEL chn);' },
-- 				{ rename = 'channel_resume', 'void Channel_Resume(HCHANNEL chn);' },
-- 				{ rename = 'channel_stop', 'void Channel_Stop(HCHANNEL chn);' },
-- 				{ rename = 'channel_pauseall', 'void Channel_PauseAll();' },
-- 				{ rename = 'channel_resumeall', 'void Channel_ResumeAll();' },
-- 				{ rename = 'channel_stopall', 'void Channel_StopAll();' },
-- 				{ rename = 'channel_isplaying', 'bool Channel_IsPlaying(HCHANNEL chn);' },
-- 				{ rename = 'channel_getlength', 'float Channel_GetLength(HCHANNEL chn);' },
-- 				{ rename = 'channel_getpos', 'float Channel_GetPos(HCHANNEL chn);' },
-- 				{ rename = 'channel_setpos', 'void Channel_SetPos(HCHANNEL chn, float fSeconds);' },
-- 				{ rename = 'channel_slideto', 'void Channel_SlideTo(HCHANNEL channel, float time, int volume, int pan, float pitch);' },
-- 				{ rename = 'channel_issliding', 'bool Channel_IsSliding(HCHANNEL channel);' },
--
-- 				{ rename = 'input_getmousepos', 'void Input_GetMousePos(float *x, float *y);' },
-- 				{ rename = 'input_setmousepos', 'void Input_SetMousePos(float x, float y);' },
-- 				{ rename = 'input_getmousewheel', 'int Input_GetMouseWheel();' },
-- 				{ rename = 'input_ismouseover', 'bool Input_IsMouseOver();' },
-- 				{ rename = 'input_keydown', 'bool Input_KeyDown(int key);' },
-- 				{ rename = 'input_keyup', 'bool Input_KeyUp(int key);' },
-- 				{ rename = 'input_getkeystate', 'bool Input_GetKeyState(int key);' },
-- 				{ rename = 'input_getkeyname', 'const char* Input_GetKeyName(int key);' },
-- 				{ rename = 'input_getkey', 'int Input_GetKey();' },
-- 				{ rename = 'input_getchar', 'int Input_GetChar();' },
-- 				{ rename = 'input_getevent', 'bool Input_GetEvent(hgeInputEvent *event);' },
--
-- 				{ rename = 'gfx_beginscene', 'bool Gfx_BeginScene(HTARGET target);' },
-- 				{ rename = 'gfx_endscene', 'void Gfx_EndScene();' },
-- 				{ rename = 'gfx_clear', 'void Gfx_Clear(DWORD color);' },
-- 				{ rename = 'gfx_renderline', 'void Gfx_RenderLine(float x1, float y1, float x2, float y2, DWORD color, float z);' },
-- 				{ rename = 'gfx_rendertriple', 'void Gfx_RenderTriple(const hgeTriple *triple);' },
-- 				{ rename = 'gfx_renderquad', 'void Gfx_RenderQuad(const hgeQuad *quad);' },
-- 				{ rename = 'gfx_startbatch', 'hgeVertex* Gfx_StartBatch(int prim_type, HTEXTURE tex, int blend, int *max_prim);' },
-- 				{ rename = 'gfx_finishbatch', 'void Gfx_FinishBatch(int nprim);' },
-- 				{ rename = 'gfx_setclipping', 'void Gfx_SetClipping(int x, int y, int w, int h);' },
-- 				{ rename = 'gfx_settransform', 'void Gfx_SetTransform(float x, float y, float dx, float dy, float rot, float hscale, float vscale);' },
--
-- 				{ rename = 'target_create', 'HTARGET Target_Create(int width, int height, bool zbuffer);' },
-- 				{ rename = 'target_free', 'void Target_Free(HTARGET target);' },
-- 				{ rename = 'target_gettexture', 'HTEXTURE Target_GetTexture(HTARGET target);' },
--
-- 				{ rename = 'texture_create', 'HTEXTURE Texture_Create(int width, int height);' },
-- 				{ rename = 'texture_load', 'HTEXTURE Texture_Load(const char *filename, DWORD size, bool bMipmap);' },
-- 				{ rename = 'texture_free', 'void Texture_Free(HTEXTURE tex);' },
-- 				{ rename = 'texture_getwidth', 'int Texture_GetWidth(HTEXTURE tex, bool bOriginal);' },
-- 				{ rename = 'texture_getheight', 'int Texture_GetHeight(HTEXTURE tex, bool bOriginal);' },
-- 				{ rename = 'texture_lock', 'DWORD* Texture_Lock(HTEXTURE tex, bool bReadOnly, int left, int top, int width, int height);' },
-- 				{ rename = 'textureunlock', 'void Texture_Unlock(HTEXTURE tex);' },
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
** HGE Blending constants
*/
#define	BLEND_COLORADD		1
#define	BLEND_COLORMUL		0
#define	BLEND_ALPHABLEND	2
#define	BLEND_ALPHAADD		0
#define	BLEND_ZWRITE		4
#define	BLEND_NOZWRITE		0

#define BLEND_DEFAULT		(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE)
#define BLEND_DEFAULT_Z		(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_ZWRITE)




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
** HGE Vertex structure
*/
struct hgeVertex
{
	float			x, y;		// screen position
	float			z;			// Z-buffer depth 0..1
	DWORD			col;		// color
	float			tx, ty;		// texture coordinates
};


/*
** HGE Triple structure
*/
struct hgeTriple
{
	hgeVertex		v[3];
	HTEXTURE		tex;
	int				blend;
};


/*
** HGE Quad structure
*/
struct hgeQuad
{
	hgeVertex		v[4];
	HTEXTURE		tex;
	int				blend;
};


/*
** HGE Input Event structure
*/
struct hgeInputEvent
{
	int		type;			// event type
	int		key;			// key code
	int		flags;			// event flags
	int		chr;			// character code
	int		wheel;			// wheel shift
	float	x;				// mouse cursor x-coordinate
	float	y;				// mouse cursor y-coordinate
};


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


/*
** HGE Virtual-key codes
*/
#define HGEK_LBUTTON	0x01
#define HGEK_RBUTTON	0x02
#define HGEK_MBUTTON	0x04

#define HGEK_ESCAPE		0x1B
#define HGEK_BACKSPACE	0x08
#define HGEK_TAB		0x09
#define HGEK_ENTER		0x0D
#define HGEK_SPACE		0x20

#define HGEK_SHIFT		0x10
#define HGEK_CTRL		0x11
#define HGEK_ALT		0x12

#define HGEK_LWIN		0x5B
#define HGEK_RWIN		0x5C
#define HGEK_APPS		0x5D

#define HGEK_PAUSE		0x13
#define HGEK_CAPSLOCK	0x14
#define HGEK_NUMLOCK	0x90
#define HGEK_SCROLLLOCK	0x91

#define HGEK_PGUP		0x21
#define HGEK_PGDN		0x22
#define HGEK_HOME		0x24
#define HGEK_END		0x23
#define HGEK_INSERT		0x2D
#define HGEK_DELETE		0x2E

#define HGEK_LEFT		0x25
#define HGEK_UP			0x26
#define HGEK_RIGHT		0x27
#define HGEK_DOWN		0x28

#define HGEK_0			0x30
#define HGEK_1			0x31
#define HGEK_2			0x32
#define HGEK_3			0x33
#define HGEK_4			0x34
#define HGEK_5			0x35
#define HGEK_6			0x36
#define HGEK_7			0x37
#define HGEK_8			0x38
#define HGEK_9			0x39

#define HGEK_A			0x41
#define HGEK_B			0x42
#define HGEK_C			0x43
#define HGEK_D			0x44
#define HGEK_E			0x45
#define HGEK_F			0x46
#define HGEK_G			0x47
#define HGEK_H			0x48
#define HGEK_I			0x49
#define HGEK_J			0x4A
#define HGEK_K			0x4B
#define HGEK_L			0x4C
#define HGEK_M			0x4D
#define HGEK_N			0x4E
#define HGEK_O			0x4F
#define HGEK_P			0x50
#define HGEK_Q			0x51
#define HGEK_R			0x52
#define HGEK_S			0x53
#define HGEK_T			0x54
#define HGEK_U			0x55
#define HGEK_V			0x56
#define HGEK_W			0x57
#define HGEK_X			0x58
#define HGEK_Y			0x59
#define HGEK_Z			0x5A

#define HGEK_GRAVE		0xC0
#define HGEK_MINUS		0xBD
#define HGEK_EQUALS		0xBB
#define HGEK_BACKSLASH	0xDC
#define HGEK_LBRACKET	0xDB
#define HGEK_RBRACKET	0xDD
#define HGEK_SEMICOLON	0xBA
#define HGEK_APOSTROPHE	0xDE
#define HGEK_COMMA		0xBC
#define HGEK_PERIOD		0xBE
#define HGEK_SLASH		0xBF

#define HGEK_NUMPAD0	0x60
#define HGEK_NUMPAD1	0x61
#define HGEK_NUMPAD2	0x62
#define HGEK_NUMPAD3	0x63
#define HGEK_NUMPAD4	0x64
#define HGEK_NUMPAD5	0x65
#define HGEK_NUMPAD6	0x66
#define HGEK_NUMPAD7	0x67
#define HGEK_NUMPAD8	0x68
#define HGEK_NUMPAD9	0x69

#define HGEK_MULTIPLY	0x6A
#define HGEK_DIVIDE		0x6F
#define HGEK_ADD		0x6B
#define HGEK_SUBTRACT	0x6D
#define HGEK_DECIMAL	0x6E

#define HGEK_F1			0x70
#define HGEK_F2			0x71
#define HGEK_F3			0x72
#define HGEK_F4			0x73
#define HGEK_F5			0x74
#define HGEK_F6			0x75
#define HGEK_F7			0x76
#define HGEK_F8			0x77
#define HGEK_F9			0x78
#define HGEK_F10		0x79
#define HGEK_F11		0x7A
#define HGEK_F12		0x7B

--]]
