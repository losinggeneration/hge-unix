--
-- Haaf's Game Engine 1.7
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeVector helper class
--

bindhgeVector = {
	classes = {
		{
			name = 'hge.Vector',
			className = 'hgeVector',
			ctors = {
				'()',
				'(float x, float y)',
			},
			properties = {
				'float x',
				'float y',
			},
			memberFunctions = {[[
				hgeVector	operator-  ()					const;
				hgeVector	operator-  (const hgeVector &v) const;
				hgeVector	operator+  (const hgeVector &v) const;
				hgeVector&	operator-= (const hgeVector &v);
				hgeVector&	operator+= (const hgeVector &v);

				hgeVector	operator/  (const float scalar)	const;
				hgeVector	operator*  (const float scalar) const;
				hgeVector&	operator*= (const float scalar);
			]],
				{ rename = 'dot', 'float Dot(const hgeVector *v) const;' },
				{ rename = 'length', 'float Length() const;' },
				{ rename = 'angle', 'float Angle(const hgeVector *v) const;' },

				{ rename = 'clamp', 'void Clamp(const float max);' },
				{ rename = 'normalize', 'hgeVector* Normalize();' },
				{ rename = 'rotate', 'hgeVector* Rotate(float a);' },
			},
		}
	},
	modules = {
	}
}

--[[
-- NOTE: These are all Unbound still
float InvSqrt(float x);

class hgeVector
{
public:
	bool		operator== (const hgeVector &v)	const;
	bool		operator!= (const hgeVector &v)	const;
};

inline hgeVector operator* (const float s, const hgeVector &v);
inline float	 operator^ (const hgeVector &v, const hgeVector &u);
inline float	 operator% (const hgeVector &v, const hgeVector &u);

--]]
