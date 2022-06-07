#ifndef READ_H_
#define READ_H_

#include <stdio.h>
#include <stddef.h>
#include "dbconfigs.h"

typedef struct CModel {
  size_t id;
  char username[MAX_USER_DATA];
  char password[MAX_PASS_DATA];
} cmod_t;

typedef struct SModel {
  size_t id;
  float temperature;
  float humidity;
  char timestamp[TIMESTAMP];
} smod_t;

typedef struct Reader {
  size_t rows;
  cmod_t *table_client;
  smod_t *table_sample;
  size_t file_size;
  char *file_data;
  FILE *file;
} read_t;

typedef void (*read_func)(read_t *read);

typedef struct {
  const char *sysmesg;
  read_func func;
} read_item;

void read_driver(read_t *reader);
void free_driver(read_t *reader);

#endif