#include "hge.h"
#include "hge_c.h"
#include "hge_impl.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdarg.h>

extern "C" {

HGE_t * HGE_Create(int ver) {
	HGE_t *hge = (HGE_t *)malloc(sizeof(HGE_t));

	// Make sure malloc was successful
	if (hge == NULL) {
		return NULL;
	}

	hge->h = hgeCreate(ver);

	return hge;
}

void HGE_Release(HGE_t *hge) {
	hge->h->Release();
	free(hge);
	hge = NULL;
}

BOOL HGE_System_Initiate(HGE_t *hge) {
	return hge->h->System_Initiate();
}

void HGE_System_Shutdown(HGE_t *hge) {
	hge->h->System_Shutdown();
}

BOOL HGE_System_Start(HGE_t *hge) {
	return hge->h->System_Start();
}

const char* HGE_System_GetErrorMessage(HGE_t *hge) {
	return hge->h->System_GetErrorMessage();
}

void HGE_System_Log(HGE_t *hge, const char *format, ...) {
	char *str;
	// We'll try to be sufficiently large, but for long variable conversions,
	// it may not be enough
	int len = strlen(format)+1024;
	str = (char *)malloc(len * sizeof(char));

	va_list ap;
	va_start(ap, format);
	int n = vsnprintf(str, len, format, ap);
	va_end(ap);

	// Warn if we're at capacity for str
	if(n < 0 || n == len) {
		hge->h->System_Log("The following message may be truncated because it's longer than format(%d) + 1024", strlen(format));
	}

	hge->h->System_Log(str);
	free(str);
}

BOOL HGE_System_Launch(HGE_t *hge, const char *url) {
	return hge->h->System_Launch(url);
}

void HGE_System_Snapshot(HGE_t *hge, const char *filename) {
	hge->h->System_Snapshot(filename);
}

void HGE_System_SetStateBool(HGE_t *hge, HGE_BoolState_t state, BOOL value) {
	hge->h->System_SetState((hgeBoolState)state, (bool)value);
}

void HGE_System_SetStateFunc(HGE_t *hge, HGE_FuncState_t state, HGE_Callback value) {
	hge->h->System_SetState((hgeFuncState)state, (hgeCallback)value);
}

void HGE_System_SetStateHwnd(HGE_t *hge, HGE_HwndState_t state, HWND value) {
	hge->h->System_SetState((hgeHwndState)state, value);
}

void HGE_System_SetStateInt (HGE_t *hge, HGE_IntState_t state, int value) {
	hge->h->System_SetState((hgeIntState)state, value);
}

void HGE_System_SetStateString(HGE_t *hge, HGE_StringState_t state, const char *value) {
	hge->h->System_SetState((hgeStringState)state, value);
}

BOOL HGE_System_GetStateBool(HGE_t *hge, HGE_BoolState_t state) {
	return hge->h->System_GetState((hgeBoolState)state);
}

HGE_Callback HGE_System_GetStateFunc(HGE_t *hge, HGE_FuncState_t state) {
	return (HGE_Callback)hge->h->System_GetState((hgeFuncState)state);
}

HWND HGE_System_GetStateHwnd(HGE_t *hge, HGE_HwndState_t state) {
	return hge->h->System_GetState((hgeHwndState)state);
}

int HGE_System_GetStateInt(HGE_t *hge, HGE_IntState_t state) {
	return hge->h->System_GetState((hgeIntState)state);
}

const char* HGE_System_GetStateString(HGE_t *hge, HGE_StringState_t state) {
	return hge->h->System_GetState((hgeStringState)state);
}

void* HGE_Resource_Load(HGE_t *hge, const char *filename, DWORD *size) {
	return hge->h->Resource_Load(filename, size);
}

void HGE_Resource_Free(HGE_t *hge, void *res) {
	hge->h->Resource_Free(res);
}

BOOL HGE_Resource_AttachPack(HGE_t *hge, const char *filename, const char *password) {
	return hge->h->Resource_AttachPack(filename, password);
}

void HGE_Resource_RemovePack(HGE_t *hge, const char *filename) {
	hge->h->Resource_RemovePack(filename);
}

void HGE_Resource_RemoveAllPacks(HGE_t *hge) {
	hge->h->Resource_RemoveAllPacks();
}

char* HGE_Resource_MakePath(HGE_t *hge, const char *filename) {
	return hge->h->Resource_MakePath(filename);
}

char* HGE_Resource_EnumFiles(HGE_t *hge, const char *wildcard) {
	return hge->h->Resource_EnumFiles(wildcard);
}

char* HGE_Resource_EnumFolders(HGE_t *hge, const char *wildcard) {
	return hge->h->Resource_EnumFolders(wildcard);
}

void HGE_Ini_SetInt(HGE_t *hge, const char *section, const char *name, int value) {
	hge->h->Ini_SetInt(section, name, value);
}

int HGE_Ini_GetInt(HGE_t *hge, const char *section, const char *name, int def_val) {
	return hge->h->Ini_GetInt(section, name, def_val);
}

void HGE_Ini_SetFloat(HGE_t *hge, const char *section, const char *name, float value) {
	hge->h->Ini_SetFloat(section, name, value);
}

float HGE_Ini_GetFloat(HGE_t *hge, const char *section, const char *name, float def_val) {
	return hge->h->Ini_GetFloat(section, name, def_val);
}

void HGE_Ini_SetString(HGE_t *hge, const char *section, const char *name, const char *value) {
	hge->h->Ini_SetString(section, name, value);
}

char* HGE_Ini_GetString(HGE_t *hge, const char *section, const char *name, const char *def_val) {
	return hge->h->Ini_GetString(section, name, def_val);
}

void HGE_Random_Seed(HGE_t *hge, int seed) {
	hge->h->Random_Seed(seed);
}

int HGE_Random_Int(HGE_t *hge, int min, int max) {
	return hge->h->Random_Int(min, max);
}

float HGE_Random_Float(HGE_t *hge, float min, float max) {
	return hge->h->Random_Float(min, max);
}

float HGE_Timer_GetTime(HGE_t *hge) {
	return hge->h->Timer_GetTime();
}

float HGE_Timer_GetDelta(HGE_t *hge) {
	return hge->h->Timer_GetDelta();
}

int HGE_Timer_GetFPS(HGE_t *hge) {
	return hge->h->Timer_GetFPS();
}

HEFFECT HGE_Effect_Load(HGE_t *hge, const char *filename, DWORD size) {
	return hge->h->Effect_Load(filename, size);
}

void HGE_Effect_Free(HGE_t *hge, HEFFECT eff) {
	hge->h->Effect_Free(eff);
}

HCHANNEL HGE_Effect_Play(HGE_t *hge, HEFFECT eff) {
	return hge->h->Effect_Play(eff);
}

HCHANNEL HGE_Effect_PlayEx(HGE_t *hge, HEFFECT eff, int volume, int pan, float pitch, BOOL loop) {
	return hge->h->Effect_PlayEx(eff, volume, pan, pitch, loop);
}

HMUSIC HGE_Music_Load(HGE_t *hge, const char *filename, DWORD size) {
	return hge->h->Music_Load(filename, size);
}

void HGE_Music_Free(HGE_t *hge, HMUSIC mus) {
	hge->h->Music_Free(mus);
}

HCHANNEL HGE_Music_Play(HGE_t *hge, HMUSIC mus, BOOL loop, int volume, int order, int row) {
	return hge->h->Music_Play(mus, loop, volume, order, row);
}

void HGE_Music_SetAmplification(HGE_t *hge, HMUSIC music, int ampl) {
	hge->h->Music_SetAmplification(music, ampl);
}

int HGE_Music_GetAmplification(HGE_t *hge, HMUSIC music) {
	return hge->h->Music_GetAmplification(music);
}

int HGE_Music_GetLength(HGE_t *hge, HMUSIC music) {
	return hge->h->Music_GetLength(music);
}

void HGE_Music_SetPos(HGE_t *hge, HMUSIC music, int order, int row) {
	return hge->h->Music_SetPos(music, order, row);
}

BOOL HGE_Music_GetPos(HGE_t *hge, HMUSIC music, int *order, int *row) {
	return hge->h->Music_GetPos(music, order, row);
}

void HGE_Music_SetInstrVolume(HGE_t *hge, HMUSIC music, int instr, int volume) {
	hge->h->Music_SetInstrVolume(music, instr, volume);
}

int HGE_Music_GetInstrVolume(HGE_t *hge, HMUSIC music, int instr) {
	return hge->h->Music_GetInstrVolume(music, instr);
}

void HGE_Music_SetChannelVolume(HGE_t *hge, HMUSIC music, int channel, int volume) {
	hge->h->Music_SetChannelVolume(music, channel, volume);
}

int HGE_Music_GetChannelVolume(HGE_t *hge, HMUSIC music, int channel) {
	return hge->h->Music_GetChannelVolume(music, channel);
}

HSTREAM HGE_Stream_Load(HGE_t *hge, const char *filename, DWORD size) {
	return hge->h->Stream_Load(filename, size);
}

void HGE_Stream_Free(HGE_t *hge, HSTREAM stream) {
	hge->h->Stream_Free(stream);
}

HCHANNEL HGE_Stream_Play(HGE_t *hge, HSTREAM stream, BOOL loop, int volume) {
	return hge->h->Stream_Play(stream, loop, volume);
}

void HGE_Channel_SetPanning(HGE_t *hge, HCHANNEL chn, int pan) {
	hge->h->Channel_SetPanning(chn, pan);
}

void HGE_Channel_SetVolume(HGE_t *hge, HCHANNEL chn, int volume) {
	hge->h->Channel_SetVolume(chn, volume);
}

void HGE_Channel_SetPitch(HGE_t *hge, HCHANNEL chn, float pitch) {
	hge->h->Channel_SetPitch(chn, pitch);
}

void HGE_Channel_Pause(HGE_t *hge, HCHANNEL chn) {
	hge->h->Channel_Pause(chn);
}

void HGE_Channel_Resume(HGE_t *hge, HCHANNEL chn) {
	hge->h->Channel_Resume(chn);
}

void HGE_Channel_Stop(HGE_t *hge, HCHANNEL chn) {
	hge->h->Channel_Stop(chn);
}

void HGE_Channel_PauseAll(HGE_t *hge) {
	hge->h->Channel_PauseAll();
}

void HGE_Channel_ResumeAll(HGE_t *hge) {
	hge->h->Channel_ResumeAll();
}

void HGE_Channel_StopAll(HGE_t *hge) {
	hge->h->Channel_StopAll();
}

BOOL HGE_Channel_IsPlaying(HGE_t *hge, HCHANNEL chn) {
	return hge->h->Channel_IsPlaying(chn);
}

float HGE_Channel_GetLength(HGE_t *hge, HCHANNEL chn) {
	return hge->h->Channel_GetLength(chn);
}

float HGE_Channel_GetPos(HGE_t *hge, HCHANNEL chn) {
	return hge->h->Channel_GetPos(chn);
}

void HGE_Channel_SetPos(HGE_t *hge, HCHANNEL chn, float fSeconds) {
	hge->h->Channel_SetPos(chn, fSeconds);
}

void HGE_Channel_SlideTo(HGE_t *hge, HCHANNEL channel, float time, int volume, int pan, float pitch) {
	hge->h->Channel_SlideTo(channel, time, volume, pan, pitch);
}

BOOL HGE_Channel_IsSliding(HGE_t *hge, HCHANNEL channel) {
	return hge->h->Channel_IsSliding(channel);
}

void HGE_Input_GetMousePos(HGE_t *hge, float *x, float *y) {
	hge->h->Input_GetMousePos(x, y);
}

void HGE_Input_SetMousePos(HGE_t *hge, float x, float y) {
	hge->h->Input_SetMousePos(x, y);
}

int HGE_Input_GetMouseWheel(HGE_t *hge) {
	return hge->h->Input_GetMouseWheel();
}

BOOL HGE_Input_IsMouseOver(HGE_t *hge) {
	return hge->h->Input_IsMouseOver();
}

BOOL HGE_Input_KeyDown(HGE_t *hge, int key) {
	return hge->h->Input_KeyDown(key);
}

BOOL HGE_Input_KeyUp(HGE_t *hge, int key) {
	return hge->h->Input_KeyUp(key);
}

BOOL HGE_Input_GetKeyState(HGE_t *hge, int key) {
	return hge->h->Input_GetKeyState(key);
}

const char* HGE_Input_GetKeyName(HGE_t *hge, int key) {
	return hge->h->Input_GetKeyName(key);
}

int HGE_Input_GetKey(HGE_t *hge) {
	return hge->h->Input_GetKey();
}

int HGE_Input_GetChar(HGE_t *hge) {
	return hge->h->Input_GetChar();
}

BOOL HGE_Input_GetEvent(HGE_t *hge, HGE_InputEvent_t *event) {
	return hge->h->Input_GetEvent((hgeInputEvent *)event);
}

BOOL HGE_Gfx_BeginScene(HGE_t *hge, HTARGET target) {
	return hge->h->Gfx_BeginScene(target);
}

void HGE_Gfx_EndScene(HGE_t *hge) {
	hge->h->Gfx_EndScene();
}

void HGE_Gfx_Clear(HGE_t *hge, DWORD color) {
	hge->h->Gfx_Clear(color);
}

void HGE_Gfx_RenderLine(HGE_t *hge, float x1, float y1, float x2, float y2, DWORD color, float z) {
	hge->h->Gfx_RenderLine(x1, y1, x2, y2, color, z);
}

void HGE_Gfx_RenderTriple(HGE_t *hge, const HGE_Triple_t *triple) {
	hge->h->Gfx_RenderTriple((hgeTriple *) triple);
}

void HGE_Gfx_RenderQuad(HGE_t *hge, const HGE_Quad_t *quad) {
	hge->h->Gfx_RenderQuad((hgeQuad *)quad);
}

HGE_Vertex_t* HGE_Gfx_StartBatch(HGE_t *hge, int prim_type, HTEXTURE tex, int blend, int *max_prim) {
	return (HGE_Vertex_t *)hge->h->Gfx_StartBatch(prim_type, tex, blend, max_prim);
}

void HGE_Gfx_FinishBatch(HGE_t *hge, int nprim) {
	hge->h->Gfx_FinishBatch(nprim);
}

void HGE_Gfx_SetClipping(HGE_t *hge, int x, int y, int w, int h) {
	hge->h->Gfx_SetClipping(x, y, w, h);
}

void HGE_Gfx_SetTransform(HGE_t *hge, float x, float y, float dx, float dy, float rot, float hscale, float vscale) {
	hge->h->Gfx_SetTransform(x, y, dx, dy, rot, hscale, vscale);
}

HTARGET HGE_Target_Create(HGE_t *hge, int width, int height, BOOL zbuffer) {
	return hge->h->Target_Create(width, height, zbuffer);
}

void HGE_Target_Free(HGE_t *hge, HTARGET target) {
	hge->h->Target_Free(target);
}

HTEXTURE HGE_Target_GetTexture(HGE_t *hge, HTARGET target) {
	return hge->h->Target_GetTexture(target);
}

HTEXTURE HGE_Texture_Create(HGE_t *hge, int width, int height) {
	return hge->h->Texture_Create(width, height);
}

HTEXTURE HGE_Texture_Load(HGE_t *hge, const char *filename, DWORD size, BOOL bMipmap) {
	return hge->h->Texture_Load(filename, size, bMipmap);
}

void HGE_Texture_Free(HGE_t *hge, HTEXTURE tex) {
	hge->h->Texture_Free(tex);
}

int HGE_Texture_GetWidth(HGE_t *hge, HTEXTURE tex, BOOL bOriginal) {
	return hge->h->Texture_GetWidth(tex, bOriginal);
}

int HGE_Texture_GetHeight(HGE_t *hge, HTEXTURE tex, BOOL bOriginal) {
	return hge->h->Texture_GetHeight(tex, bOriginal);
}

DWORD* HGE_Texture_Lock(HGE_t *hge, HTEXTURE tex, BOOL bReadOnly, int left, int top, int width, int height) {
	return hge->h->Texture_Lock(tex, bReadOnly, left, top, width, height);
}

void HGE_Texture_Unlock(HGE_t *hge, HTEXTURE tex) {
	hge->h->Texture_Unlock(tex);
}

}
