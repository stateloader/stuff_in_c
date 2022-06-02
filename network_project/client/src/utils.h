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

#endif
