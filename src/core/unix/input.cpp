/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: input
*/


#include "hge_impl.h"

const char *KeyNames[] =
{
 "?",
 "Left Mouse Button", "Right Mouse Button", "?", "Middle Mouse Button",
 "?", "?", "?", "Backspace", "Tab", "?", "?", "?", "Enter", "?", "?",
 "Shift", "Ctrl", "Alt", "Pause", "Caps Lock", "?", "?", "?", "?", "?", "?",
 "Escape", "?", "?", "?", "?",
 "Space", "Page Up", "Page Down", "End", "Home",
 "Left Arrow", "Up Arrow", "Right Arrow", "Down Arrow",
 "?", "?", "?", "?", "Insert", "Delete", "?",
 "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
 "?", "?", "?", "?", "?", "?", "?",
 "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
 "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
 "Left Win", "Right Win", "Application", "?", "?",
 "NumPad 0", "NumPad 1", "NumPad 2", "NumPad 3", "NumPad 4",
 "NumPad 5", "NumPad 6", "NumPad 7", "NumPad 8", "NumPad 9",
 "Multiply", "Add", "?", "Subtract", "Decimal", "Divide",
 "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "Num Lock", "Scroll Lock",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "Semicolon", "Equals", "Comma", "Minus", "Period", "Slash", "Grave",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?",
 "Left bracket", "Backslash", "Right bracket", "Apostrophe",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?"
};


