cmake_minimum_required(VERSION 3.18)
project(LibSuperJson)

include_directories(tests)
add_subdirectory(tests)

set(CMAKE_C_FLAGS_DEBUG "-pthread -g3 -ggdb -Wall")
set(CMAKE_C_FLAGS "")

add_library(libsuperjson
  superjson.c
  sjtree.c
)

enable_testing()

add_test(NAME tsj01_openfile COMMAND testsuperjson01 --config openfile)
add_test(NAME tsj01_readfile COMMAND testsuperjson01 --config readfile)
add_test(NAME tsj01_openclosebracket COMMAND testsuperjson01 --config openclose)
add_test(NAME tsj01_openclosebracket_fail COMMAND testsuperjson01 --config
  openclose_fail)
set_property(TEST tsj01_openclosebracket_fail PROPERTY WILL_FAIL TRUE)
#add_test(NAME tsj01_getelements COMMAND testsuperjson01 --config getelements)

# SJTree
add_test(NAME tsjt_newtree COMMAND testsjtree01 --config newtree)
add_test(NAME tsjt_newelem COMMAND testsjtree01 --config newelement)
add_test(NAME tsjt_addroot COMMAND testsjtree01 --config addroot)
add_test(NAME tsjt_append COMMAND testsjtree01 --config append)
add_test(NAME tsjt_getlast COMMAND testsjtree01 --config getlast)
