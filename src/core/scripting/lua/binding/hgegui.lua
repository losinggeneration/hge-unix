--
-- Haaf's Game Engine 1.7
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeGUI helper classes header
--

bindhgeGui = {
	classes = {
		{
			name = 'hge.GUIObject',
			className = 'hgeGUIObject',
			ctors = {
				'()',
			},
			properties = {
				'int id;',
				'bool bStatic;',
				'bool bVisible;',
				'bool bEnabled;',
				'hgeRect rect;',
				'DWORD color;',

				'hgeGUI *gui;',
				'hgeGUIObject *next;',
				'hgeGUIObject *prev;',
			},
			memberFunctions = {
				{ 'void Update(float dt);' },

				{ 'virtual void Enter();' },
				{ 'virtual void Leave();' },
				{ 'virtual void Reset();' },
				{ 'virtual bool IsDone();' },
				{ 'virtual void Focus(bool bFocused);' },
				{ 'virtual void MouseOver(bool bOver);' },

				{ 'virtual bool MouseMove(float x, float y);' },
				{ 'virtual bool MouseLButton(bool bDown);' },
				{ 'virtual bool MouseRButton(bool bDown);' },
				{ 'virtual bool MouseWheel(int nNotches);' },
				{ 'virtual bool KeyClick(int key, int chr);' },

				{ 'virtual void SetColor(DWORD _color);' },
			},
		},
		{
			name = 'hge.GUI',
			className = 'hgeGUI',
			ctors = {
				'()',
			},
			memberFunctions = {
				{ 'void AddCtrl(hgeGUIObject *ctrl);' },
				{ 'void DelCtrl(int id);' },
				{ 'hgeGUIObject*	GetCtrl(int id) const;' },

				{ 'void MoveCtrl(int id, float x, float y);' },
				{ 'void ShowCtrl(int id, bool bVisible);' },
				{ 'void EnableCtrl(int id, bool bEnabled);' },

				{ 'void SetNavMode(int mode);' },
				{ 'void SetCursor(hgeSprite *spr);' },
				{ 'void SetColor(DWORD color);' },
				{ 'void SetFocus(int id);' },
				{ 'int GetFocus() const;' },

				{ 'void Enter();' },
				{ 'void Leave();' },
				{ 'void Reset();' },
				{ 'void Move(float dx, float dy);' },

				{ 'int Update(float dt);' },
				{ 'void Render();' },
			},
		},
	},
	modules = {
	},
}

--[[

#define HGEGUI_NONAVKEYS		0
#define HGEGUI_LEFTRIGHT		1
#define HGEGUI_UPDOWN			2
#define HGEGUI_CYCLED			4

class hgeGUI;

class hgeGUIObject
{
public:
	hgeGUIObject();
	virtual ~hgeGUIObject();

	virtual void Render() = 0;
	virtual void Update(float dt);

	virtual void Enter();
	virtual void Leave();
	virtual void Reset();
	virtual bool IsDone();
	virtual void Focus(bool bFocused);
	virtual void MouseOver(bool bOver);

	virtual bool MouseMove(float x, float y);
	virtual bool MouseLButton(bool bDown);
	virtual bool MouseRButton(bool bDown);
	virtual bool MouseWheel(int nNotches);
	virtual bool KeyClick(int key, int chr);

	virtual void SetColor(DWORD _color);

	int id;
	bool bStatic;
	bool bVisible;
	bool bEnabled;
	hgeRect rect;
	DWORD color;

	hgeGUI *gui;
	hgeGUIObject *next;
	hgeGUIObject *prev;
};

class hgeGUI
{
public:
	hgeGUI();
	~hgeGUI();

	void			AddCtrl(hgeGUIObject *ctrl);
	void			DelCtrl(int id);
	hgeGUIObject*	GetCtrl(int id) const;

	void			MoveCtrl(int id, float x, float y);
	void			ShowCtrl(int id, bool bVisible);
	void			EnableCtrl(int id, bool bEnabled);

	void			SetNavMode(int mode);
	void			SetCursor(hgeSprite *spr);
	void			SetColor(DWORD color);
	void			SetFocus(int id);
	int				GetFocus() const;

	void			Enter();
	void			Leave();
	void			Reset();
	void			Move(float dx, float dy);

	int				Update(float dt);
	void			Render();
};

--]]
