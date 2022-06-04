#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_BUFFER 4096

#define check_term(str, len) (str[len - 1] == '\0')

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

/*
void print_byte(uint8_t byte) {
  for (uint8_t i = 1 << 7; i > 0; i = i / 2)
    (byte & i) ? printf("1") : printf("0");
}
*/
#endif
