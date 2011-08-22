function hgeBuildDefinitionDB(files)
	local tbls = 'return'

	for i,v in  ipairs(files) do
		require(v:lower())
		tbls = tbls .. ' bind' .. v .. ','
	end

	buildDefinitionDB(loadstring(tbls:sub(0, -2))())
end

function hgeBind(class_name)
	local lower_class = class_name:lower()
	local bind_tbl = loadstring('return bind'..class_name)()

	-- Our forward declarations for the classes/structs
	for i,v in ipairs(bind_tbl.classes) do
		write([[
			class ]]..v.className..[[;
		]])
	end
	writeHeader(bind_tbl)
	flushWritten('cpp/lua_'..lower_class..'.h')

	writeIncludeBlock()
	write('#include "lua_'..lower_class..'.h"')
	write([[
		#include "]]..lower_class..[[.h"
	]])
	writeDefinitions(bind_tbl, 'bind_lua_'..class_name)
	flushWritten('cpp/lua_'..lower_class..'.cpp')
end

function generate()
	local files = {
		'hgeColor',
		'hgeRect',
		'hgeStrings',
		'hgeVector',
		'hgeResource', -- has members for sprite, animation, font, and others
	}

	hgeBuildDefinitionDB(files)

	for i,v in ipairs(files) do
		hgeBind(v)
	end
end