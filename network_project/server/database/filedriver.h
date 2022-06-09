/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               READ HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef FILEDRIVER_H_
#define FILEDRIVER_H_

#include "database.h"

typedef struct MModel {
  size_t id;
  char username[DBUFF];
  char topic[DBUFF];
  char datetime[TBUFF];
  char message[MBUFF];
} mmod_t;
//----------------------------------------------------------------------------------------------------------------------*/
typedef struct CModel {
  size_t id;
  char username[DBUFF];
  char password[DBUFF];
} cmod_t;
//----------------------------------------------------------------------------------------------------------------------*/
typedef struct SModel {
  size_t id;
  char temperature[DBUFF];
  char datetime[TBUFF];
} smod_t;
//----------------------------------------------------------------------------------------------------------------------*/

typedef struct TableItem {
  uint8_t model;
  uint8_t membr;
  const char *file_path;
} table_item;
//----------------------------------------------------------------------------------------------------------------------*/
typedef struct FileDriver {
  uint8_t route;
  uint8_t model;
  size_t rows;
  size_t file_size;
  char *file_buffer;
  cmod_t *table_client;
  smod_t *table_sample;
  mmod_t *table_message;
  table_item item;
  FILE *file;
} filed_t;
//----------------------------------------------------------------------------------------------------------------------*/
typedef uint8_t (*filed_func)(filed_t *driver);

typedef struct FileDriverItem{
  const char *error_message;
  filed_func func;
} filed_item;

//----------------------f------------------------------------------------------------------------------------------drivers
uint8_t file_driver(uint8_t request, filed_t *driver);
void free_driver(filed_t *driver);
//------------------------------------------------------------------------------------------------------------message print

#endif