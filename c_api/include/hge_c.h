#ifndef HGE_C_API_H
#define HGE_C_API_H
#define HGE_C_API

#include "unix_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WINDOWS) || defined(WIN32)
#include <windows.h>
#endif

#define HGE_VERSION 0x181

#ifndef EXPORT
#  ifdef HGEDLL
#    ifdef _WINDOWS
#      define EXPORT __declspec(dllexport)
#    elif (__GNUC__ >= 3)
#      define EXPORT __attribute__((visibility("default")))
#    else
#      define EXPORT
#    endif
#  else
#    define EXPORT
#  endif
#endif

#ifdef _WINDOWS
#define CALL  __stdcall
#else
#define CALL
#endif

#ifdef __BORLANDC__
#define floorf (float)floor
#define sqrtf (float)sqrt
#define acosf (float)acos
#define atan2f (float)atan2
#define cosf (float)cos
#define sinf (float)sin
#define powf (float)pow
#define fabsf (float)fabs

#define min(x,y) ((x) < (y)) ? (x) : (y)
#define max(x,y) ((x) > (y)) ? (x) : (y)
#endif


/*
 * * Common data types
 */
#ifdef _WINDOWS
#ifndef DWORD
typedef unsigned long       DWORD;
typedef unsigned short      WORD;
typedef unsigned char       BYTE;
#endif
#endif

/*
 * * Common math constants
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
 * * HGE Handle types
 */
typedef size_t HTEXTURE;
typedef size_t HTARGET;
typedef size_t HEFFECT;
typedef size_t HMUSIC;
typedef size_t HSTREAM;
typedef size_t HCHANNEL;


/*
 * * Hardware color macros
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
 * * HGE Blending constants
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
 * * HGE System state constants
 */
typedef enum HGE_BoolState_e
{
	HGE_C_WINDOWED		= 1,    // bool		run in window?		(default: false)
	HGE_C_ZBUFFER			= 2,    // bool		use z-buffer?		(default: false)
	HGE_C_TEXTUREFILTER	= 3,    // bool		texture filtering?	(default: true)

	HGE_C_USESOUND		= 4,    // bool		use BASS for sound?	(default: true)

	HGE_C_DONTSUSPEND		= 5,	// bool		focus lost:suspend?	(default: false)
	HGE_C_HIDEMOUSE		= 6,	// bool		hide system cursor?	(default: true)

	HGE_C_SHOWSPLASH		= 7,	// bool		hide system cursor?	(default: true)

	HGE_C_BOOLSTATE_FORCE_DWORD = 0x7FFFFFFF
} HGE_BoolState_t;

typedef enum HGE_FuncState_e
{
	HGE_C_FRAMEFUNC		= 8,    // bool*()	frame function		(default: NULL) (you MUST set this)
	HGE_C_RENDERFUNC		= 9,    // bool*()	render function		(default: NULL)
	HGE_C_FOCUSLOSTFUNC	= 10,   // bool*()	focus lost function	(default: NULL)
	HGE_C_FOCUSGAINFUNC	= 11,   // bool*()	focus gain function	(default: NULL)
	HGE_C_GFXRESTOREFUNC	= 12,   // bool*()	exit function		(default: NULL)
	HGE_C_EXITFUNC		= 13,   // bool*()	exit function		(default: NULL)

	HGE_C_FUNCSTATE_FORCE_DWORD = 0x7FFFFFFF
} HGE_FuncState_t;

typedef enum HGE_HwndState_e
{
	HGE_C_HWND			= 15,	// int		window handle: read only
	HGE_C_HWNDPARENT		= 16,	// int		parent win handle	(default: 0)

	HGE_C_HWNDSTATE_FORCE_DWORD = 0x7FFFFFFF
} HGE_HwndState_t;

