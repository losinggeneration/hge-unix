#include "hgefont.h"
#include "hgefont_c.h"
#include "hgesprite_c.h"
#include "hgesprite_impl.h"

#include <malloc.h>

extern "C" {

typedef struct HGE_Font_s {
	hgeFont *f;
} HGE_Font_t;

HGE_Font_t *HGE_Font_New(const char *filename, BOOL bMipmap) {
	HGE_Font_t *f = (HGE_Font_t *)malloc(sizeof(HGE_Font_t));

	f->f = new hgeFont(filename, bMipmap);

	return f;
}

void HGE_Font_Free(HGE_Font_t *font) {
	delete font->f;
	free(font);
}

void HGE_Font_Render(HGE_Font_t *font, float x, float y, int align, const char *string) {
	font->f->Render(x, y, align, string);
}

void HGE_Font_printf(HGE_Font_t *font, float x, float y, int align, const char *format, ...) {
	va_list vl;
	char buffer[1024];

	va_start(vl, format);
	vsnprintf(buffer, 1024, format, vl);
	va_end(vl);

	font->f->printf(x, y, align, buffer);
}

void HGE_Font_printfb(HGE_Font_t *font, float x, float y, float w, float h, int align, const char *format, ...) {
	va_list vl;
	char buffer[1024];

	va_start(vl, format);
	vsnprintf(buffer, 1024, format, vl);
	va_end(vl);

	font->f->printfb(x, y, w, h, align, buffer);
}

void HGE_Font_SetColor(HGE_Font_t *font, DWORD col) {
	font->f->SetColor(col);
}

void HGE_Font_SetZ(HGE_Font_t *font, float z) {
	font->f->SetZ(z);
}

void HGE_Font_SetBlendMode(HGE_Font_t *font, int blend) {
	font->f->SetBlendMode(blend);
}

void HGE_Font_SetScale(HGE_Font_t *font, float scale) {
	font->f->SetScale(scale);
}

void HGE_Font_SetProportion(HGE_Font_t *font, float prop) {
	font->f->SetProportion(prop);
}

void HGE_Font_SetRotation(HGE_Font_t *font, float rot) {
	font->f->SetRotation(rot);
}

void HGE_Font_SetTracking(HGE_Font_t *font, float tracking) {
	font->f->SetTracking(tracking);
}

void HGE_Font_SetSpacing(HGE_Font_t *font, float spacing) {
	font->f->SetSpacing(spacing);
}

DWORD HGE_Font_GetColor(HGE_Font_t *font) {
	return font->f->GetColor();
}

float HGE_Font_GetZ(HGE_Font_t *font) {
	return font->f->GetZ();
}

int HGE_Font_GetBlendMode(HGE_Font_t *font) {
	return font->f->GetBlendMode();
}

float HGE_Font_GetScale(HGE_Font_t *font) {
	return font->f->GetScale();
}

float HGE_Font_GetProportion(HGE_Font_t *font) {
	return font->f->GetProportion();
}

float HGE_Font_GetRotation(HGE_Font_t *font) {
	return font->f->GetRotation();
}

float HGE_Font_GetTracking(HGE_Font_t *font) {
	return font->f->GetTracking();
}

float HGE_Font_GetSpacing(HGE_Font_t *font) {
	return font->f->GetSpacing();
}

HGE_Sprite_t* HGE_Font_GetSprite(HGE_Font_t *font, char chr) {
	HGE_Sprite_t *s = HGE_Sprite_Empty();

	s->s = font->f->GetSprite(chr);

	return s;
}

float HGE_Font_GetPreWidth(HGE_Font_t *font, char chr) {
	return font->f->GetPreWidth(chr);
}

float HGE_Font_GetPostWidth(HGE_Font_t *font, char chr) {
	return font->f->GetPostWidth(chr);
}

float HGE_Font_GetHeight(HGE_Font_t *font) {
	return font->f->GetHeight();
}

float HGE_Font_GetStringWidth(HGE_Font_t *font, const char *string, BOOL bMultiline) {
	return font->f->GetStringWidth(string, bMultiline);
}

}
