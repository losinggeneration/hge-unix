--
-- Haaf's Game Engine 1.7
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeRect helper class
--

bindhgeRect = {
	classes = {
		{
			name = "hge.Rect",
			className = "hgeRect",
			ctors = {
				'()',
				'(float _x1, float _y1, float _x2, float _y2)',
			},
			properties = {
				'float x1',
				'float y1',
				'float x2',
				'float y2',
			},
			memberFunctions = {
				{ rename = 'clear', 'void Clear();' },
				{ rename ='isclean', 'bool IsClean() const;' },
				{ rename ='set', 'void Set(float _x1, float _y1, float _x2, float _y2);' },
				{ rename ='setradius', 'void SetRadius(float x, float y, float r);' },
				{ rename ='encapsulate', 'void Encapsulate(float x, float y);' },
				{ rename ='testpoint', 'bool TestPoint(float x, float y) const;' },
				{ rename ='intersect', 'bool Intersect(const hgeRect *rect) const;' },
			},
		},
	},
	modules = {
	}
}

--[[

class hgeRect
{
public:
	float	x1, y1, x2, y2;

	hgeRect(float _x1, float _y1, float _x2, float _y2);
	hgeRect();

	void    Clear();
	bool    IsClean() const;
	void	Set(float _x1, float _y1, float _x2, float _y2);
	void	SetRadius(float x, float y, float r);
	void	Encapsulate(float x, float y);
	bool	TestPoint(float x, float y) const;
	bool	Intersect(const hgeRect *rect) const;
};

--]]
