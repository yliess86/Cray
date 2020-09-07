cmake_minimum_required(VERSION 3.10)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c" main.c)
add_executable(cray ${SOURCES})

target_compile_options(cray PUBLIC -Wall -Wextra -Werror -O3)
target_link_libraries(cray PUBLIC m png pthread)