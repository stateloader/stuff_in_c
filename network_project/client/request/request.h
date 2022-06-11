#ifndef REQUEST_H_
#define REQUEST_H_

#include <stddef.h>
#include <stdint.h>

#define MAX_BUFFER 4096
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#define START 0
#define FETCH 1
#define STEER 2
#define LEAVE 3

size_t request_driver(char *request, uint8_t *online);

#endif
