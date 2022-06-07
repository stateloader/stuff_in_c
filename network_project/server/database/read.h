#ifndef READ_H_
#define READ_H_

#include <stdio.h>
#include <stddef.h>

#define MAX_FILE_DATA 262114           // File Size Buffer
#define TIMESTAMP 24
#define INTERVAL_SM 4
#define INTERVAL_CM 3

typedef struct CModel {
  size_t id;
  char *username;
  char *password;
} cmod_t;

typedef struct SModel {
  size_t id;
  float temperature;
  float humidity;
  char timestamp[TIMESTAMP];
} smod_t;

typedef struct Reader {
  size_t entry_count;             // given number of entries ("SM or CM").
  size_t *size_CMmodels;          // array of SModel-sizes.
  size_t *size_SMmodels;          // array of CModel-sizes.
  cmod_t **client_model;          // handler for CModel-array.
  smod_t **sample_model;          // handler for SModel-array.
  size_t file_size;
  char *file_data;
  FILE *file;
} read_t;

void read_driver(read_t *reader);

#endif