static int SDLKeyToHGEKey(const int sdlkey)
{
	switch (sdlkey)
	{
		case SDLK_ESCAPE: return HGEK_ESCAPE;
		case SDLK_BACKSPACE: return HGEK_BACKSPACE;
		case SDLK_TAB: return HGEK_TAB;
		case SDLK_RETURN: return HGEK_ENTER;
		case SDLK_SPACE: return HGEK_SPACE;
		case SDLK_LSHIFT: return HGEK_SHIFT;
		case SDLK_RSHIFT: return HGEK_SHIFT;
		case SDLK_LCTRL: return HGEK_CTRL;
		case SDLK_RCTRL: return HGEK_CTRL;
		case SDLK_LALT: return HGEK_ALT;
		case SDLK_RALT: return HGEK_ALT;
		case SDLK_LMETA: return HGEK_LWIN;
		case SDLK_RMETA: return HGEK_RWIN;
		//case SDLK_APPS: return HGEK_APPS;
		case SDLK_PAUSE: return HGEK_PAUSE;
		case SDLK_CAPSLOCK: return HGEK_CAPSLOCK;
		case SDLK_NUMLOCK: return HGEK_NUMLOCK;
		case SDLK_SCROLLOCK: return HGEK_SCROLLLOCK;
		case SDLK_PAGEUP: return HGEK_PGUP;
		case SDLK_PAGEDOWN: return HGEK_PGDN;
		case SDLK_HOME: return HGEK_HOME;
		case SDLK_END: return HGEK_END;
		case SDLK_INSERT: return HGEK_INSERT;
		case SDLK_DELETE: return HGEK_DELETE;
		case SDLK_LEFT: return HGEK_LEFT;
		case SDLK_UP: return HGEK_UP;
		case SDLK_RIGHT: return HGEK_RIGHT;
		case SDLK_DOWN: return HGEK_DOWN;
		case SDLK_0: return HGEK_0;
		case SDLK_1: return HGEK_1;
		case SDLK_2: return HGEK_2;
		case SDLK_3: return HGEK_3;
		case SDLK_4: return HGEK_4;
		case SDLK_5: return HGEK_5;
		case SDLK_6: return HGEK_6;
		case SDLK_7: return HGEK_7;
		case SDLK_8: return HGEK_8;
		case SDLK_9: return HGEK_9;
		case SDLK_a: return HGEK_A;
		case SDLK_b: return HGEK_B;
		case SDLK_c: return HGEK_C;
		case SDLK_d: return HGEK_D;
		case SDLK_e: return HGEK_E;
		case SDLK_f: return HGEK_F;
		case SDLK_g: return HGEK_G;
		case SDLK_h: return HGEK_H;
		case SDLK_i: return HGEK_I;
		case SDLK_j: return HGEK_J;
		case SDLK_k: return HGEK_K;
		case SDLK_l: return HGEK_L;
		case SDLK_m: return HGEK_M;
		case SDLK_n: return HGEK_N;
		case SDLK_o: return HGEK_O;
		case SDLK_p: return HGEK_P;
		case SDLK_q: return HGEK_Q;
		case SDLK_r: return HGEK_R;
		case SDLK_s: return HGEK_S;
		case SDLK_t: return HGEK_T;
		case SDLK_u: return HGEK_U;
		case SDLK_v: return HGEK_V;
		case SDLK_w: return HGEK_W;
		case SDLK_x: return HGEK_X;
		case SDLK_y: return HGEK_Y;
		case SDLK_z: return HGEK_Z;
		//case SDLK_GRAVE: return HGEK_GRAVE;
		case SDLK_MINUS: return HGEK_MINUS;
		case SDLK_EQUALS: return HGEK_EQUALS;
		case SDLK_BACKSLASH: return HGEK_BACKSLASH;
		case SDLK_LEFTBRACKET: return HGEK_LBRACKET;
		case SDLK_RIGHTBRACKET: return HGEK_RBRACKET;
		case SDLK_SEMICOLON: return HGEK_SEMICOLON;
		case SDLK_QUOTE: return HGEK_APOSTROPHE;
		case SDLK_COMMA: return HGEK_COMMA;
		case SDLK_PERIOD: return HGEK_PERIOD;
		case SDLK_SLASH: return HGEK_SLASH;
		case SDLK_KP0: return HGEK_NUMPAD0;
		case SDLK_KP1: return HGEK_NUMPAD1;
		case SDLK_KP2: return HGEK_NUMPAD2;
		case SDLK_KP3: return HGEK_NUMPAD3;
		case SDLK_KP4: return HGEK_NUMPAD4;
		case SDLK_KP5: return HGEK_NUMPAD5;
		case SDLK_KP6: return HGEK_NUMPAD6;
		case SDLK_KP7: return HGEK_NUMPAD7;
		case SDLK_KP8: return HGEK_NUMPAD8;
		case SDLK_KP9: return HGEK_NUMPAD9;
		case SDLK_KP_MULTIPLY: return HGEK_MULTIPLY;
		case SDLK_KP_DIVIDE: return HGEK_DIVIDE;
		case SDLK_KP_PLUS: return HGEK_ADD;
		case SDLK_KP_MINUS: return HGEK_SUBTRACT;
		case SDLK_KP_PERIOD: return HGEK_DECIMAL;
		case SDLK_F1: return HGEK_F1;
		case SDLK_F2: return HGEK_F2;
		case SDLK_F3: return HGEK_F3;
		case SDLK_F4: return HGEK_F4;
		case SDLK_F5: return HGEK_F5;
		case SDLK_F6: return HGEK_F6;
		case SDLK_F7: return HGEK_F7;
		case SDLK_F8: return HGEK_F8;
		case SDLK_F9: return HGEK_F9;
		case SDLK_F10: return HGEK_F10;
		case SDLK_F11: return HGEK_F11;
		case SDLK_F12: return HGEK_F12;
		default: return -1;
	}

	return -1;
}


bool CALL HGE_Impl::Input_GetEvent(hgeInputEvent *event)
{
	CInputEventList *eptr;

	if(queue)
	{
		eptr=queue;
		memcpy(event, &eptr->event, sizeof(hgeInputEvent));
		queue=eptr->next;
		delete eptr;
		return true;
	}

	return false;
}

void CALL HGE_Impl::Input_GetMousePos(float *x, float *y)
{
	*x=Xpos; *y=Ypos;
}


void CALL HGE_Impl::Input_SetMousePos(float x, float y)
{
	SDL_WarpMouse(x, y);
}

int CALL HGE_Impl::Input_GetMouseWheel()
{
	return Zpos;
}

bool CALL HGE_Impl::Input_IsMouseOver()
{
	return bMouseOver;
}

bool CALL HGE_Impl::Input_GetKeyState(int key)
{
	return (keyz[key] & 4) != 0;
}

bool CALL HGE_Impl::Input_KeyDown(int key)
{
	return (keyz[key] & 1) != 0;
}

bool CALL HGE_Impl::Input_KeyUp(int key)
{
	return (keyz[key] & 2) != 0;
}

const char* CALL HGE_Impl::Input_GetKeyName(int key)
{
	return KeyNames[key];
}

int CALL HGE_Impl::Input_GetKey()
{
	return VKey;
}

