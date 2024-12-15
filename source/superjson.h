struct jsonfile_t {
  bool open;
  char filename[1024];
  long unsigned int size;
};

FILE *jsonfopen(char fn[PATH_MAX], char flag[3]);
int jsonfread(FILE *fstream, char *buffer, uint64_t buffersize);
int jsonfclose(FILE *fstream);
