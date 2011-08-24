find_package(Lua51 REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(cpp)

set(LUNA_GEN "${CMAKE_CURRENT_SOURCE_DIR}/luna-gen/luna_gen.lua")
set(HGEBINDING_LUA "${CMAKE_CURRENT_SOURCE_DIR}/binding/hgeBinding.lua")
set(HGEBINDING_LUA_ALL
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgeBinding.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hge.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgeanim.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgecolor.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgedistort.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgefont.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgegui.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgeguictrls.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgeparticle.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgerect.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgeresource.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgesprite.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgestrings.lua"
	"${CMAKE_CURRENT_SOURCE_DIR}/binding/hgevector.lua"
)

set(HGEBINDING_CPP
# Generated headers
	cpp/lua_hge.h
	cpp/lua_hgeanim.h
	cpp/lua_hgecolor.h
	cpp/lua_hgedistort.h
	cpp/lua_hgefont.h
	cpp/lua_hgegui.h
	cpp/lua_hgeguictrls.h
	cpp/lua_hgeparticle.h
	cpp/lua_hgerect.h
	cpp/lua_hgeresource.h
	cpp/lua_hgesprite.h
	cpp/lua_hgestrings.h
	cpp/lua_hgevector.h

# Generated source files
	cpp/lua_hge.cpp
	cpp/lua_hgeanim.cpp
	cpp/lua_hgecolor.cpp
	cpp/lua_hgedistort.cpp
	cpp/lua_hgefont.cpp
# 	cpp/lua_hgegui.cpp
	cpp/lua_hgeguictrls.cpp
	cpp/lua_hgeparticle.cpp
	cpp/lua_hgerect.cpp
# 	cpp/lua_hgeresource.cpp
	cpp/lua_hgesprite.cpp
	cpp/lua_hgestrings.cpp
	cpp/lua_hgevector.cpp
)

include_directories(
	${CMAKE_SOURCE_DIR}/src/core
	${CMAKE_SOURCE_DIR}/src/core/unix
	${CMAKE_SOURCE_DIR}/src/core/windows
	${CMAKE_CURRENT_BINARY_DIR}/cpp
	${CMAKE_CURRENT_SOURCE_DIR}/luna-gen
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cpp)

add_custom_command(
	OUTPUT ${HGEBINDING_CPP}
	DEPENDS "${LUNA_GEN}" ${HGEBINDING_LUA_ALL}
	PRE_BUILD
	COMMAND lua "${LUNA_GEN}" "${HGEBINDING_LUA}"
)

add_library(${HGE_BINDING_LUA}
	${HGEBINDING_CPP}
	luna-gen/luna.cpp
	luna-gen/luna.h
)
target_link_libraries(${HGE_BINDING_LUA} ${LUA_LIBRARY})

add_subdirectory(example)