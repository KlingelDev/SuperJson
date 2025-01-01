struct SuperJsonTree {
  /*********************
   * Type id - Type
   * 0       - Unkown
   * 1       - File
   * 2       - Memory
   ********************/
  uint8_t type;
  char identifier[PATH_MAX+1];
  struct SuperJasonTreeElement *root;
};

typedef struct SuperJsonTree sjsontree_t;

struct SuperJsonTreeElement {
  uint64_t level;
  uint64_t pos;
  char elemname[PATH_MAX+1];
  struct SuperJsonTree *next;
  struct SuperJsonTree *prev;
  struct SuperJsonTree *root;
};

typedef struct SuperJsonTreeElement sjtelem_t;

sjsontree_t *sjt_new(uint8_t type, char identifier[PATH_MAX+1]);
sjtelem_t *sjt_elemnew();
sjtelem_t *sjt_addroot(sjsontree_t *tree);
sjtelem_t *sjt_append(sjtelem_t root, sjtelem_t elem);
sjtelem_t *sjt_remove(sjtelem_t elem);
sjtelem_t *sjt_free(sjtelem_t elem);

