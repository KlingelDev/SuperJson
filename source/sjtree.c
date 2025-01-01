#include <linux/limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sjtree.h"

sjsontree_t *sjt_new(uint8_t type, char identifier[PATH_MAX+1]) {
  sjsontree_t *tree = malloc(sizeof(sjsontree_t));
  tree->type = type;
  strcpy(tree->identifier, identifier);
  return tree;
}

sjtelem_t *sjt_addroot(sjsontree_t *tree) {
  sjtelem_t *e = sjt_elemnew();
  tree->root = &e;
  return e;
}

sjtelem_t *sjt_elemnew() {
  return malloc(sizeof(sjtelem_t));
}

sjtelem_t *sjt_append(sjtelem_t root, sjtelem_t elem) {

}

sjtelem_t *sjt_remove(sjtelem_t elem) {

}

sjtelem_t *sjt_free(sjtelem_t elem) {

}
