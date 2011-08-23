--
-- Haaf's Game Engine 1.7
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeGUI default controls header
--

bindhgeGuiCtrls = {
	classes = {
		{
			name = 'hge.GUI.Button',
			className = 'hgeGUIButton',
			ctors = {
				'(int id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty)',
			},
			memberFunctions = {
				{ 'void SetMode(bool _bTrigger);' },
				{ 'void SetState(bool _bPressed);' },
				{ 'bool GetState() const;' },

				{ 'void Render();' },
				{ 'bool MouseLButton(bool bDown);' },
			},
		},
		{
			name = 'hge.GUI.Listbox',
			className = 'hgeGUIListbox',
			ctors = {
				'(int id, float x, float y, float w, float h, hgeFont *fnt, DWORD tColor, DWORD thColor, DWORD hColor)',
			},
			memberFunctions = {
				{ 'int AddItem(const char * item);' },
				{ 'void DeleteItem(int n);' },
				{ 'int GetSelectedItem();' },
				{ 'void SetSelectedItem(int n);' },
				{ 'int GetTopItem();' },
				{ 'void SetTopItem(int n);' },

				{ 'const char * GetItemText(int n);' },
				{ 'int GetNumItems();' },
				{ 'int GetNumRows();' },
				{ 'void Clear();' },

				{ 'void Render();' },
				{ 'bool MouseMove(float x, float y);' },
				{ 'bool MouseLButton(bool bDown);' },
				{ 'bool MouseWheel(int nNotches);' },
				{ 'bool KeyClick(int key, int chr);' },
			},
		},
		{
			name = 'hge.GUI.Listbox.Item',
			className = 'hgeGUIListboxItem',
			--  really text[64]
			properties = {
-- 				'std::string text;',
				'hgeGUIListboxItem *next;',
			},
		},
		{
			name = 'hge.GUI.Slider',
			className = 'hgeGUISlider',
			ctors = {
				'(int id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty, float sw, float sh, bool vertical)',
			},
			memberFunctions = {
				{ 'void SetMode(float _fMin, float _fMax, int _mode);' },
				{ 'void SetValue(float _fVal);' },
				{ 'float GetValue() const;' },

				{ 'void Render();' },
				{ 'bool MouseMove(float x, float y);' },
				{ 'bool MouseLButton(bool bDown);' },
			},
		},
		{
			name = 'hge.GUI.Text',
			className = 'hgeGUIText',
			ctors = {
				'(int id, float x, float y, float w, float h, hgeFont *fnt)',
			},
			memberFunctions = {
				{ 'void SetMode(int _align);' },
				{ 'void SetText(const char * _text);' },
-- 				{ 'void printf(const char *format, ...);' },

				{ 'void Render();' },
			},
		},
	},
	modules = {
	},
}

--[[

#define hgeButtonGetState(gui,id) ((hgeGUIButton*)gui->GetCtrl(id))->GetState()
#define hgeButtonSetState(gui,id,b) ((hgeGUIButton*)gui->GetCtrl(id))->SetState(b)
#define hgeSliderGetValue(gui,id) ((hgeGUISlider*)gui->GetCtrl(id))->GetValue()
#define hgeSliderSetValue(gui,id,f) ((hgeGUISlider*)gui->GetCtrl(id))->SetValue(f)
#define hgeGetTextCtrl(gui,id) ((hgeGUIText*)gui->GetCtrl(id))
#define hgeGetListboxCtrl(gui,id) ((hgeGUIListbox*)gui->GetCtrl(id))

#define HGESLIDER_BAR 0
#define HGESLIDER_BARRELATIVE 1
#define HGESLIDER_SLIDER 2

--]]