typedef enum HGE_IntState_e
{
	HGE_C_SCREENWIDTH		= 17,   // int		screen width		(default: 800)
	HGE_C_SCREENHEIGHT	= 18,   // int		screen height		(default: 600)
	HGE_C_SCREENBPP		= 19,   // int		screen bitdepth		(default: 32) (desktop bpp in windowed mode)

	HGE_C_SAMPLERATE		= 20,   // int		sample rate			(default: 44100)
	HGE_C_FXVOLUME		= 21,   // int		global fx volume	(default: 100)
	HGE_C_MUSVOLUME		= 22,   // int		global music volume	(default: 100)
	HGE_C_STREAMVOLUME	= 23,   // int		global music volume	(default: 100)

	HGE_C_FPS				= 24,	// int		fixed fps			(default: HGEFPS_UNLIMITED)

	HGE_C_POWERSTATUS		= 25,   // int		battery life percent + status

	HGE_C_ORIGSCREENWIDTH		= 30,   // int		original screen width		(default: 800 ... not valid until HGE_C_->System_Initiate()!)
	HGE_C_ORIGSCREENHEIGHT	= 31,   // int		original screen height		(default: 600 ... not valid until HGE_C_->System_Initiate()!))

	HGE_C_INTSTATE_FORCE_DWORD = 0x7FFFFFF
} HGE_IntState_t;

typedef enum HGE_StringState_e
{
	HGE_C_ICON			= 26,   // char*	icon resource		(default: NULL)
	HGE_C_TITLE			= 27,   // char*	window title		(default: "HGE")

	HGE_C_INIFILE			= 28,   // char*	ini file			(default: NULL) (meaning no file)
	HGE_C_LOGFILE			= 29,   // char*	log file			(default: NULL) (meaning no file)

	HGE_C_STRINGSTATE_FORCE_DWORD = 0x7FFFFFFF
} HGE_StringState_t;

/*
 * * Callback protoype used by HGE
 */
typedef BOOL (*HGE_Callback)();


/*
 * * HGE_FPS system state special constants
 */
#define HGE_FPS_UNLIMITED	0
#define HGE_FPS_VSYNC		-1


/*
 * * HGE_POWERSTATUS system state special constants
 */
#define HGE_PWR_AC			-1
#define HGE_PWR_UNSUPPORTED	-2


/*
 * * HGE Primitive type constants
 */
#define HGE_PRIM_LINES		2
#define HGE_PRIM_TRIPLES		3
#define HGE_PRIM_QUADS		4


/*
 * * HGE Vertex structure
 */
typedef struct HGE_Vertex_s
{
	float			x, y;		// screen position
	float			z;			// Z-buffer depth 0..1
	DWORD			col;		// color
	float			tx, ty;		// texture coordinates
} HGE_Vertex_t;


/*
 * * HGE Triple structure
 */
typedef struct HGE_Triple_s
{
	HGE_Vertex_t		v[3];
	HTEXTURE		tex;
	int				blend;
} HGE_Triple_t;


/*
 * * HGE Quad structure
 */
typedef struct HGE_Quad_s
{
	HGE_Vertex_t		v[4];
	HTEXTURE		tex;
	int				blend;
} HGE_Quad_t;


/*
 * * HGE Input Event structure
 */
typedef struct HGE_InputEvent_s
{
	int		type;			// event type
	int		key;			// key code
	int		flags;			// event flags
	int		chr;			// character code
	int		wheel;			// wheel shift
	float	x;				// mouse cursor x-coordinate
	float	y;				// mouse cursor y-coordinate
} HGE_InputEvent_t;


/*
 * * HGE Input Event type constants
 */
#define HGE_INPUT_KEYDOWN		1
#define HGE_INPUT_KEYUP			2
#define HGE_INPUT_MBUTTONDOWN	3
#define HGE_INPUT_MBUTTONUP		4
#define HGE_INPUT_MOUSEMOVE		5
#define HGE_INPUT_MOUSEWHEEL	6


/*
 * * HGE Input Event flags
 */
#define HGE_INP_SHIFT		1
#define HGE_INP_CTRL		2
#define HGE_INP_ALT			4
#define HGE_INP_CAPSLOCK	8
#define HGE_INP_SCROLLLOCK	16
#define HGE_INP_NUMLOCK		32
#define HGE_INP_REPEAT		64


/*
 * * HGE Interface class
 */
typedef struct HGE_s HGE_t;

HGE_t* HGE_Create(int ver);

