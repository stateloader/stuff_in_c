/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               READ HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef FILEDRIVER_H_
#define FILEDRIVER_H_

#include "dbconfigs.h"

//---------------------------CMODEL, i think of it as an instance - a representation of a "row" - in the database (Client)
typedef struct CModel {
  size_t id;
  char username[DATA_BUFFER];
  char password[DATA_BUFFER];
} cmod_t;
//---------------------------SMODEL, i think of it as an instance - a representation of a "row" - in the database (Sample)
typedef struct SModel {
  size_t id;
  float temperature;
  float humidity;
  char datetime[TIME_BUFFER];
} smod_t;
//----------------------------FileDriver struct dealing with all logic about and around reading/writing from the databases
typedef struct FileDriver {
  size_t rows;
  uint8_t bill;
  cmod_t *table_client;
  smod_t *table_sample;
  size_t file_size;
  char *file_data;
  FILE *file;
} filed_t;
//----------------------f------------------------------------------------------------------------------------------drivers
uint8_t file_driver(filed_t *driver);
void free_driver(filed_t *driver);
//------------------------------------------------------------------------------------------------------------message print

#endif