int CALL HGE_Impl::Input_GetChar()
{
	return Char;
}


//////// Implementation ////////


void HGE_Impl::_InputInit()
{
	Xpos = 0;  // eh.
	Ypos = 0;
	memset(&keyz, 0, sizeof(keyz));
}

void HGE_Impl::_UpdateMouse()
{
	// no-op.
}


void HGE_Impl::_BuildEvent(int type, int key, int scan, int flags, int x, int y)
{
	CInputEventList *last, *eptr=new CInputEventList;

	eptr->event.type=type;
	eptr->event.chr=0;
	int ptx=x;
	int pty=y;

	if(type==INPUT_KEYDOWN)
	{
		key = SDLKeyToHGEKey(key);
		if ( (key < 0) || (key > (sizeof (keyz) / sizeof (keyz[0]))) ) return;
		keyz[key] |= 4;
		if((flags & HGEINP_REPEAT) == 0) keyz[key] |= 1;
		eptr->event.chr = (char) ((key >= 32) && (key <= 127)) ? key : 0;  // these map to ASCII in sdl.
	}
	if(type==INPUT_KEYUP)
	{
		key = SDLKeyToHGEKey(key);
		if ( (key < 0) || (key > (sizeof (keyz) / sizeof (keyz[0]))) ) return;
		keyz[key] &= ~4;
		keyz[key] |= 2;
		eptr->event.chr = (char) ((key >= 32) && (key <= 127)) ? key : 0;  // these map to ASCII in sdl.
	}
	if(type==INPUT_MOUSEWHEEL)
	{
		eptr->event.key=0; eptr->event.wheel=key;
	}
	else { eptr->event.key=key; eptr->event.wheel=0; }

	if(type==INPUT_MBUTTONDOWN)
	{
		keyz[key] |= 1;
		keyz[key] |= 4;
		//SetCapture(hwnd);
		bCaptured=true;
	}
	if(type==INPUT_MBUTTONUP)
	{
		keyz[key] |= 2;
		keyz[key] &= ~4;
		//ReleaseCapture();
		//Input_SetMousePos(Xpos, Ypos);
		ptx=(int)Xpos; pty=(int)Ypos;
		bCaptured=false;
	}

	if(keymods & KMOD_SHIFT) flags|=HGEINP_SHIFT;
	if(keymods & KMOD_CTRL)  flags|=HGEINP_CTRL;
	if(keymods & KMOD_ALT)  flags|=HGEINP_ALT;
	if(keymods & KMOD_CAPS)  flags|=HGEINP_CAPSLOCK;
	if(keymods & KMOD_MODE) flags|=HGEINP_SCROLLLOCK;
	if(keymods & KMOD_NUM) flags|=HGEINP_NUMLOCK;
	eptr->event.flags=flags;

	if(ptx==-1) { eptr->event.x=Xpos;eptr->event.y=Ypos; }
	else
	{
		if(ptx<0) ptx=0;
		if(pty<0) pty=0;
		if(ptx>=nScreenWidth) ptx=nScreenWidth-1;
		if(pty>=nScreenHeight) pty=nScreenHeight-1;

		eptr->event.x=(float)ptx;
		eptr->event.y=(float)pty;
	}

	eptr->next=0;

	if(!queue) queue=eptr;
	else
	{
		last=queue;
		while(last->next) last=last->next;
		last->next=eptr;
	}

	if(eptr->event.type==INPUT_KEYDOWN || eptr->event.type==INPUT_MBUTTONDOWN)
	{
		VKey=eptr->event.key;Char=eptr->event.chr;
	}
	else if(eptr->event.type==INPUT_MOUSEMOVE)
	{
		Xpos=eptr->event.x;Ypos=eptr->event.y;
	}
	else if(eptr->event.type==INPUT_MOUSEWHEEL)
	{
		Zpos+=eptr->event.wheel;
	}
}

void HGE_Impl::_ClearQueue()
{
	CInputEventList *nexteptr, *eptr=queue;

	//memset(&keyz, 0, sizeof(keyz));
	for (int i = 0; i < sizeof (keyz) / sizeof (keyz[0]); i++)
		keyz[i] &= ~3;  // only reset some of the bits.

	while(eptr)
	{
		nexteptr=eptr->next;
		delete eptr;
		eptr=nexteptr;
	}

	queue=0; VKey=0; Char=0; Zpos=0;
}
