--
-- Haaf's Game Engine 1.7
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeFont helper class header
--

bindhgeFont = {
	classes = {
		{
			name = 'hge.Font',
			className = 'hgeFont',
			ctors  = {
				'(const char *filename, bool bMipmap)',
			},
			memberFunctions = {[[
				void Render(float x, float y, int align, const char *string);
			]],
-- 				'void printf(float x, float y, int align, const char *format, ...);',
-- 				'void printfb(float x, float y, float w, float h, int align, const char *format, ...);',
			[[
				void SetColor(DWORD col);
				void SetZ(float z);
				void SetBlendMode(int blend);
				void SetScale(float scale);
				void SetProportion(float prop);
				void SetRotation(float rot);
				void SetTracking(float tracking);
				void SetSpacing(float spacing);

				DWORD GetColor() const;
				float GetZ() const;
				int GetBlendMode() const;
				float GetScale() const;
				float GetProportion() const;
				float GetRotation() const;
				float GetTracking() const;
				float GetSpacing() const;
			]],

-- 				'hgeSprite* GetSprite(char c) const;'
-- 				'float GetPreWidth(char c) const;'
-- 				'float GetPostWidth(char c) const;'
			[[
				float GetHeight() const;
				float GetStringWidth(const char *string, bool bMultiline) const;
			]]},
		},
	},
	modules = {
	},
}

--[[

#define HGETEXT_LEFT		0
#define HGETEXT_RIGHT		1
#define HGETEXT_CENTER		2
#define HGETEXT_HORZMASK	0x03

#define HGETEXT_TOP			0
#define HGETEXT_BOTTOM		4
#define HGETEXT_MIDDLE		8
#define HGETEXT_VERTMASK	0x0C

class hgeFont
{
public:
	void		printf(float x, float y, int align, const char *format, ...);
	void		printfb(float x, float y, float w, float h, int align, const char *format, ...);

	hgeSprite*	GetSprite(char chr) const;
	float		GetPreWidth(char chr) const;
	float		GetPostWidth(char chr) const;
};

--]]