void HGE_Release(HGE_t *hge);
BOOL HGE_System_Initiate(HGE_t *hge);
void HGE_System_Shutdown(HGE_t *hge);
BOOL HGE_System_Start(HGE_t *hge);
const char* HGE_System_GetErrorMessage(HGE_t *hge);
void HGE_System_Log(HGE_t *hge, const char *format, ...);
BOOL HGE_System_Launch(HGE_t *hge, const char *url);
void HGE_System_Snapshot(HGE_t *hge, const char *filename);
void HGE_System_SetStateBool(HGE_t *hge, HGE_BoolState_t state, BOOL value);
void HGE_System_SetStateFunc(HGE_t *hge, HGE_FuncState_t state, HGE_Callback value);
void HGE_System_SetStateHwnd(HGE_t *hge, HGE_HwndState_t state, HWND value);
void HGE_System_SetStateInt (HGE_t *hge, HGE_IntState_t state, int value);
void HGE_System_SetStateString(HGE_t *hge, HGE_StringState_t state, const char *value);
BOOL HGE_System_GetStateBool(HGE_t *hge, HGE_BoolState_t state);
HGE_Callback HGE_System_GetStateFunc(HGE_t *hge, HGE_FuncState_t state);
HWND HGE_System_GetStateHwnd(HGE_t *hge, HGE_HwndState_t state);
int HGE_System_GetStateInt(HGE_t *hge, HGE_IntState_t state);
const char* HGE_System_GetStateString(HGE_t *hge, HGE_StringState_t state);
void* HGE_Resource_Load(HGE_t *hge, const char *filename, DWORD *size);
void HGE_Resource_Free(HGE_t *hge, void *res);
BOOL HGE_Resource_AttachPack(HGE_t *hge, const char *filename, const char *password);
void HGE_Resource_RemovePack(HGE_t *hge, const char *filename);
void HGE_Resource_RemoveAllPacks(HGE_t *hge);
char* HGE_Resource_MakePath(HGE_t *hge, const char *filename);
char* HGE_Resource_EnumFiles(HGE_t *hge, const char *wildcard);
char* HGE_Resource_EnumFolders(HGE_t *hge, const char *wildcard);
void HGE_Ini_SetInt(HGE_t *hge, const char *section, const char *name, int value);
int HGE_Ini_GetInt(HGE_t *hge, const char *section, const char *name, int def_val);
void HGE_Ini_SetFloat(HGE_t *hge, const char *section, const char *name, float value);
float HGE_Ini_GetFloat(HGE_t *hge, const char *section, const char *name, float def_val);
void HGE_Ini_SetString(HGE_t *hge, const char *section, const char *name, const char *value);
char* HGE_Ini_GetString(HGE_t *hge, const char *section, const char *name, const char *def_val);
void HGE_Random_Seed(HGE_t *hge, int seed);
int HGE_Random_Int(HGE_t *hge, int min, int max);
float HGE_Random_Float(HGE_t *hge, float min, float max);
float HGE_Timer_GetTime(HGE_t *hge);
float HGE_Timer_GetDelta(HGE_t *hge);
int HGE_Timer_GetFPS(HGE_t *hge);
/// DWORD size=0
HEFFECT HGE_Effect_Load(HGE_t *hge, const char *filename, DWORD size);
void HGE_Effect_Free(HGE_t *hge, HEFFECT eff);
HCHANNEL HGE_Effect_Play(HGE_t *hge, HEFFECT eff);
/// int volume=100, int pan=0, float pitch=1.0f, bool loop=false
HCHANNEL HGE_Effect_PlayEx(HGE_t *hge, HEFFECT eff, int volume, int pan, float pitch, BOOL loop);
HMUSIC HGE_Music_Load(HGE_t *hge, const char *filename, DWORD size);
void HGE_Music_Free(HGE_t *hge, HMUSIC mus);
HCHANNEL HGE_Music_Play(HGE_t *hge, HMUSIC mus, BOOL loop, int volume, int order, int row);
void HGE_Music_SetAmplification(HGE_t *hge, HMUSIC music, int ampl);
int HGE_Music_GetAmplification(HGE_t *hge, HMUSIC music);
int HGE_Music_GetLength(HGE_t *hge, HMUSIC music);
void HGE_Music_SetPos(HGE_t *hge, HMUSIC music, int order, int row);
BOOL HGE_Music_GetPos(HGE_t *hge, HMUSIC music, int *order, int *row);
void HGE_Music_SetInstrVolume(HGE_t *hge, HMUSIC music, int instr, int volume);
int HGE_Music_GetInstrVolume(HGE_t *hge, HMUSIC music, int instr);
void HGE_Music_SetChannelVolume(HGE_t *hge, HMUSIC music, int channel, int volume);
int HGE_Music_GetChannelVolume(HGE_t *hge, HMUSIC music, int channel);
HSTREAM HGE_Stream_Load(HGE_t *hge, const char *filename, DWORD size);
void HGE_Stream_Free(HGE_t *hge, HSTREAM stream);
HCHANNEL HGE_Stream_Play(HGE_t *hge, HSTREAM stream, BOOL loop, int volume);
void HGE_Channel_SetPanning(HGE_t *hge, HCHANNEL chn, int pan);
void HGE_Channel_SetVolume(HGE_t *hge, HCHANNEL chn, int volume);
void HGE_Channel_SetPitch(HGE_t *hge, HCHANNEL chn, float pitch);
void HGE_Channel_Pause(HGE_t *hge, HCHANNEL chn);
void HGE_Channel_Resume(HGE_t *hge, HCHANNEL chn);
void HGE_Channel_Stop(HGE_t *hge, HCHANNEL chn);
void HGE_Channel_PauseAll(HGE_t *hge);
void HGE_Channel_ResumeAll(HGE_t *hge);
void HGE_Channel_StopAll(HGE_t *hge);
BOOL HGE_Channel_IsPlaying(HGE_t *hge, HCHANNEL chn);
float HGE_Channel_GetLength(HGE_t *hge, HCHANNEL chn);
float HGE_Channel_GetPos(HGE_t *hge, HCHANNEL chn);
void HGE_Channel_SetPos(HGE_t *hge, HCHANNEL chn, float fSeconds);
void HGE_Channel_SlideTo(HGE_t *hge, HCHANNEL channel, float time, int volume, int pan, float pitch);
BOOL HGE_Channel_IsSliding(HGE_t *hge, HCHANNEL channel);
void HGE_Input_GetMousePos(HGE_t *hge, float *x, float *y);
void HGE_Input_SetMousePos(HGE_t *hge, float x, float y);
int HGE_Input_GetMouseWheel(HGE_t *hge);
BOOL HGE_Input_IsMouseOver(HGE_t *hge);
BOOL HGE_Input_KeyDown(HGE_t *hge, int key);
BOOL HGE_Input_KeyUp(HGE_t *hge, int key);
BOOL HGE_Input_GetKeyState(HGE_t *hge, int key);
const char* HGE_Input_GetKeyName(HGE_t *hge, int key);
int HGE_Input_GetKey(HGE_t *hge);
int HGE_Input_GetChar(HGE_t *hge);
BOOL HGE_Input_GetEvent(HGE_t *hge, HGE_InputEvent_t *event);
/// HTARGET target=0
BOOL HGE_Gfx_BeginScene(HGE_t *hge, HTARGET target);
void HGE_Gfx_EndScene(HGE_t *hge);
void HGE_Gfx_Clear(HGE_t *hge, DWORD color);
void HGE_Gfx_RenderLine(HGE_t *hge, float x1, float y1, float x2, float y2, DWORD color, float z);
void HGE_Gfx_RenderTriple(HGE_t *hge, const HGE_Triple_t *triple);
void HGE_Gfx_RenderQuad(HGE_t *hge, const HGE_Quad_t *quad);
HGE_Vertex_t* HGE_Gfx_StartBatch(HGE_t *hge, int prim_type, HTEXTURE tex, int blend, int *max_prim);
void HGE_Gfx_FinishBatch(HGE_t *hge, int nprim);
void HGE_Gfx_SetClipping(HGE_t *hge, int x, int y, int w, int h);
void HGE_Gfx_SetTransform(HGE_t *hge, float x, float y, float dx, float dy, float rot, float hscale, float vscale);
HTARGET HGE_Target_Create(HGE_t *hge, int width, int height, BOOL zbuffer);
void HGE_Target_Free(HGE_t *hge, HTARGET target);
HTEXTURE HGE_Target_GetTexture(HGE_t *hge, HTARGET target);
HTEXTURE HGE_Texture_Create(HGE_t *hge, int width, int height);
/// DWORD size=0, bool bMipmap=false
HTEXTURE HGE_Texture_Load(HGE_t *hge, const char *filename, DWORD size, BOOL bMipmap);
void HGE_Texture_Free(HGE_t *hge, HTEXTURE tex);
int HGE_Texture_GetWidth(HGE_t *hge, HTEXTURE tex, BOOL bOriginal);
int HGE_Texture_GetHeight(HGE_t *hge, HTEXTURE tex, BOOL bOriginal);
DWORD* HGE_Texture_Lock(HGE_t *hge, HTEXTURE tex, BOOL bReadOnly, int left, int top, int width, int height);
void HGE_Texture_Unlock(HGE_t *hge, HTEXTURE tex);

