cmake_minimum_required(VERSION 3.16)

project(compiler C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(compiler
    src/main.c
    src/lexer.c
    src/parser.c
    src/ast.c
)

target_include_directories(compiler PRIVATE include)

if(MSVC)
    target_compile_options(compiler PRIVATE /W4 /WX)
    target_compile_definitions(compiler PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(compiler PRIVATE -Wall -Wextra -Werror)
endif()
