#ifndef BROWSE_H_
#define BROWSE_H_

#include "scan/scan.h"

typedef struct Browse {
  char command[MAX_BUFFER];
  char comment[MAX_BUFFER];
} browse_t;

#endif
