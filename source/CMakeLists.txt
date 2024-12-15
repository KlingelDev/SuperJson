cmake_minimum_required(VERSION 3.18)
project(LibSuperJson)

include_directories(tests)
add_subdirectory(tests)

set(CMAKE_C_FLAGS_DEBUG "-pthread -g3 -ggdb -Wall")
set(CMAKE_C_FLAGS "")

add_library(libsuperjson
  superjson.h
  superjson.c
)

enable_testing()

add_test(NAME tsj01_openfile COMMAND testsuperjson01 --config openfile)
