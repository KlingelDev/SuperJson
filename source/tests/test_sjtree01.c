#include <linux/limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "testsuite.h"
#include "test_sjtree01.h"

#include "superjson.h"
#include "sjtree.h"

int main(int argc, char *argv[]) {
  struct Test *tests = CreateTests();

  AddTest(tests, "newtree", test_newtree);
  AddTest(tests, "newelement", test_newelem);
  AddTest(tests, "addroot", test_addroot);
  AddTest(tests, "append", test_append);

  int r = RunTest(tests, argc, argv);

  free(tests);

  return r;
}

int test_newtree() {
  sjsontree_t *tree = sjt_new(2, "test");
  int a = AssertThat(tree->type, IsEqualTo(2));
  free(tree);

  return a;
}

int test_newelem() {
  sjtelem_t *e = sjt_elemnew();

  return AssertPass;
}

int test_addroot() {
  sjsontree_t *tree = sjt_new(2, "test");
  sjtelem_t *root = sjt_addroot(tree);

  return AssertPass;
}

int test_append() {
  sjsontree_t *tree = sjt_new(2, "test");
  sjtelem_t *root = sjt_addroot(tree);
  sjtelem_t *e = sjt_elemnew();
  sjtelem_t *a = sjt_append(root, e);

  return AssertThat(e, IsEqualTo(a));
}
