struct jsonfile {
  bool open;
  char filename[PATH_MAX+1];
  long unsigned int size;
};

typedef struct jsonfile jsonfile_t;

struct SuperJsonTree {
  uint64_t level;
  uint64_t pos;
  char name[4096];
  struct SuperJsonTree *next;
  struct SuperJsonTree *prev;
  struct SuperJsonTree *root;
};

typedef struct SuperJsonTree sjsontree_t;

// Byte position start end of element in filestream.
struct SuperJsonFileIndex {
  uint64_t start;
  uint64_t end;
  struct SuperJsonFileIndex *next;
  struct SuperJsonFileIndex *prev;
};

typedef struct SuperJsonFileIndex sjsonfindex_t;

FILE *jsonfopen(char fn[PATH_MAX], char flag[3]);
int jsonfread(FILE *fstream, char *buffer, uint64_t buffersize);
int jsonfclose(FILE *fstream);

int check_openclose(FILE *fstream);
sjsontree_t *get_elements(FILE *fstream);
sjsontree_t *add_element(char name[], sjsontree_t *prev);
sjsonfindex_t *add_sjindex(uint64_t start, uint64_t end, sjsonfindex_t *prev);
