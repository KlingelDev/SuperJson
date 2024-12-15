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

  int r = RunTest(tests, argc, argv);

  free(tests);

  return r;
}

int test_openfile() {
  char cwd[PATH_MAX];
  if(getcwd(cwd, sizeof(cwd)) == NULL) {
    perror("getcwd error.\n");
    return 1;
  }

  char testfp[PATH_MAX];
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

  remove(testfp);

  return 0;
}
