#ifndef HGE_GUI_C_H
#define HGE_GUI_C_H

#include "unix_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HGE_GUI_NONAVKEYS 0
#define HGE_GUI_LEFTRIGHT 1
#define HGE_GUI_UPDOWN 2
#define HGE_GUI_CYCLED 4

typedef struct HGE_GUI_Object_s HGE_GUI_Object_t;
typedef struct HGE_GUI_s HGE_GUI_t;

// Used for inheritance
typedef struct HGE_GUI_Object_Impl_s {
	void (*Render)(void *user_struct);
	void (*Update)(void *user_struct, float dt);

	void (*Enter)(void *user_struct);
	void (*Leave)(void *user_struct);
	void (*Reset)(void *user_struct);
	BOOL (*IsDone)(void *user_struct);
	void (*Focus)(void *user_struct, BOOL bFocused);
	void (*MouseOver)(void *user_struct, BOOL bOver);

	BOOL (*MouseMove)(void *user_struct, float x, float y);
	BOOL (*MouseLButton)(void *user_struct, BOOL bDown);
	BOOL (*MouseRButton)(void *user_struct, BOOL bDown);
	BOOL (*MouseWheel)(void *user_struct, int nNotches);
	BOOL (*KeyClick)(void *user_struct, int key, int chr);

	void (*SetColor)(void *user_struct, DWORD _color);
} HGE_GUI_Object_Impl_t;

// forward declarations from other headers
typedef struct HGE_Rect_s HGE_Rect_t;
typedef struct HGE_Sprite_s HGE_Sprite_t;
typedef struct HGE_s HGE_t;

/// hgeGUIObject
HGE_GUI_Object_t *HGE_GUI_Object_New(HGE_GUI_Object_Impl_t* impl, void* user_struct);
void HGE_GUI_Object_Free(HGE_GUI_Object_t *go);

void HGE_GUI_Object_HGE_GUI_Object_Render(HGE_GUI_Object_t *go);
void HGE_GUI_Object_Update(HGE_GUI_Object_t *go, float dt);

void HGE_GUI_Object_Enter(HGE_GUI_Object_t *go);
void HGE_GUI_Object_Leave(HGE_GUI_Object_t *go);
void HGE_GUI_Object_Reset(HGE_GUI_Object_t *go);
BOOL HGE_GUI_Object_IsDone(HGE_GUI_Object_t *go);
void HGE_GUI_Object_Focus(HGE_GUI_Object_t *go, BOOL focused);
void HGE_GUI_Object_MouseOver(HGE_GUI_Object_t *go, BOOL over);

BOOL HGE_GUI_Object_MouseMove(HGE_GUI_Object_t *go, float x, float y);
BOOL HGE_GUI_Object_MouseLButton(HGE_GUI_Object_t *go, BOOL down);
BOOL HGE_GUI_Object_MouseRButton(HGE_GUI_Object_t *go, BOOL down);
BOOL HGE_GUI_Object_MouseWheel(HGE_GUI_Object_t *go, int notches);
BOOL HGE_GUI_Object_KeyClick(HGE_GUI_Object_t *go, int key, int chr);

void HGE_GUI_Object_SetColor(HGE_GUI_Object_t *go, DWORD color);

void HGE_GUI_Object_SetId(HGE_GUI_Object_t *go, int id);
int HGE_GUI_Object_GetId(HGE_GUI_Object_t *go);
void HGE_GUI_Object_SetStatic(HGE_GUI_Object_t *go, BOOL is_static);
BOOL HGE_GUI_Object_GetStatic(HGE_GUI_Object_t *go);
void HGE_GUI_Object_SetVisible(HGE_GUI_Object_t *go, BOOL visible);
BOOL HGE_GUI_Object_GetVisible(HGE_GUI_Object_t *go);
void HGE_GUI_Object_SetEnabled(HGE_GUI_Object_t *go, BOOL enabled);
BOOL HGE_GUI_Object_GetEnabled(HGE_GUI_Object_t *go);
void HGE_GUI_Object_SetRect(HGE_GUI_Object_t *go, const HGE_Rect_t *rect);
HGE_Rect_t *HGE_GUI_Object_GetRect(HGE_GUI_Object_t *go);
DWORD HGE_GUI_Object_GetColor(HGE_GUI_Object_t *go);

void HGE_GUI_Object_SetGui(HGE_GUI_Object_t *go, HGE_GUI_t *gui);
HGE_GUI_t *HGE_GUI_Object_GetGui(HGE_GUI_Object_t *go);
void HGE_GUI_Object_SetNext(HGE_GUI_Object_t *go, HGE_GUI_Object_t *next);
HGE_GUI_Object_t *HGE_GUI_Object_GetNext(HGE_GUI_Object_t *go);
void HGE_GUI_Object_SetPrev(HGE_GUI_Object_t *go, HGE_GUI_Object_t *prev);
HGE_GUI_Object_t *HGE_GUI_Object_GetPrev(HGE_GUI_Object_t *go);

/// hgeGUI
HGE_GUI_t *HGE_GUI_New();
void HGE_GUI_Free(HGE_GUI_t *g);

void HGE_GUI_AddCtrl(HGE_GUI_t *g, HGE_GUI_Object_t *ctrl);
void HGE_GUI_DelCtrl(HGE_GUI_t *g, int id);
/// You must call free() on the returned object when you're done
/// DO NOT call HGE_GUI_Object_Free on it.
HGE_GUI_Object_t *HGE_GUI_GetCtrl(HGE_GUI_t *g, int id);

void HGE_GUI_MoveCtrl(HGE_GUI_t *g, int id, float x, float y);
void HGE_GUI_ShowCtrl(HGE_GUI_t *g, int id, BOOL visible);
void HGE_GUI_EnableCtrl(HGE_GUI_t *g, int id, BOOL enabled);

void HGE_GUI_SetNavMode(HGE_GUI_t *g, int mode);
void HGE_GUI_SetCursor(HGE_GUI_t *g, HGE_Sprite_t *spr);
void HGE_GUI_SetColor(HGE_GUI_t *g, DWORD color);
void HGE_GUI_SetFocus(HGE_GUI_t *g, int id);
int HGE_GUI_GetFocus(HGE_GUI_t *g);

void HGE_GUI_Enter(HGE_GUI_t *g);
void HGE_GUI_Leave(HGE_GUI_t *g);
void HGE_GUI_Reset(HGE_GUI_t *g);
void HGE_GUI_Move(HGE_GUI_t *g, float dx, float dy);

int HGE_GUI_Update(HGE_GUI_t *g, float dt);
void HGE_GUI_Render(HGE_GUI_t *g);

#ifdef __cplusplus
}
#endif

#endif
