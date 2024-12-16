struct jsonfile {
  bool open;
  char filename[PATH_MAX+1];
  long unsigned int size;
};

typedef struct jsonfile jsonfile_t;

FILE *jsonfopen(char fn[PATH_MAX], char flag[3]);
int jsonfread(FILE *fstream, char *buffer, uint64_t buffersize);
int jsonfclose(FILE *fstream);
int check_openclose(FILE *fstream);
