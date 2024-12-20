#include <linux/limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
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

sjsontree_t *get_elements(FILE *fstream) {
  fseek(fstream, 0, SEEK_SET);
  uint64_t b_num = 0;
  int bsize = 4096;
  char buff[bsize];

  uint64_t f_dquote = NULL;
  uint64_t s_dquote = NULL;
  uint64_t colon = NULL;

  int a[3][3];
  int ai = 0;
  sjsonfindex_t *index = NULL;

  while(fgets(buff, bsize, fstream)) {
    int i;

    for(i = 0; i < strlen(buff); i++) {
      char c = buff[i];

      if(c == '"') {
        if(!f_dquote) { f_dquote = b_num; }
        else if(!s_dquote) { s_dquote = b_num; }
        else if(f_dquote && s_dquote) { f_dquote = NULL; s_dquote = NULL; }
      }

      if(c == ':') {
        if(f_dquote && s_dquote) {
          // complete, reset
          printf("F %d S %d C %d\n", f_dquote, s_dquote, b_num);

          index = add_sjindex(f_dquote, b_num+1, index);
          printf("I %s\n", index->next ? "true" : "false");

          f_dquote = NULL;
          s_dquote = NULL;
        }
      }
      b_num++;
    }
  }

  sjsontree_t *jt = NULL;
  printf("next %s \n", index->next ? "true": "false");
  while(index->next != NULL) {
    int sbuffsize = index->end - index->start +1;
    char sbuffer[sbuffsize];

    fseek(fstream, index->start, SEEK_SET);
    fgets(sbuffer, sbuffsize, fstream);

    if(!jt) {
      jt = add_element(sbuffer, NULL);

    } else {
      jt = add_element(sbuffer, jt);
    }

    index = index->next;

    printf("%s %s\n", sbuffer, jt->name);
  }

  sjsontree_t *tree = malloc(sizeof(sjsontree_t));
  return tree;
}

// Add element to chain
sjsontree_t *add_element(char name[], sjsontree_t *prev) {
  sjsontree_t *njt = malloc(sizeof(sjsontree_t));
  strcpy(njt->name, name);
  njt->next = NULL;
  njt->prev = prev;
  return njt;
}

// Add Index
sjsonfindex_t *add_sjindex(uint64_t start, uint64_t end, sjsonfindex_t *prev) {
  sjsonfindex_t *nsji = malloc(sizeof(sjsonfindex_t));
  nsji->start = start;
  nsji->end = end;

  nsji->prev = prev;
  if(prev) {
    prev->next = nsji;
  }

  return nsji;
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
