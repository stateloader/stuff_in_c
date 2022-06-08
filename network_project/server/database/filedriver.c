/*------------------------------------------------------------------------------------------------------------------------
                                                                                                         FILEDRIVER MODULE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/

#include <string.h>
#include "dbconfigs.h"
#include "filedriver.h"

//-----------------------------------------------------------------------------------------------read routine logic part 1

static uint8_t file_driver_file_open(filed_t *driver) {

  uint8_t result = 0;

  switch(driver->model) {
  case CLIENT:
    result = (driver->file = fopen(PATH_CLIENT, "r")) != NULL ? 1 : 0;
    break;
  case SAMPLE:
    result = (driver->file = fopen(PATH_SAMPLE, "r")) != NULL ? 1 : 0;
    break;
  default:
    result = FAIL;
  }
  return result;
}

static uint8_t file_driver_file_buff(filed_t *driver) {

  uint8_t result = (driver->file_data = calloc(FILE_BUFFER, sizeof(char))) != NULL ? SUCC : FAIL;
  return result;
}

static uint8_t file_driver_file_read(filed_t *driver) {

  driver->file_size = fread(driver->file_data, sizeof(char), FILE_BUFFER, driver->file);
  uint8_t result = (driver->file_size > 0) ? SUCC : FAIL; 
  return result;
}

static uint8_t file_driver_calc_rows(filed_t *driver) {

  uint8_t delim_interval = (driver->model == CLIENT) ? FREQ_DELIM_CLIENT : FREQ_DELIM_SAMPLE;

  for (size_t i = 0; i < driver->file_size; i++)
    driver->rows += (driver->file_data[i] == DELIM) ? 1 : 0;
  driver->rows = (driver->rows / delim_interval);
  return SUCC;
}

static uint8_t file_driver_allc_rows(filed_t *driver) {

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
    result = (driver->table_sample = malloc(sizeof(cmod_t) * driver->rows)) != NULL ? SUCC : FAIL;
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
    char byte = driver->file_data[i];

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

  size_t index = 0, row = 0;
  uint8_t state = STATE_TEMP;

  for (size_t i = 0; i < driver->file_size; i++) {
    char byte = driver->file_data[i];

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

static uint8_t file_driver_data_rows(filed_t *driver) {

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
  {"failed to open file\n", file_driver_file_open}, {"failed to create filebuffer\n", file_driver_file_buff},
  {"failed to read file\n",file_driver_file_read}, {"failed to fetch amnt rows\n", file_driver_calc_rows},
  {"failed to memalloc\n", file_driver_allc_rows}, {"failed copy data_rows\n", file_driver_data_rows}
};

static uint8_t run_read_routine(filed_t *driver) {

  for (size_t i = 0; i < 6; i++) {
    if (!filed_read_items[i].func(driver)) {
      printf("failed number %ld\n", i);
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
  default:
    free_driver(driver);
    return FAIL;
  }
  free_driver(driver);
  return FAIL;
}

void free_driver(filed_t *driver) {

  if (driver->file_data)
    free(driver->file_data);
  if (driver->table_client)
    free(driver->table_client);
  if (driver->table_sample)
    free(driver->table_sample);
  if (driver->file)
    fclose(driver->file);
}
//-------------------------------------------------------------------------------------------------------------------------