/*
 * * HGE_ Virtual-key codes
 */
#define HGE_K_LBUTTON	0x01
#define HGE_K_RBUTTON	0x02
#define HGE_K_MBUTTON	0x04

#define HGE_K_ESCAPE	0x1B
#define HGE_K_BACKSPACE	0x08
#define HGE_K_TAB		0x09
#define HGE_K_ENTER		0x0D
#define HGE_K_SPACE		0x20

#define HGE_K_SHIFT		0x10
#define HGE_K_CTRL		0x11
#define HGE_K_ALT		0x12

#define HGE_K_LWIN		0x5B
#define HGE_K_RWIN		0x5C
#define HGE_K_APPS		0x5D

#define HGE_K_PAUSE		0x13
#define HGE_K_CAPSLOCK	0x14
#define HGE_K_NUMLOCK	0x90
#define HGE_K_SCROLLLOCK 0x91

#define HGE_K_PGUP		0x21
#define HGE_K_PGDN		0x22
#define HGE_K_HOME		0x24
#define HGE_K_END		0x23
#define HGE_K_INSERT	0x2D
#define HGE_K_DELETE	0x2E

#define HGE_K_LEFT		0x25
#define HGE_K_UP		0x26
#define HGE_K_RIGHT		0x27
#define HGE_K_DOWN		0x28

