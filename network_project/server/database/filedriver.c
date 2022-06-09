/*------------------------------------------------------------------------------------------------------------------------
                                                                                                         FILEDRIVER MODULE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/

#include <string.h>
#include "dbconfigs.h"
#include "filedriver.h"

static uint8_t MODELS[] = {CLIENT, SAMPLE};
static uint8_t DMNUMS[] = {DMNUM_CLIENT, DMNUM_SAMPLE};
static char *FILE_PATH[] = {PATH_CLIENT, PATH_SAMPLE};

//-----------------------------------------------------------------------------------------------read routine logic part

static table_item table_items[] = {
  {"resources/client.txt", CLIENT, DMNUM_CLIENT, 1},
  {"resources/sample.txt", SAMPLE, DMNUM_SAMPLE, 1},
};

static uint8_t read_fetch_file(filed_t *driver) {
//iterates through existing models/tables from database. opens "mapped" path.

  uint8_t result = 0;
  for (size_t i = 0; i < ARRAY_SIZE(MODELS); i++) {
    if (driver->model == MODELS[i]) {
      result = (driver->file = fopen(FILE_PATH[i], "r")) != NULL ? 1 : 0;
      return result;
    }
  }
  return FAIL;
}

static uint8_t read_fetch_filebuff(filed_t *driver) {
//alloc memory size of FILE_BUFFER.

  uint8_t result = (driver->file_buffer = calloc(FILE_BUFFER, sizeof(char))) != NULL ? SUCC : FAIL;
  return result;
}

static uint8_t read_fetch_filedata(filed_t *driver) {
//reads file-content to FILE_BUFFER, storing it's size in member file_size.

  driver->file_size = fread(driver->file_buffer, sizeof(char), FILE_BUFFER, driver->file);
  uint8_t result = (driver->file_size > 0) ? SUCC : FAIL; 
  return result;
}

static uint8_t read_fetch_filerows(filed_t *driver) {

  uint8_t interval = 0;

  for (size_t i = 0; i < ARRAY_SIZE(MODELS); i++) {
    if (driver->model == MODELS[i])
      interval = DMNUMS[i];
  }

  for (size_t i = 0; i < driver->file_size; i++)
    driver->rows += (driver->file_buffer[i] == DELIM) ? 1 : 0;
  driver->rows = (driver->rows / interval);

  return SUCC;
}

static uint8_t read_fetch_rowmem(filed_t *driver) {

  uint8_t result = 0;

  switch(driver->model) {

  case CLIENT:
    result = (driver->table_client = malloc(sizeof(cmod_t) * driver->rows)) != NULL ? SUCC : FAIL;
    if (result) {
      for (size_t i = 0; i < driver->rows; i++) {
        cmod_t rows = {.id = i};
        driver->table_client[i] = rows;
      }
    }
    break;
  case SAMPLE:
    result = (driver->table_sample = malloc(sizeof(smod_t) * driver->rows)) != NULL ? SUCC : FAIL;
    if (result) {
      for (size_t i = 0; i < driver->rows; i++) {
        smod_t rows = {.id = i};
        driver->table_sample[i] = rows;
      }
    }
    break;
    
  }
  return result;
}
//-----------------------------------------------------------------------------------------------read routine logic part 2

static uint8_t fetch_client_data(filed_t *driver) {

  uint8_t state = STATE_USER;
  size_t index = 0, row = 0;

  for (size_t i = 0; i < driver->file_size; i++) {
    char byte = driver->file_buffer[i];

    switch(state) {
    case STATE_USER:
      if (byte != DELIM) {
        driver->table_client[row].username[index] = byte;
        index++;
      } else {
        driver->table_client[row].username[index] = '\0';
        state = STATE_PASS;
        index = 0;
      }
      break;

    case STATE_PASS:
      if (byte != DELIM) {
        driver->table_client[row].password[index] = byte;
        index++;
      } else {
        driver->table_client[row].password[index] = '\0';
        state = STATE_USER;
        index = 0, row++;
      }
      break;
    default:
      free_driver(driver);
      return FAIL;
    }
  }
  return SUCC;
}

static uint8_t fetch_sample_data(filed_t *driver) {

  uint8_t state = STATE_TEMP;
  size_t index = 0, row = 0;

  for (size_t i = 0; i < driver->file_size; i++) {
    char byte = driver->file_buffer[i];

    switch(state) {
    case STATE_TEMP:
      if (byte != DELIM) {
        driver->table_sample[row].temperature[index] = byte;
        index++;
      } else {
        driver->table_sample[row].temperature[index] = '\0';
        state = STATE_DTME;
        index = 0;
      }
      break;
    case STATE_DTME:
      if (byte != DELIM) {
        driver->table_sample[row].datetime[index] = byte;
        index++;
      } else {
        driver->table_sample[row].datetime[index] = '\0';
        state = STATE_TEMP;
        index = 0, row++;
      }
      break;
    default:
      free_driver(driver);
      return FAIL;
    }
  }
  return SUCC;
}

static uint8_t rread_fetch_rowdata(filed_t *driver) {

  switch(driver->model) {
  case CLIENT:
    return fetch_client_data(driver);
    break;
  case SAMPLE:
    return fetch_sample_data(driver);
    break;
  default:
    return FAIL;
  }
  return SUCC;
}

static filed_item filed_read_items[] = {
  {"failed to open file\n", read_fetch_file}, {"failed to create filebuffer\n", read_fetch_filebuff},
  {"failed to read file\n",read_fetch_filedata}, {"failed to fetch amnt rows\n", read_fetch_filerows},
  {"failed to memalloc\n", read_fetch_rowmem}, {"failed copy data_rows\n", rread_fetch_rowdata}
};

static uint8_t run_read_routine(filed_t *driver) {

  for (size_t i = 0; i < ARRAY_SIZE(filed_read_items); i++) {
    if (!filed_read_items[i].func(driver)) {
      printf("%s\n", filed_read_items[i].error_message);
      return FAIL;
    }
  }
  return SUCC;
}

static uint8_t run_write_routine(filed_t *driver) {
  printf("write routine test\n");
  return SUCC;
}

//-----------------------------------------------------------------------------------------------------write routine logic
//------------------------------------------------------------------------------------------------------------------------

uint8_t file_driver(filed_t *driver) {
  
  switch(driver->routine) {
  case READ_ROUTINE:
    return run_read_routine(driver);
  case WRITE_ROUTINE:
    return run_write_routine(driver);
  default: ;
  }
  free_driver(driver);
  return FAIL;
}

void free_driver(filed_t *driver) {

  if (driver->file_buffer)
    free(driver->file_buffer);
  if (driver->table_client)
    free(driver->table_client);
  if (driver->table_sample)
    free(driver->table_sample);
  if (driver->file)
    fclose(driver->file);
}
//-------------------------------------------------------------------------------------------------------------------------