require('hgevector')

function hgeBind(class_name)
	local bind_tbl = loadstring('return bind'..class_name)()
	local lower_class = class_name:lower();
	buildDefinitionDB(bind_tbl)
	write([[
		class ]]..class_name..[[;
	]])
	writeHeader(bind_tbl)
	flushWritten('cpp/lua_'..lower_class..'.h')

	writeIncludeBlock()
	write('#include "lua_'..lower_class..'.h"')
	write([[
		#include "]]..lower_class..[[.h"
	]])
	writeDefinitions(bindhgeVector, 'bind_'..class_name)
	flushWritten('cpp/lua_'..lower_class..'.cpp')
end

function generate()
	hgeBind("hgeVector")
-- 	hgeVectorBind()
end