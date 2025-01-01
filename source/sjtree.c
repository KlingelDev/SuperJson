#include <linux/limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sjtree.h"

sjsontree_t *sjt_new(uint8_t type, char identifier[NAMEMAX]) {
  sjsontree_t *tree = malloc(sizeof(sjsontree_t));
  tree->type = type;
  strcpy(tree->identifier, identifier);

  return tree;
}

sjtelem_t *sjt_addroot(sjsontree_t *tree,
                       uint64_t pos,
                       char elementname[NAMEMAX]) {
  sjtelem_t *e = sjt_elemnew(0, pos, elementname);
  tree->root = e;

  return e;
}

sjtelem_t *sjt_elemnew(uint64_t level,
                       uint64_t pos,
                       char elementname[NAMEMAX]) {
  sjtelem_t *e = malloc(sizeof(sjtelem_t));
  e->level = level;
  e->pos = pos;
  strcpy(e->ename, elementname);
  return e;
}

sjtelem_t *sjt_append(sjtelem_t *root,
                      sjtelem_t *elem) {

  root->next = elem;
  return elem;
}

sjtelem_t *sjt_remove(sjtelem_t *elem) {

}

sjtelem_t *sjt_free(sjtelem_t *elem) {

}
