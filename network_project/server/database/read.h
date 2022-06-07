#ifndef READ_H_
#define READ_H_

#include <stdio.h>
#include <stddef.h>

#define DELIM '|'

#define INTERVAL_SM 4
#define INTERVAL_CM 2

#define MEMB_SMODEL_TP 0
#define MEMB_SMODEL_HD 1
#define MEMB_SMODEL_TS 2

#define MAX_FILE_DATA 4096
#define MAX_USER_DATA 64
#define MAX_PASS_DATA 64

#define TIMESTAMP 24

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

void read_driver(read_t *reader);
void free_driver(read_t *reader);

#endif