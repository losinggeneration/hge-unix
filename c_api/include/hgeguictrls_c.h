#ifndef HGE_GUI_C_H
#define HGE_GUI_C_H

#include "unix_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HGE_Button_GetState(gui,id) HGE_GUI_Button_GetState((HGE_GUI_Button_t*)HGE_GUI_GetCtl(gui, id))
#define HGE_Button_SetState(gui,id,b) HGE_GUI_Button_SetState((HGE_GUI_Button_t*)HGE_GUI_GetCtl(gui, id))
#define HGE_Slider_GetValue(gui,id) HGE_GUI_Slider_GetValue((HGE_GUI_Slider_t*)HGE_GUI_GetCtl(gui, id))
#define HGE_Slider_SetValue(gui,id,f) HGE_GUI_Slider_SetValue((HGE_GUI_Slider_t*)HGE_GUI_GetCtl(gui, id), f)
#define HGE_Text_GetCtrl(gui,id) ((HGE_GUI_Text_t*)HGE_GUI_GetCtl(gui, id))
#define HGE_Listbox_GetCtrl(gui,id) ((HGE_GUI_Listbox_t*)HGE_GUI_GetCtl(gui, id))

typedef struct HGE_Font_s HGE_Font_t;

typedef struct HGE_GUI_Text_s HGE_GUI_Text_t;
typedef struct HGE_GUI_Button_s HGE_GUI_Button_t;
typedef struct HGE_GUI_Slider_s HGE_GUI_Slider_t;
// typedef struct HGE_GUI_ListboxItem_s HGE_GUI_ListboxItem_t;
typedef struct HGE_GUI_Listbox_s HGE_GUI_Listbox_t;

/// hgeGUIText
HGE_GUI_Text_t *HGE_GUI_Text_New(int id, float x, float y, float w, float h, HGE_Font_t *fnt);
void HGE_GUI_Text_Free(HGE_GUI_Text_t *t);

void HGE_GUI_Text_SetMode(HGE_GUI_Text_t *t, int align);
void HGE_GUI_Text_SetText(HGE_GUI_Text_t *t, const char *text);
// void printf(const char *format, ...);

void HGE_GUI_Text_Render(HGE_GUI_Text_t *t);

/// hgeGUIButton
HGE_GUI_Button_t *HGE_GUI_Button_New(int id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty);
void HGE_GUI_Button_Free(HGE_GUI_Button_t *b);

void HGE_GUI_Button_SetMode(HGE_GUI_Button_t *b, BOOL trigger);
void HGE_GUI_Button_SetState(HGE_GUI_Button_t *b, BOOL pressed);
BOOL HGE_GUI_Button_GetState(HGE_GUI_Button_t *b);

void HGE_GUI_Button_Render(HGE_GUI_Button_t *b);
BOOL HGE_GUI_Button_MouseLButton(HGE_GUI_Button_t *b, BOOL down);

/// hgeGUISlider
#define HGE_SLIDER_BAR 0
#define HGE_SLIDER_BARRELATIVE 1
#define HGE_SLIDER_SLIDER 2

HGE_GUI_Slider_t *HGE_GUI_Slider_New(int id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty, float sw, float sh, BOOL vertical);
void HGE_GUI_Slider_Free(HGE_GUI_Slider_t *s);

void HGE_GUI_Slider_SetMode(HGE_GUI_Slider_t *s, float min, float max, int mode);
void HGE_GUI_Slider_SetValue(HGE_GUI_Slider_t *s, float val);
float HGE_GUI_Slider_GetValue(HGE_GUI_Slider_t *s);

void HGE_GUI_Slider_Render(HGE_GUI_Slider_t *s);
BOOL HGE_GUI_Slider_MouseMove(HGE_GUI_Slider_t *s, float x, float y);
BOOL HGE_GUI_Slider_MouseLButton(HGE_GUI_Slider_t *s, BOOL down);

/// hgeGUIListbox
HGE_GUI_Listbox_t *HGE_GUI_Listbox_New(int id, float x, float y, float w, float h, HGE_Font_t *fnt, DWORD tColor, DWORD thColor, DWORD hColor);
void HGE_GUI_Listbox_Free(HGE_GUI_Listbox_t *l);

int HGE_GUI_Listbox_AddItem(HGE_GUI_Listbox_t *l, char *item);
void HGE_GUI_Listbox_DeleteItem(HGE_GUI_Listbox_t *l, int n);
int HGE_GUI_Listbox_GetSelectedItem(HGE_GUI_Listbox_t *l);
void HGE_GUI_Listbox_SetSelectedItem(HGE_GUI_Listbox_t *l, int n);
int HGE_GUI_Listbox_GetTopItem(HGE_GUI_Listbox_t *l);
void HGE_GUI_Listbox_SetTopItem(HGE_GUI_Listbox_t *l, int n);

char *HGE_GUI_Listbox_GetItemText(HGE_GUI_Listbox_t *l, int n);
int HGE_GUI_Listbox_GetNumItems(HGE_GUI_Listbox_t *l);
int HGE_GUI_Listbox_GetNumRows(HGE_GUI_Listbox_t *l);
void HGE_GUI_Listbox_Clear(HGE_GUI_Listbox_t *l);

void HGE_GUI_Listbox_Render(HGE_GUI_Listbox_t *l);
BOOL HGE_GUI_Listbox_MouseMove(HGE_GUI_Listbox_t *l, float x, float y);
BOOL HGE_GUI_Listbox_MouseLButton(HGE_GUI_Listbox_t *l, BOOL bDown);
BOOL HGE_GUI_Listbox_MouseWheel(HGE_GUI_Listbox_t *l, int nNotches);
BOOL HGE_GUI_Listbox_KeyClick(HGE_GUI_Listbox_t *l, int key, int chr);

#ifdef __cplusplus
}
#endif

#endif
