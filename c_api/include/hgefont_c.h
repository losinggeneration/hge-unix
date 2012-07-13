#ifndef HGE__FONT_C_H
#define HGE__FONT_C_H

#include "unix_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HGE_TEXT_LEFT 0
#define HGE_TEXT_RIGHT 1
#define HGE_TEXT_CENTER 2
#define HGE_TEXT_HORZMASK 0x03

#define HGE_TEXT_TOP 0
#define HGE_TEXT_BOTTOM 4
#define HGE_TEXT_MIDDLE 8
#define HGE_TEXT_VERTMASK 0x0C

typedef struct HGE_Sprite_s HGE_Sprite_t;
typedef struct HGE_Font_s HGE_Font_t;

/// bool bMipmap=false
HGE_Font_t *HGE_Font_New(const char *filename, BOOL bMipmap);
void HGE_Font_Free(HGE_Font_t *font);

void HGE_Font_Render(HGE_Font_t *font, float x, float y, int align, const char *string);
void HGE_Font_printf(HGE_Font_t *font, float x, float y, int align, const char *format, ...);
// void HGE_Font_printfb(HGE_Font_t *font, float x, float y, float w, float h, int align, const char *format, ...);

void HGE_Font_SetColor(HGE_Font_t *font, DWORD col);
void HGE_Font_SetZ(HGE_Font_t *font, float z);
void HGE_Font_SetBlendMode(HGE_Font_t *font, int blend);
void HGE_Font_SetScale(HGE_Font_t *font, float scale);
void HGE_Font_SetProportion(HGE_Font_t *font, float prop);
void HGE_Font_SetRotation(HGE_Font_t *font, float rot);
void HGE_Font_SetTracking(HGE_Font_t *font, float tracking);
void HGE_Font_SetSpacing(HGE_Font_t *font, float spacing);

DWORD HGE_Font_GetColor(HGE_Font_t *font);
float HGE_Font_GetZ(HGE_Font_t *font);
int HGE_Font_GetBlendMode(HGE_Font_t *font);
float HGE_Font_GetScale(HGE_Font_t *font);
float HGE_Font_GetProportion(HGE_Font_t *font);
float HGE_Font_GetRotation(HGE_Font_t *font);
float HGE_Font_GetTracking(HGE_Font_t *font);
float HGE_Font_GetSpacing(HGE_Font_t *font);

HGE_Sprite_t* HGE_Font_GetSprite(HGE_Font_t *font, char chr);
float HGE_Font_GetPreWidth(HGE_Font_t *font, char chr);
float HGE_Font_GetPostWidth(HGE_Font_t *font, char chr);
float HGE_Font_GetHeight(HGE_Font_t *font);
float HGE_Font_GetStringWidth(HGE_Font_t *font, const char *string, BOOL bMultiline);

#ifdef __cplusplus
}
#endif

#endif
