cmake_minimum_required(VERSION 3.13)
project(source C)

set(CMAKE_C_STANDARD 99)

add_executable(source main.c mpc.c mpc.h value_type.h read.h headers.h read.c value_type.c eval.c eval.h builtin.c builtin.h hash_table.c hash_table.h)