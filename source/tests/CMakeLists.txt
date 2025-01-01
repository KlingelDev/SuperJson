set(LIBTESTSUITE_PATH "/home/karl/dev/TestSuite")
include_directories(${LIBTESTSUITE_PATH})

include_directories(..)

add_library(libtestsuite
  ${LIBTESTSUITE_PATH}/testsuite.c
)

add_executable(testsuperjson01
  test_sj01.c
)

add_executable(testsjtree01
  test_sjtree01.c
)
target_link_libraries(testsuperjson01 libtestsuite libsuperjson)
target_link_libraries(testsjtree01 libtestsuite libsuperjson)

