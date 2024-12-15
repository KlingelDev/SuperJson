#include <linux/limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "superjson.h"

FILE *jsonfopen(char fn[PATH_MAX], char flag[3]) {
  FILE *fstream = fopen(fn, flag);

  if(fstream == NULL) {
    printf("Json file could not be opened.\n");
    return NULL;
  }

  return fstream;
}

int jsonfread(FILE *fstream, char *buffer, uint64_t buffersize) {


  return 0;
}

int jsonfclose(FILE *fstream) {
  fclose(fstream);
  return 0;
}
