#include <linux/limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "superjson.h"

FILE *jsonfopen(char fn[PATH_MAX+1], char flag[3]) {
  FILE *fstream = fopen(fn, flag);

  if(fstream == NULL) {
    printf("Json file could not be opened.\n");
    return NULL;
  }

  return fstream;
}

int jsonfread(FILE *fstream, char *buffer, uint64_t buffersize) {
  if(fstream == NULL) {
    perror("file stream is not readable.\n");
    return 0;
  }

  int openclose = check_openclose(fstream);
  if(!openclose) {
    return 1;
  }

  while(fgets(buffer, buffersize, fstream)) {
  }

  return 1;
}

int check_openclose(FILE *fstream) {
  fseek(fstream, 0, SEEK_CUR);

  bool start = false;
  bool end = false;
  int bsize = 4096;
  char buff[bsize];

  while(fgets(buff, bsize, fstream)) {
    int i;

    for(i = 0; i < strlen(buff); i++) {
      char c = buff[i];

      if(c == '{') {
        start = true;
        continue;
      }

      if(c == '}') {
        end = true;
        continue;
      }

    } // for
  } // while

  if(start && end) {
    return 0;

  } else if(!start && end) {
    perror("Missing starting bracket.\n");
    return 1;

  } else if(start && !end) {
    perror("Missing ending bracket.\n");
    return 1;

  } else {
    perror("Missing toplevel brackets.\n");
    return 1;

  }
} // check_openclose

int jsonfclose(FILE *fstream) {
  fclose(fstream);
  return 0;
}
