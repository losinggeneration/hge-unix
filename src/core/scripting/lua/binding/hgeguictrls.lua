--
-- Haaf's Game Engine 1.7
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeGUI default controls header
--

--[[

#define hgeButtonGetState(gui,id) ((hgeGUIButton*)gui->GetCtrl(id))->GetState()
#define hgeButtonSetState(gui,id,b) ((hgeGUIButton*)gui->GetCtrl(id))->SetState(b)
#define hgeSliderGetValue(gui,id) ((hgeGUISlider*)gui->GetCtrl(id))->GetValue()
#define hgeSliderSetValue(gui,id,f) ((hgeGUISlider*)gui->GetCtrl(id))->SetValue(f)
#define hgeGetTextCtrl(gui,id) ((hgeGUIText*)gui->GetCtrl(id))
#define hgeGetListboxCtrl(gui,id) ((hgeGUIListbox*)gui->GetCtrl(id))

class hgeGUIText : public hgeGUIObject
{
public:
	hgeGUIText(int id, float x, float y, float w, float h, hgeFont *fnt);

	void SetMode(int _align);
	void SetText(const char *_text);
	void printf(const char *format, ...);

	virtual void Render();
};

class hgeGUIButton : public hgeGUIObject
{
public:
	hgeGUIButton(int id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty);
	virtual ~hgeGUIButton();

	void SetMode(bool _bTrigger) { bTrigger=_bTrigger; }
	void SetState(bool _bPressed) { bPressed=_bPressed; }
	bool GetState() const { return bPressed; }

	virtual void Render();
	virtual bool MouseLButton(bool bDown);
};

#define HGESLIDER_BAR 0
#define HGESLIDER_BARRELATIVE 1
#define HGESLIDER_SLIDER 2

class hgeGUISlider : public hgeGUIObject
{
public:
	hgeGUISlider(int id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty, float sw, float sh, bool vertical=false);
	virtual ~hgeGUISlider();

	void SetMode(float _fMin, float _fMax, int _mode) { fMin=_fMin; fMax=_fMax; mode=_mode; }
	void SetValue(float _fVal);
	float GetValue() const { return fVal; }

	virtual void Render();
	virtual bool MouseMove(float x, float y);
	virtual bool MouseLButton(bool bDown);
};

struct hgeGUIListboxItem
{
	char text[64];
	hgeGUIListboxItem *next;
};

class hgeGUIListbox : public hgeGUIObject
{
public:
	hgeGUIListbox(int id, float x, float y, float w, float h, hgeFont *fnt, DWORD tColor, DWORD thColor, DWORD hColor);
	virtual ~hgeGUIListbox();

	int AddItem(char *item);
	void DeleteItem(int n);
	int GetSelectedItem() { return nSelectedItem; }
	void SetSelectedItem(int n) { if(n>=0 && n<GetNumItems()) nSelectedItem=n; }
	int GetTopItem() { return nTopItem; }
	void SetTopItem(int n) { if(n>=0 && n<=GetNumItems()-GetNumRows()) nTopItem=n; }

	char *GetItemText(int n);
	int GetNumItems() { return nItems; }
	int GetNumRows() { return int((rect.y2-rect.y1)/font->GetHeight()); }
	void Clear();

	virtual void Render();
	virtual bool MouseMove(float x, float y) { mx=x; my=y; return false; }
	virtual bool MouseLButton(bool bDown);
	virtual bool MouseWheel(int nNotches);
	virtual bool KeyClick(int key, int chr);
};

--]]
