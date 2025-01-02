#define NAMEMAX 1024

struct SuperJsonTree {
  /*********************
   * Type id - Type
   * 0       - Unkown
   * 1       - File
   * 2       - Memory
   ********************/
  uint8_t type;
  char identifier[NAMEMAX];
  struct SuperJsonTreeElement *root;
};

typedef struct SuperJsonTree sjsontree_t;

struct SuperJsonTreeElement {
  uint64_t level;
  uint64_t pos;
  char ename[NAMEMAX];
  struct SuperJsonTreeElement *next;
  struct SuperJsonTreeElement *prev;
  struct SuperJsonTreeElement *root;
};

typedef struct SuperJsonTreeElement sjtelem_t;

sjsontree_t *sjt_new(uint8_t type, char identifier[NAMEMAX]);
sjtelem_t *sjt_elemnew(uint64_t level,
                       uint64_t pos,
                       char elementname[NAMEMAX]);
sjtelem_t *sjt_addroot(sjsontree_t *tree,
                       uint64_t pos,
                       char elementname[NAMEMAX]);
sjtelem_t *sjt_append(sjtelem_t *root, sjtelem_t *elem);
sjtelem_t *sjt_remove(sjtelem_t *elem);
sjtelem_t *sjt_free(sjtelem_t *elem);
sjtelem_t *sjt_getlast(sjtelem_t *elem);
