#ifndef REQUEST_H_
#define REQUEST_H_

#include <stddef.h>
#include <stdint.h>
#include "utils.h"

#define START 0
#define FETCH 1
#define STEER 2
#define LEAVE 3

int request_driver(char *request);

#endif
