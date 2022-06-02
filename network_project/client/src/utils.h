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

#define set_bit(byte, bit) byte |= (1 << bit)
#define get_bit(byte, bit) byte &= (1 << bit)
#define tog_bit(byte, bit) byte ^= (1 << bit)
#define clr_bit(byte, bit) byte &= ~(1 << bit)


/*
void print_byte(uint8_t byte) {
  for (uint8_t i = 1 << 7; i > 0; i = i / 2)
    (byte & i) ? printf("1") : printf("0");
}
*/

#endif