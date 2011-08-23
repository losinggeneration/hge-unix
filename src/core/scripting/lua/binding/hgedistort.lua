--
-- Haaf's Game Engine 1.7
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeDistortionMesh helper class header
--

bindhgeDistort = {
	classes = {
		{
			name = 'hge.DistortionMesh',
			className = 'hgeDistortionMesh',
			ctors = {
				'(int cols, int rows)',
				'(const hgeDistortionMesh &dm)',
			},
			memberFunctions =  {[[
				hgeDistortionMesh& operator=(const hgeDistortionMesh &dm);

				void Render(float x, float y);
				void Clear(DWORD col, float z);

				void SetTexture(HTEXTURE tex);
				void SetTextureRect(float x, float y, float w, float h);
				void SetBlendMode(int blend);
				void SetZ(int col, int row, float z);
				void SetColor(int col, int row, DWORD color);
				void SetDisplacement(int col, int row, float dx, float dy, int ref);

				HTEXTURE GetTexture() const;
				int GetBlendMode() const;
				float GetZ(int col, int row) const;
				DWORD GetColor(int col, int row) const;

				int GetRows();
				int GetCols();
			]],
			-- luna-gen seems to fail on these
-- 				'void GetTextureRect(float *x, float *y, float *w, float *h) const;',
-- 				'void GetDisplacement(int col, int row, float* dx, float* dy, int ref) const;',

			},
		},
	},
	modules = {
	},
}

--[[

#define HGEDISP_NODE		0
#define HGEDISP_TOPLEFT		1
#define HGEDISP_CENTER		2

class hgeDistortionMesh
{
public:
	void GetTextureRect(float *x, float *y, float *w, float *h) const;
	void GetDisplacement(int col, int row, float *dx, float *dy, int ref) const;
};

--]]
