#ifndef READ_H_
#define READ_H_

#include <stdio.h>
#include <stddef.h>

#define FILE_BUFFER 262114
#define DELIM '|'
#define PIPE 6

typedef struct Entry {
  size_t id;
  size_t timestamp;
  char *username;
  char *password;
  char *request;
  char *response;
} entr_t;

typedef struct Reader {
  size_t data_size;
  size_t item_size;
  entr_t *entries;
  char *file_data;
  FILE *file;
} read_t;

void read_driver(read_t *reader);

#endif