#define HGE_K_0			0x30
#define HGE_K_1			0x31
#define HGE_K_2			0x32
#define HGE_K_3			0x33
#define HGE_K_4			0x34
#define HGE_K_5			0x35
#define HGE_K_6			0x36
#define HGE_K_7			0x37
#define HGE_K_8			0x38
#define HGE_K_9			0x39

#define HGE_K_A			0x41
#define HGE_K_B			0x42
#define HGE_K_C			0x43
#define HGE_K_D			0x44
#define HGE_K_E			0x45
#define HGE_K_F			0x46
#define HGE_K_G			0x47
#define HGE_K_H			0x48
#define HGE_K_I			0x49
#define HGE_K_J			0x4A
#define HGE_K_K			0x4B
#define HGE_K_L			0x4C
#define HGE_K_M			0x4D
#define HGE_K_N			0x4E
#define HGE_K_O			0x4F
#define HGE_K_P			0x50
#define HGE_K_Q			0x51
#define HGE_K_R			0x52
#define HGE_K_S			0x53
#define HGE_K_T			0x54
#define HGE_K_U			0x55
#define HGE_K_V			0x56
#define HGE_K_W			0x57
#define HGE_K_X			0x58
#define HGE_K_Y			0x59
#define HGE_K_Z			0x5A

#define HGE_K_GRAVE		0xC0
#define HGE_K_MINUS		0xBD
#define HGE_K_EQUALS	0xBB
#define HGE_K_BACKSLASH	0xDC
#define HGE_K_LBRACKET	0xDB
#define HGE_K_RBRACKET	0xDD
#define HGE_K_SEMICOLON	0xBA
#define HGE_K_APOSTROPHE 0xDE
#define HGE_K_COMMA		0xBC
#define HGE_K_PERIOD	0xBE
#define HGE_K_SLASH		0xBF

#define HGE_K_NUMPAD0	0x60
#define HGE_K_NUMPAD1	0x61
#define HGE_K_NUMPAD2	0x62
#define HGE_K_NUMPAD3	0x63
#define HGE_K_NUMPAD4	0x64
#define HGE_K_NUMPAD5	0x65
#define HGE_K_NUMPAD6	0x66
#define HGE_K_NUMPAD7	0x67
#define HGE_K_NUMPAD8	0x68
#define HGE_K_NUMPAD9	0x69

#define HGE_K_MULTIPLY	0x6A
#define HGE_K_DIVIDE	0x6F
#define HGE_K_ADD		0x6B
#define HGE_K_SUBTRACT	0x6D
#define HGE_K_DECIMAL	0x6E

#define HGE_K_F1		0x70
#define HGE_K_F2		0x71
#define HGE_K_F3		0x72
#define HGE_K_F4		0x73
#define HGE_K_F5		0x74
#define HGE_K_F6		0x75
#define HGE_K_F7		0x76
#define HGE_K_F8		0x77
#define HGE_K_F9		0x78
#define HGE_K_F10		0x79
#define HGE_K_F11		0x7A
#define HGE_K_F12		0x7B

#ifdef __cplusplus
}
#endif

#endif
