/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               READ HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef FILEDRIVER_H_
#define FILEDRIVER_H_

#include "dbconfigs.h"

typedef struct MModel {
  size_t id;
  char username[DATA_BUFFER];
  char topic[DATA_BUFFER];
  char datetime[TIME_BUFFER];
  char message[MESG_BUFFER];
} mmod_t;
//----------------------------------------------------------------------------------------------------------------------*/
typedef struct CModel {
  size_t id;
  char username[DATA_BUFFER];
  char password[DATA_BUFFER];
} cmod_t;
//----------------------------------------------------------------------------------------------------------------------*/
typedef struct SModel {
  size_t id;
  char temperature[DATA_BUFFER];
  char datetime[TIME_BUFFER];
} smod_t;
//----------------------------------------------------------------------------------------------------------------------*/
typedef struct TableItem {
  const char *file_path;
  uint8_t model;
  uint8_t interval;
  uint8_t members;
} table_item;

typedef struct FileDriver {
  size_t rows;
  size_t file_size;
  char *file_buffer;
  uint8_t model;
  uint8_t routine;
  cmod_t *table_client;
  smod_t *table_sample;
  mmod_t *table_message;
  table_item items;
  FILE *file;
} filed_t;
//----------------------------------------------------------------------------------------------------------------------*/
typedef uint8_t (*filed_func)(filed_t *driver);

typedef struct FileDriverItem{
  const char *error_message;
  filed_func func;
} filed_item;

//----------------------f------------------------------------------------------------------------------------------drivers
uint8_t file_driver(filed_t *driver);
void free_driver(filed_t *driver);
//------------------------------------------------------------------------------------------------------------message print

#endif