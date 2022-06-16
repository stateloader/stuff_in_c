#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdint.h>
#include "reader.h"
#include "writer.h"
/*
#define PCLNT "src/client.dat"   // path client          - relative path to .dat-file storing clientdata.
#define PSMPL "src/sample.dat"   // Path sample          - relative path to .dat-file storing sampledata.
#define PMSGE "src/message.dat"  // Path message         - relative path to .dat-file storing messagedata.
#define PDVCE "src/device.dat"   // Path device          - relative path to .dat-file storing devicedata.
*/
int8_t database_driver(read_t *reader, write_t *writer);

#endif