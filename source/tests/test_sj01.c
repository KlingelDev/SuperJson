#include <linux/limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "testsuite.h"
#include "test_sj01.h"

#include "superjson.h"

int main(int argc, char *argv[]) {
  struct Test *tests = CreateTests();

  AddTest(tests, "openfile", test_openfile);
  AddTest(tests, "readfile", test_readfile);
  AddTest(tests, "openclose", test_openclosebracket);
  AddTest(tests, "openclose_fail", test_openclosebracket_fail);
  AddTest(tests, "getelements", test_getelements);

  setup_once();
  int r = RunTest(tests, argc, argv);

  free(tests);

  return r;
}

int setup_once() {
}

int test_openfile() {
  char cwd[PATH_MAX+1];
  if(getcwd(cwd, sizeof(cwd)) == NULL) {
    perror("getcwd error.\n");
    return AssertFail;
  }

  char testfp[PATH_MAX+1];
  sprintf(testfp, "%s/%s", cwd, "testfileopen01.json");

  FILE *jtestfile;

  jtestfile = fopen(testfp, "w");
  if(jtestfile == NULL) {
    perror("Could not open testfile");
    return 1;
  }

  fprintf(jtestfile, "{ \"test\"= 1 }");
  fclose(jtestfile);

  FILE *testfile;
  testfile = jsonfopen(testfp, "r");

  if(testfile != NULL) {
    jsonfclose(testfile);
    remove(testfp);

    return AssertPass;
  }

  return AssertFail;
}

int test_readfile_null() {
  FILE *tjsonfile = NULL;

  uint64_t bsize = 4096;
  char buffer[bsize];
  int r = 0;
  r = jsonfread(tjsonfile, buffer, bsize);

  free(tjsonfile);
  free(buffer);

  return AssertThat(r, IsEqualTo(1));
}

int test_readfile() {
  char fp[] = "../source/tests/testfiles/test02.json";
  char *abspath = realpath(fp, NULL);

  FILE *tjsonfile;
  tjsonfile = jsonfopen(abspath, "r");
  uint64_t bsize = 4096;
  char buffer[bsize];
  int r = 0;
  r = jsonfread(tjsonfile, buffer, bsize);

  return AssertThat(r, IsEqualTo(1));
}

int test_openclosebracket() {
  char fp[] = "../source/tests/testfiles/test02.json";
  char *abspath = realpath(fp, NULL);

  FILE *tjsonfile;
  tjsonfile = jsonfopen(abspath, "r");
  uint64_t bsize = 4096;
  char buffer[bsize];
  int r = 0;
  r = check_openclose(tjsonfile);

  return AssertThat(r, IsEqualToZero);
}

int test_openclosebracket_fail() {
  char fp[] = "../source/tests/testfiles/test02_broken.json";
  char *abspath = realpath(fp, NULL);

  FILE *tjsonfile;
  tjsonfile = jsonfopen(abspath, "r");
  uint64_t bsize = 4096;
  char buffer[bsize];
  int r = 0;
  r = check_openclose(tjsonfile);

  return AssertThat(r, IsEqualToZero);
}

int test_getelements() {
  char fp[] = "../source/tests/testfiles/test03.json";
  char *abspath = realpath(fp, NULL);

  FILE *tjsonfile;
  tjsonfile = jsonfopen(abspath, "r");
  uint64_t bsize = 4096;
  char buffer[bsize];
  get_elements(tjsonfile);

  return AssertPass;
}
