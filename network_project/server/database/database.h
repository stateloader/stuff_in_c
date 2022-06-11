#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdint.h>
#include "dbconfig.h"
#include "reader.h"
#include "writer.h"

uint8_t database_driver(read_t * reader, write_t *writer, uint8_t request, const char *package);

#endif