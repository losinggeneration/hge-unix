print("Hello HGE")

function test_bound(expected, real_value)
	local r,e = pcall(assert, expected == real_value)
	if r then
		print("test succeeded: "..tostring(expected).." == "..tostring(real_value))
	else
		print("test failed: ".. e .. " | "..tostring(expected).." ~= "..tostring(real_value))
	end
end

function print_vector(v)
	print(v.x,v.y)
end

function print_separator()
	print("-------------------------------------")
end

print('Doing some basic tests')

v = hge.Vector()
v1 = hge.Vector(2.2, 3.3)
print_vector(v)
print_vector(v1)
v3 = v:normalize()
print_vector(v3)
v4 = v1:rotate(0.5)
print_vector(v4)
v5 = v4 * 5
print_vector(v5)
print(v5:dot(v4))
print(v5:length())
print("testing ==")
test_bound(false, v5 == v4)
test_bound(true, v5 ~= v4)
test_bound(false, true)

print_separator()
local f = io.open('test_strings', 'w');
f:write('[HGESTRINGTABLE]\n')
f:write('string1="this is a test string"\n')
f:write('string2="this is another test"\n')
f:close()

s = hge.StringTable('test_strings')
print('lua: hgeStringTable string1 = '..s:getstring('string1'))
print('lua: hgeStringTable string2 = '..s:getstring('string2'))
-- nothing else really useful to be done with hgestrings yet

print_separator()

function print_rect(r)
	print(r.x1,r.x2,r.y1,r.y2)
end

r = hge.Rect()
print_rect(r)

r1 = hge.Rect(1,2,3,4)
print_rect(r1)
r1:clear()
print_rect(r1)
test_bound(true, r1:testpoint(1.5,3.5))
test_bound(false, r1:testpoint(5,5))
r2 = hge.Rect(8,9,10,11)
test_bound(false, r1:intersect(r2))
r3 = hge.Rect(1,2,5,6)
test_bound(true, r3:intersect(r1))
test_bound(false, r2:intersect(r3))

print_separator()

print("Tests finished, loading HGE")

print_separator()

function pairsByKeys (t, f)
   local a = {}
   for n in pairs(t) do table.insert(a, n) end
   if f==nil then
	   f=function (a,b) -- default key comparison function
		   if type(a)==type(b) then
			   return a<b
		   end
		   return type(a)<type(b)
	   end
   end
   table.sort(a, f)
   local i = 0      -- iterator variable
   local iter = function ()   -- iterator function
		   i = i + 1
		   if a[i] == nil then return nil
		   else return a[i], t[a[i]]
		   end
		end
   return iter
end

function printTable(t, bPrintUserData)
	local out="{"
	for k,v in pairsByKeys(t) do
		local tv=type(v)
		if tv=="string" or tv=="number" or tv=="boolean" then
			out=out..'['..k..']='..tostring(v)..', '
		elseif tv=="userdata" then
			if bPrintUserData==true then
				out=out..'\n['..k..']=\n'..v..', '
			else
				out=out..'['..k..']='..tv..', '
			end
		else
			out=out..'['..k..']='..tv..', '
		end
	end
	print(out..'}')
end

-- print(hge.Vertex.new():x)
-- os.exit()

-- Quad is the basic primitive in HGE
-- used for rendering graphics.
-- Quad contains 4 vertices, numbered
-- 0 to 3 clockwise.
quad = {
-- 	v = hge.Vertex.new()[4],
	tex = 0,
	blend = 0,
}

-- Handle for a sound effect
snd = HGE.HEFFECT

-- Some "gameplay" variables and constants
x = 100.0
y = 100.0
dx = 0.0
dy = 0.0

speed = 90
friction = 0.98

-- This function plays collision sound with
-- parameters based on sprite position and speed
function boom()
	local pan= tonumber((x - 400) / 4, 10)
	local pitch= (dx * dx + dy * dy) * 0.0005 + 0.2
	lhge:effect_playex(snd, 100, pan, pitch)
end

