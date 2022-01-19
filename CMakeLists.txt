# CMakeList.txt : CMake project for DSnake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("DSnake")


set(ARCH x64)

set (DEPS "${CMAKE_CURRENT_SOURCE_DIR}/deps")
set (SDL2_INCLUDE "${DEPS}/SDL2/include")
set (SDL2_LIB "${DEPS}/SDL2/lib/${ARCH}")

# Add source to this project's executable.
add_executable (DSnake "src/main.c" "include/game.h" "src/game.c" "include/snake.h" "src/snake.c")
# TODO: Add tests and install targets if needed.

add_custom_command(
        TARGET DSnake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SDL2_LIB}/SDL2.dll
                ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll)

target_include_directories (DSnake PUBLIC ${SDL2_INCLUDE} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries (DSnake ${SDL2_LIB}/SDL2.lib ${SDL2_LIB}/SDL2main.lib)
