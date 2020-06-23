cmake_minimum_required(VERSION 3.13)
project(vemacs C)

set(CMAKE_C_STANDARD 11)

file(GLOB FILES_ALL
    "src/*.h"
    "src/*.c")

foreach (CI IN LISTS FILES_ALL)
    message(STATUS "${CI}")
endforeach()
message("\n")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -lm -g")

add_executable(vemacs ${FILES_ALL})

target_link_libraries(vemacs m)
target_link_libraries(vemacs ncurses)

# TODO Fix for tests
list(REMOVE_ITEM FILES_ALL EXCLUDE REGEX ".*src\/vemacs.c")

foreach (CI IN LISTS FILES_ALL)
    message(STATUS "${CI}")
endforeach()


add_executable(tests_all ./test/test_buf.c ${FILES_ALL})

target_link_libraries(tests_all m)
target_link_libraries(tests_all ncurses)

