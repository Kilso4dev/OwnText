cmake_minimum_required(VERSION 3.13)
project(OwnText C)

set(CMAKE_C_STANDARD 11)

file(GLOB FILES_ALL
    "./src/*.h"
    "./src/*.c")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -lm -g")

#add_executable(OwnText main.c termio.c owntext.h termio.h prog.c prog.h owntext.c Texts.h)

add_executable(OwnText ${FILES_ALL})

target_link_libraries(OwnText m)
target_link_libraries(OwnText ncurses)
