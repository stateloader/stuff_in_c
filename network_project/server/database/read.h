#ifndef READ_H_
#define READ_H_

#include <stdio.h>
#include <stddef.h>

#define DELIM '|'

#define MAX_FILE_DATA 262114           // File Size Buffer
#define MAX_USER_DATA 64
#define MAX_PASS_DATA 64

#define TIMESTAMP 24
#define INTERVAL_SM 4
#define INTERVAL_CM 3

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
  size_t model_count;             // given number of entries ("SM or CM").
  cmod_t **model_cmods;          // handler for CModel-array.
  smod_t **model_smods;          // handler for SModel-array.
  size_t file_size;
  char *file_data;
  FILE *file;
} read_t;

void read_driver(read_t *reader);
void free_driver(read_t *reader);

#endif
