#include "hgegui.h"
#include "hgegui_c.h"
#include "hge_impl.h"
#include "hgerect_impl.h"
#include "hgesprite_impl.h"

#include <malloc.h>

extern "C" {

typedef struct HGE_GUI_Object_s {
	hgeGUIObject *go;
	HGE_Rect_t *r;
	HGE_GUI_t *g;
	HGE_GUI_Object_t *n;
	HGE_GUI_Object_t *p;
} HGE_GUI_Object_t;

typedef struct HGE_GUI_s {
	hgeGUI *g;
} HGE_GUI_t;

class _hgeGUIObject_impl : public hgeGUIObject {
public:
 _hgeGUIObject_impl(HGE_GUI_Object_Impl_t *obj, void *user_struct) : user_struct(user_struct) {
		go.Render = obj->Render;
		go.Update = obj->Update;

		go.Enter = obj->Enter;
		go.Leave = obj->Leave;
		go.Reset = obj->Reset;
		go.IsDone = obj->IsDone;
		go.Focus = obj->Focus;
		go.MouseOver = obj->MouseOver;

		go.MouseMove = obj->MouseMove;
		go.MouseLButton = obj->MouseLButton;
		go.MouseRButton = obj->MouseRButton;
		go.MouseWheel = obj->MouseWheel;
		go.KeyClick = obj->KeyClick;

		go.SetColor = obj->SetColor;
	}

	virtual void Render() {
		go.Render(user_struct);
	}

	virtual void Update(float dt) {
		go.Update(user_struct, dt);
	}

	virtual void Enter() {
		go.Enter(user_struct);
	}

	virtual void Leave() {
		go.Leave(user_struct);
	}

	virtual void Reset() {
		go.Reset(user_struct);
	}

	virtual bool IsDone() {
		return go.IsDone(user_struct);
	}

	virtual void Focus(bool bFocused) {
		go.Focus(user_struct, bFocused);
	}

	virtual void MouseOver(bool bOver) {
		go.MouseOver(user_struct, bOver);
	}

	virtual bool MouseMove(float x, float y) {
		return go.MouseMove(user_struct, x, y);
	}

	virtual bool MouseLButton(bool bDown) {
		return go.MouseLButton(user_struct, bDown);
	}

	virtual bool MouseRButton(bool bDown) {
		return go.MouseRButton(user_struct, bDown);
	}

	virtual bool MouseWheel(int nNotches) {
		return go.MouseWheel(user_struct, nNotches);
	}

	virtual bool KeyClick(int key, int chr) {
		return go.KeyClick(user_struct, key, chr);
	}

	virtual void SetColor(DWORD _color) {
		go.SetColor(user_struct, _color);
	}

private:
	HGE_GUI_Object_Impl_t go;
	void *user_struct;
};

static HGE_GUI_t *mallocHGE_GUI_t() {
	return new HGE_GUI_t;
}

static HGE_GUI_Object_t *mallocHGE_GUI_Object_t() {
	return new HGE_GUI_Object_t;
}

HGE_GUI_Object_t *HGE_GUI_Object_New(HGE_GUI_Object_Impl_t *impl, void *user_struct) {
	HGE_GUI_Object_t *go = mallocHGE_GUI_Object_t();

	go->r = new HGE_Rect_t();
	go->g = mallocHGE_GUI_t();
	go->n = mallocHGE_GUI_Object_t();
	go->p = mallocHGE_GUI_Object_t();

	go->go = new _hgeGUIObject_impl(impl, user_struct);

	return go;
}

void HGE_GUI_Object_Free(HGE_GUI_Object_t *go) {
	delete go->go;
	delete go->r;
	delete go->g;
	delete go->n;
	delete go->p;
	delete go;
}

void HGE_GUI_Object_HGE_GUI_Object_Render(HGE_GUI_Object_t *go) {
	go->go->Render();
}

void HGE_GUI_Object_Update(HGE_GUI_Object_t *go, float dt) {
	go->go->Update(dt);
}

void HGE_GUI_Object_Enter(HGE_GUI_Object_t *go) {
	go->go->Enter();
}

void HGE_GUI_Object_Leave(HGE_GUI_Object_t *go) {
	go->go->Leave();
}

void HGE_GUI_Object_Reset(HGE_GUI_Object_t *go) {
	go->go->Reset();
}

BOOL HGE_GUI_Object_IsDone(HGE_GUI_Object_t *go) {
	return go->go->IsDone();
}

void HGE_GUI_Object_Focus(HGE_GUI_Object_t *go, BOOL focused) {
	go->go->Focus(focused);
}

void HGE_GUI_Object_MouseOver(HGE_GUI_Object_t *go, BOOL over) {
	go->go->MouseOver(over);
}

BOOL HGE_GUI_Object_MouseMove(HGE_GUI_Object_t *go, float x, float y) {
	return go->go->MouseMove(x, y);
}

BOOL HGE_GUI_Object_MouseLButton(HGE_GUI_Object_t *go, BOOL down) {
	return go->go->MouseLButton(down);
}

BOOL HGE_GUI_Object_MouseRButton(HGE_GUI_Object_t *go, BOOL down) {
	return go->go->MouseRButton(down);
}

BOOL HGE_GUI_Object_MouseWheel(HGE_GUI_Object_t *go, int notches) {
	return go->go->MouseWheel(notches);
}

BOOL HGE_GUI_Object_KeyClick(HGE_GUI_Object_t *go, int key, int chr) {
	return go->go->KeyClick(key, chr);
}

void HGE_GUI_Object_SetColor(HGE_GUI_Object_t *go, DWORD color) {
	go->go->SetColor(color);
}

void HGE_GUI_Object_SetId(HGE_GUI_Object_t *go, int id) {
	go->go->id = id;
}

int HGE_GUI_Object_GetId(HGE_GUI_Object_t *go) {
	return go->go->id;
}

void HGE_GUI_Object_SetStatic(HGE_GUI_Object_t *go, BOOL is_static) {
	go->go->bStatic = is_static;
}

BOOL HGE_GUI_Object_GetStatic(HGE_GUI_Object_t *go) {
	return go->go->bStatic;
}

void HGE_GUI_Object_SetVisible(HGE_GUI_Object_t *go, BOOL visible) {
	go->go->bVisible = visible;
}

BOOL HGE_GUI_Object_GetVisible(HGE_GUI_Object_t *go) {
	return go->go->bVisible;
}

void HGE_GUI_Object_SetEnabled(HGE_GUI_Object_t *go, BOOL enabled) {
	go->go->bEnabled = enabled;
}

BOOL HGE_GUI_Object_GetEnabled(HGE_GUI_Object_t *go) {
	return go->go->bEnabled;
}

void HGE_GUI_Object_SetRect(HGE_GUI_Object_t *go, const HGE_Rect_t *rect) {
	go->go->rect = *rect->r;
}

HGE_Rect_t *HGE_GUI_Object_GetRect(HGE_GUI_Object_t *go) {
	delete go->r;
	go->r = new HGE_Rect_s(&go->go->rect);
	return go->r;
}

DWORD HGE_GUI_Object_GetColor(HGE_GUI_Object_t *go) {
	return go->go->color;
}

void HGE_GUI_Object_SetGui(HGE_GUI_Object_t *go, HGE_GUI_t *gui) {
	go->go->gui = gui->g;
}

HGE_GUI_t *HGE_GUI_Object_GetGui(HGE_GUI_Object_t *go) {
	delete go->g;
	go->g = mallocHGE_GUI_t();
	go->g->g = go->go->gui;
	return go->g;
}

void HGE_GUI_Object_SetNext(HGE_GUI_Object_t *go, HGE_GUI_Object_t *next) {
	go->go->next = next->go;
}

HGE_GUI_Object_t *HGE_GUI_Object_GetNext(HGE_GUI_Object_t *go) {
	delete go->n;
	go->n = mallocHGE_GUI_Object_t();
	go->n->go = go->go->next;
	return go->n;
}

void HGE_GUI_Object_SetPrev(HGE_GUI_Object_t *go, HGE_GUI_Object_t *prev) {
	go->go->prev = prev->go;
}

HGE_GUI_Object_t *HGE_GUI_Object_GetPrev(HGE_GUI_Object_t *go) {
	delete go->p;
	go->p = mallocHGE_GUI_Object_t();
	go->p->go = go->go->prev;
	return go->p;
}

HGE_GUI_t *HGE_GUI_New() {
	HGE_GUI_t *g = mallocHGE_GUI_t();

	g->g = new hgeGUI();

	return g;
}

void HGE_GUI_Free(HGE_GUI_t *g) {
	delete g->g;
	delete g;
}

void HGE_GUI_AddCtrl(HGE_GUI_t *g, HGE_GUI_Object_t *ctrl) {
	g->g->AddCtrl(ctrl->go);
}

void HGE_GUI_DelCtrl(HGE_GUI_t *g, int id) {
	g->g->DelCtrl(id);
}

HGE_GUI_Object_t* HGE_GUI_GetCtrl(HGE_GUI_t *g, int id) {
	HGE_GUI_Object_t *go = mallocHGE_GUI_Object_t();
	go->go = g->g->GetCtrl(id);
	return go;
}

void HGE_GUI_MoveCtrl(HGE_GUI_t *g, int id, float x, float y) {
	g->g->MoveCtrl(id, x, y);
}

void HGE_GUI_ShowCtrl(HGE_GUI_t *g, int id, BOOL visible) {
	g->g->ShowCtrl(id, visible);
}

void HGE_GUI_EnableCtrl(HGE_GUI_t *g, int id, BOOL enabled) {
	g->g->EnableCtrl(id, enabled);
}

void HGE_GUI_SetNavMode(HGE_GUI_t *g, int mode) {
	g->g->SetNavMode(mode);
}

void HGE_GUI_SetCursor(HGE_GUI_t *g, HGE_Sprite_t *spr) {
	g->g->SetCursor(spr->s);
}

void HGE_GUI_SetColor(HGE_GUI_t *g, DWORD color) {
	g->g->SetColor(color);
}

void HGE_GUI_SetFocus(HGE_GUI_t *g, int id) {
	g->g->SetFocus(id);
}

int HGE_GUI_GetFocus(HGE_GUI_t *g) {
	return g->g->GetFocus();
}

void HGE_GUI_Enter(HGE_GUI_t *g) {
	g->g->Enter();
}

void HGE_GUI_Leave(HGE_GUI_t *g) {
	g->g->Leave();
}

void HGE_GUI_Reset(HGE_GUI_t *g) {
	g->g->Reset();
}

void HGE_GUI_Move(HGE_GUI_t *g, float dx, float dy) {
	g->g->Move(dx, dy);
}

int HGE_GUI_Update(HGE_GUI_t *g, float dt) {
	return g->g->Update(dt);
}

void HGE_GUI_Render(HGE_GUI_t *g) {
	g->g->Render();
}

}