function FrameFunc()
	-- Get the time elapsed since last call of FrameFunc().
	-- This will help us to synchronize on different
	-- machines and video modes.
	local dt = lhge:timer_getdelta();

	-- Process keys
	if lhge:input_getkeystate(HGE.HGEK_ESCAPE) then
		return true
	end
	if lhge:input_getkeystate(HGE.HGEK_LEFT) then
		dx = dx - speed * dt
	end
	if lhge:input_getkeystate(HGE.HGEK_RIGHT) then
		dx = dx + speed * dt
	end
	if lhge:input_getkeystate(HGE.HGEK_UP) then
		dy = dy - speed * dt
	end
	if lhge:input_getkeystate(HGE.HGEK_DOWN) then
		dy = dy + speed * dt
	end

	-- Do some movement calculations and collision detection
	dx = dx * friction
	dy = dy * friction
	x = x + dx
	y = y + dy

	if x > 784 then
		x = 784 - (x - 784)
		dx = -dx
		boom()
	end
	if x < 16 then
		x = 16 + 16 - x
		dx = -dx
		boom()
	end
	if y > 584 then
		y = 584 - (y - 584)
		dy = -dy;
		boom();
	end
	if y < 16 then
		y = 16 + 16 - y;
		dy = -dy
		boom()
	end

	-- Set up quad's screen coordinates
-- 	quad.v[0].x = x - 16; quad.v[0].y = y - 16
-- 	quad.v[1].x = x + 16; quad.v[1].y = y - 16;
-- 	quad.v[2].x = x + 16; quad.v[2].y = y + 16;
-- 	quad.v[3].x = x - 16; quad.v[3].y = y + 16;

	-- Continue execution
	return false
end

function RenderFunc()
	-- Begin rendering quads.
	-- This function must be called
	-- before any actual rendering.
	lhge:gfx_beginscene(0)

	-- Clear screen with black color
	lhge:gfx_clear(0)

	-- Render quads here. This time just
	-- one of them will serve our needs.
-- 	lhge:gfx_renderquad(quad)

	-- End rendering and update the screen
	lhge:gfx_endscene()

	-- RenderFunc should always return false
	return false
end

if lhge:system_initiate() then
	require('bit')

	-- Load sound and texture
	snd = lhge:effect_load("menu.ogg", 0);

	-- for windows
-- 	snd = lhge:effect_load("menu.wav");

	quad.tex = lhge:texture_load("particles.png", 0, false);

	if snd == 0 or quad.tex == 0 then
		-- If one of the data files is not found, display
		-- an error message and shutdown.
		print("Error: Can't load menu.wav or particles.png");

		lhge:system_shutdown();
		lhge:release();
		return 1;
	end

	-- Set up quad which we will use for rendering sprite
	quad.blend = bit.bor(bit.bor(HGE.BLEND_ALPHAADD, HGE.BLEND_COLORMUL), HGE.BLEND_ZWRITE);

-- 	for(int i=0;i<4;i++)
-- 	{
-- 		-- Set up z-coordinate of vertices
-- 		quad.v[i].z=0.5f;
-- 		-- Set up color. The format of DWORD col is 0xAARRGGBB
-- 		quad.v[i].col=0xFFFFA000;
-- 	}
--
-- 	-- Set up quad's texture coordinates.
-- 	-- 0,0 means top left corner and 1,1 -
-- 	-- bottom right corner of the texture.
-- 	quad.v[0].tx=96.0/128.0; quad.v[0].ty=64.0/128.0;
-- 	quad.v[1].tx=128.0/128.0; quad.v[1].ty=64.0/128.0;
-- 	quad.v[2].tx=128.0/128.0; quad.v[2].ty=96.0/128.0;
-- 	quad.v[3].tx=96.0/128.0; quad.v[3].ty=96.0/128.0;

	lhge:system_start()

	-- Free loaded texture and sound
	lhge:texture_free(quad.tex);
	lhge:effect_free(snd);
else
	fprintf(stderr, "Unable to initialize HGE: %s\n", lhge:system_geterrormessage())
end

-- Finish up hge
lhge:system_shutdown();
lhge:release();