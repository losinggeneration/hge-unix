print("Hello HGE")
function print_vector(v)
	print(v.x,v.y)
end
v = hge.Vector()
v1 = hge.Vector(2.2, 3.3)
print_vector(v)
print_vector(v1)
v3 = v:Normalize()
print_vector(v3)
v4 = v1:Rotate(0.5)
print_vector(v4)
v5 = v4 * 5
print_vector(v5)
print(v5:Dot(v4))
print(v5:Length())

s = hge.StringTable("hge_script.lua")
-- Seems to not work
--print(s.GetString(""))
-- nothing else really useful to be done with hgestrings yet

function print_rect(r)
	print(r.x1,r.x2,r.y1,r.y2)
end

r = hge.Rect()
print_rect(r)

r1 = hge.Rect(1,2,3,4)
print_rect(r1)
r1:Clear()
print_rect(r1)
print(r1:TestPoint(1.5,3.5))
print(r1:TestPoint(5,5))
r2 = hge.Rect(8,9,10,11)
print(r1:Intersect(r2))
r3 = hge.Rect(1,2,5,6)
print(r3:Intersect(r1))
print(r2:Intersect(r3))
