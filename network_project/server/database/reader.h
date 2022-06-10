/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               READ HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef READER_H_
#define READER_H_

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
typedef struct RouteItem {
  uint8_t model;
  uint8_t membr;
  const char *file_path;
} route_item;
//----------------------------------------------------------------------------------------------------------------------*/
typedef struct ReadDriver {
  uint8_t model;
  size_t rows;
  size_t file_size;
  char *file_buffer;
  cmod_t *table_client;
  smod_t *table_sample;
  mmod_t *table_message;
  route_item item;
  FILE *file;
} read_t;
//----------------------------------------------------------------------------------------------------------------------*/
typedef uint8_t (*read_func)(read_t *reader);

typedef struct FileDriverItem{
  const char *error_message;
  read_func func;
} read_item;

//----------------------f------------------------------------------------------------------------------------------drivers
uint8_t database_reader(uint8_t request, read_t *reader);
void reader_free(read_t *reader);
//------------------------------------------------------------------------------------------------------------message print

#endif