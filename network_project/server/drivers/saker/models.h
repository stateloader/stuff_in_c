#ifndef MODELS_H_
#define MODELS_H_

#include <stdint.h>
#include "../sconfig.h"

inline static int8_t fileopen_check(FILE *file) {
  if (!file) {
    System_Message("failed to open file");
    return FAIL;
  }
  return SUCC;
}
/*
typedef struct FileItem {
  const uint8_t model;
  const char *path;
} file_item;

typedef struct ConnModel {
  int8_t set;
  char user[SBUFF];
  char pass[SBUFF];
} cmod_t;

typedef struct TempModel {
  int8_t set;
  char temp[SBUFF];
  char datm[TBUFF];
} tmod_t;

typedef struct DvceModel {
  int8_t set;
  int8_t led;
  char user[SBUFF];
  char datm[TBUFF];
} dmod_t;

typedef struct MesgModel {
  int8_t set;
  char user[SBUFF];
  char datm[TBUFF];
  char topc[SBUFF];
  char mesg[SBUFF];
} mmod_t;
*/
#endif