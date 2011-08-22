print("Hello HGE")

function test_bound(expected, real_value)
	print("should be "..tostring(expected).."::"..tostring(real_value))
end

function print_vector(v)
	print(v.x,v.y)
end

function print_separator()
	print("-------------------------------------")
end

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
