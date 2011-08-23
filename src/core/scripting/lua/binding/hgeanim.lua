--
-- Haaf's Game Engine 1.7
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeAnimation helper class header
--

array.pushBack(gen_lua.number_types, 'HTEXTURE')

bindhgeAnim = {
	classes = {
		{
			name = 'hge.Animation',
			className = 'hgeAnimation',
			ctors = {
				'(HTEXTURE tex, int nframes, float FPS, float x, float y, float w, float h)',
				'(const hgeAnimation &anim)',
			},
			memberFunctions = {[[
				void Play();
				void Stop();
				void Resume();
				void Update(float fDeltaTime);
				bool IsPlaying() const;

				void SetTexture(HTEXTURE tex);
				void SetTextureRect(float x1, float y1, float x2, float y2);
				void SetMode(int mode);
				void SetSpeed(float FPS);
				void SetFrame(int n);
				void SetFrames(int n);

				int GetMode() const;
				float GetSpeed() const;
				int GetFrame() const;
				int GetFrames() const;
			]]},
		},
	},
	modules = {
	},
}

--[[
#define HGEANIM_FWD			0
#define HGEANIM_REV			1
#define HGEANIM_PINGPONG	2
#define HGEANIM_NOPINGPONG	0
#define HGEANIM_LOOP		4
#define HGEANIM_NOLOOP		0
--]]
