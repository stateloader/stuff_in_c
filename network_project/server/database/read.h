#ifndef READ_H_
#define READ_H_

#include <stdio.h>
#include <stddef.h>

#define FILE_BUFFER 262114
#define USERDATA 16
#define TIMESTAMP 24
#define INTERVAL_SM 4
#define INTERVAL_CM 3

typedef struct CModel {
  size_t id;
  char username[USERDATA];
  char password[USERDATA];
} cmod_t;

typedef struct SModel {
  size_t id;
  float temperature;
  float humidity;
  char timestamp[TIMESTAMP];
} smod_t;

typedef struct Reader {
  size_t count_entries;
  cmod_t *client_model;
  smod_t *sample_model;
  char *file_data;
  size_t file_size;
  FILE *file;
} read_t;

void read_driver(read_t *reader);

#endif
