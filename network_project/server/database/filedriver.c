/*------------------------------------------------------------------------------------------------------------------------
                                                                                                         FILEDRIVER MODULE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/

#include "dbconfigs.h"
#include "filedriver.h"
//---------------------------------------------------------------------------------------------------------read file logic

static void Error_Message(const char *action, const char *result, const char *note) {
  printf(ERROR_MESSAGE_FORMAT, action, result, note);
}

static uint8_t file_driver_file_open(filed_t *driver, const char *file_path) {
  
  driver->file = fopen(file_path, "r");

  uint8_t result = (driver->file != NULL) ? SUCC : FAIL;
  if (!result) Error_Message("open file", "FAILURE", file_path);
  return result;
}

static uint8_t file_driver_file_buff(filed_t *driver) {

  driver->file_data = calloc(FILE_BUFFER, sizeof(char));

  uint8_t result = (driver->file_data != NULL) ? SUCC : FAIL;
  if (!result) Error_Message("calloc memory", "FAILURE", "check FILE_BUFFER macro");
  return result;
}

static uint8_t file_driver_file_read(filed_t *driver) {

  driver->file_size = fread(driver->file_data, sizeof(char), FILE_BUFFER, driver->file);

  uint8_t result = (driver->file_size > 0) ? 1 : 0; 
  if (!result) Error_Message("fread data", "FAILURE", "check FILE_BUFFER macro");
  return result;
}

static uint8_t file_driver_calc_rows(filed_t *driver, uint8_t delim_interval) {

  for (size_t i = 0; i < driver->file_size; i++)
    driver->rows += (driver->file_data[i] == DELIM) ? 1 : 0;
  driver->rows = (driver->rows / delim_interval);

  uint8_t result = ((driver->rows % delim_interval == 0) ? SUCC : FAIL);
  if (!result) Error_Message("calc rows", "FAILURE", "N/A");
  
  return result;
}

static uint8_t file_driver_allc_rows(filed_t *driver) {

  driver->table_client = malloc(sizeof(cmod_t) * driver->rows);

  uint8_t result = (driver->table_client != NULL) ? 1 : 0;
  if (!result) {Error_Message("calc rows", "FAILURE", "N/A");
    return result;
  } for (size_t i = 0; i < driver->rows; i++) {
    cmod_t rows = {.id = i};
    driver->table_client[i] = rows;
  }
  return result;
}

static uint8_t file_driver_data_rows(filed_t *driver) {

  char byte = ' ';
  uint8_t state = STATE_USERNAME;
  size_t memidx = 0, modrow = 0;

  for (size_t i = 0; i < driver->file_size; i++) {
    byte = driver->file_data[i];

    switch(state) {
    case 0:
      if (byte != DELIM) {
        driver->table_client[modrow].username[memidx] = byte;
        memidx++;
      } else {
        driver->table_client[modrow].username[memidx] = '\0';
        state = STATE_PASSWORD;
        memidx = 0;
      }
      break;

    case 1:
      if (byte != DELIM) {
        driver->table_client[modrow].password[memidx] = byte;
        memidx++;
      } else {
        driver->table_client[modrow].password[memidx] = '\0';
        state = STATE_USERNAME;
        memidx = 0, modrow++;
      }
      break;
    default:
      printf("something went south during read-routine. terminating.\n");
      free_driver(driver);
      return FAIL;
    }
  }
  return SUCC;
}

//------------------------------------------------------------------------------------------------------------------------

uint8_t file_driver(filed_t *driver) {
  
  switch(driver->bill) {

  case READ_CLIENT_ROUTINE:
    printf("res %d\n", file_driver_file_open(driver, PATH_CLIENT));
    printf("res %d\n", file_driver_file_buff(driver));
    printf("res %d\n", file_driver_file_read(driver));
    printf("res %d\n", file_driver_calc_rows(driver, FREQ_DELIM_CLIENT));
    printf("res %d\n", file_driver_allc_rows(driver));
    printf("res %d\n", file_driver_data_rows(driver));
    break;
  default:
    printf("not added more yet");
  }
  return SUCC;
}

void free_driver(filed_t *driver) {
  free(driver->file_data); 
  free(driver->table_client);
}
//-------------------------------------------------------------------------------------------------------------------------