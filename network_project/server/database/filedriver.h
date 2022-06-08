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
  char temperature[DATA_BUFFER];
  char datetime[DATA_BUFFER];
} smod_t;
//----------------------------FileDriver struct dealing with all logic about and around reading/writing from the databases
typedef struct FileDriver {
  uint8_t routine, model;
  size_t rows, file_size;
  cmod_t *table_client;
  smod_t *table_sample;
  char *file_data;
  FILE *file;
} filed_t;
//----------------------------FileDriver struct dealing with all logic about and around reading/writing from the databases
typedef uint8_t (*filed_func)(filed_t *driver);
//static void Error_Message(const char *action, const char *result, const char *note) {
typedef struct FileDriverItem{
  const char *error_message;
  filed_func func;
} filed_item;
//----------------------f------------------------------------------------------------------------------------------drivers
uint8_t file_driver(filed_t *driver);
void free_driver(filed_t *driver);
//------------------------------------------------------------------------------------------------------------message print

#endif