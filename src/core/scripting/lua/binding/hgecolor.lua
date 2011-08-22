--
-- Haaf's Game Engine 1.7
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeColor*** helper classes
--

array.pushBack(gen_lua.number_types, 'DWORD')

bindhgeColor = {
	classes = {
		{
			name = 'hge.ColorRGB',
			className = 'hgeColorRGB',
			ctors = {
				'()',
				'(DWORD col)',
				'(float _r, float _g, float _b, float _a)',
			},
			properties = {
				'float r',
				'float g',
				'float b',
				'float a',
			},
			memberFunctions = {[[
				hgeColorRGB operator-(const hgeColorRGB &c) const;
				hgeColorRGB operator+(const hgeColorRGB &c) const;
				hgeColorRGB operator*(const hgeColorRGB &c) const;
				hgeColorRGB & operator-=(const hgeColorRGB &c);
				hgeColorRGB & operator+=(const hgeColorRGB &c);
			]],
				-- Not implemented in luna-gen
-- 				bool operator ==(const hgeColorRGB &c) const;
-- 				bool operator!=(const hgeColorRGB &c) const;
			[[
				hgeColorRGB operator/(const float scalar) const;
				hgeColorRGB operator*(const float scalar) const;
				hgeColorRGB & operator*=(const float scalar);
			]],

				{ rename = 'clamp', 'void Clamp();' },
				{ rename = 'sethwcolor', 'void SetHWColor(DWORD col);' },
				{ rename = 'gethwcolor', 'DWORD GetHWColor() const;' },
			},
		},
		{
			name = 'hge.ColorHSV',
			className = 'hgeColorHSV',
			ctors = {
				'()',
				'(DWORD col)',
				'(float _h, float _s, float _v, float _a)',
			},
			properties = {
				'float h',
				'float s',
				'float v',
				'float a',
			},
			memberFunctions = {[[
				hgeColorHSV operator-(const hgeColorHSV &c) const;
				hgeColorHSV operator+(const hgeColorHSV &c) const;
				hgeColorHSV operator*(const hgeColorHSV &c) const;
				hgeColorHSV & operator-=(const hgeColorHSV &c);
				hgeColorHSV & operator+=(const hgeColorHSV &c);
			]],
-- 				bool operator==(const hgeColorHSV &c) const;
-- 				bool operator!=(const hgeColorHSV &c) const;
			[[
				hgeColorHSV operator/(const float scalar) const;
				hgeColorHSV operator*(const float scalar) const;
				hgeColorHSV & operator*=(const float scalar);
			]],

				{ rename = 'clamp', 'void Clamp();' },
				{ rename = 'sethwcolor', 'void SetHWColor(DWORD col);' },
				{ rename = 'gethwcolor', 'DWORD GetHWColor() const;' },
			}
		},
	},
	modules = {
	}
}

--[[

#define hgeColor hgeColorRGB

inline void ColorClamp(float &x) { if(x<0.0f) x=0.0f; if(x>1.0f) x=1.0f; }

inline hgeColorRGB operator* (const float sc, const hgeColorRGB &c) { return c*sc; }
inline hgeColorHSV operator* (const float sc, const hgeColorHSV &c) { return c*sc; }

--]]
