include_directories(
	${CMAKE_SOURCE_DIR}/src/core
	${CMAKE_SOURCE_DIR}/src/core/unix
	${CMAKE_SOURCE_DIR}/src/core/windows
	${CMAKE_CURRENT_BINARY_DIR}/../cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../luna-gen
)

set(LUA_SCRIPTING_EXAMPLE_SRCS
	main.cpp
)

add_executable(lua_scripting_example ${LUA_SCRIPTING_EXAMPLE_SRCS})
target_link_libraries(lua_scripting_example ${HGE_HELPER_LIBRARY})
