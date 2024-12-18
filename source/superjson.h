struct jsonfile {
  bool open;
  char filename[PATH_MAX+1];
  long unsigned int size;
};

typedef struct jsonfile jsonfile_t;

struct SuperJsonTree {
  uint64_t level;
  uint64_t stream_pos;
  char name[4096];
  struct SuperJsonTree *next;
  struct SuperJsonTree *prev;
  struct SuperJsonTree *root;
};

typedef struct SuperJsonTree sjsontree_t;

FILE *jsonfopen(char fn[PATH_MAX], char flag[3]);
int jsonfread(FILE *fstream, char *buffer, uint64_t buffersize);
int jsonfclose(FILE *fstream);

int check_openclose(FILE *fstream);
sjsontree_t *get_elements(FILE *fstream);
sjsontree_t *add_element(char name[], sjsontree_t *prev);
