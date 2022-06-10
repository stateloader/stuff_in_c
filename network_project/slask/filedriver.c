/*------------------------------------------------------------------------------------------------------------------------
                                                                                                         FILEDRIVER MODULE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/

#include <string.h>
#include "database.h"
#include "filedriver.h"

/*-----------------------------------------------------------------------------------------------read routine logic part 0
before a table being crated (...) info info info
-------------------------------------------------------------------------------------------------------------------------*/

static route_item route_items[] = {
//custom datatype for mapping specific data given (...) [vilken model, därmed databas, ärendet rör etc].
  {MCLNT, CCLNT, PCLNT},
  {MSMPL, CSMPL, PSMPL},
  {MMSGE, CMSGE, PMSGE},
};

static void decode_route(uint8_t request, filed_t *driver) {
//setups a "route-stack" (read or write, which table etc.) by parsing a route-byte sent from the response-module.

  uint8_t check_bit = 0;
  
  while (check_bit < 8) {
    if (check_bit == 7)
      driver->route = (request & 0x01) ? WINIT: RINIT;
    else if (request & 0x01)
      driver->item = route_items[check_bit];
    check_bit++;
    request = request >> 1;
  }
}
/*-----------------------------------------------------------------------------------------------read routine logic part 1
info info info
-------------------------------------------------------------------------------------------------------------------------*/
static uint8_t read_fetch_file(filed_t *driver) {
//open file.

  uint8_t result = (driver->file = fopen(driver->item.file_path, "r")) != NULL ? SUCC : FAIL;
  return result;
}

static uint8_t read_fetch_filebuff(filed_t *driver) {
//alloc memory of size FBUFF.

  uint8_t result = (driver->file_buffer = calloc(FBUFF, sizeof(char))) != NULL ? SUCC : FAIL;
  return result;
}

static uint8_t read_fetch_filedata(filed_t *driver) {
//read file-content to file_buffer. fread-func returns "actual size" of file wich beeing stored in file_size.

  driver->file_size = fread(driver->file_buffer, sizeof(char), FBUFF, driver->file);

  uint8_t result = (driver->file_size > 0) ? SUCC : FAIL;
  return result;
}

static uint8_t read_fetch_filerows(filed_t *driver) {
//every struct-model/entry/row (semantics really fails me on this one) has N-size of members and every member has data.
//while stored in file, every member is separated by a delimiter (pipe character '|', constant DELIM in this source-code).

//for now, my solution for fetching correct amount of entries/rows of a given model from a given source-file is to count
//delimiters and just devide it with N number of DELIM in every model/entry/row.

  for (size_t i = 0; i < driver->file_size; i++)
    driver->rows += (driver->file_buffer[i] == DELIM) ? 1 : 0;

  if (driver->rows % driver->item.membr != 0)
    return FAIL;
  driver->rows = (driver->rows / driver->item.membr);
  return SUCC;
}
/*-----------------------------------------------------------------------------------------------read routine logic part 2
info info info
------------------------------------------------------------------------------------------------------------------------*/
static void fetch_cmod_id(size_t rows, cmod_t *table) {
  for (size_t i = 0; i < rows; i++) {
    cmod_t rows = {.id = i};
    table[i] = rows;
  }
}

static void fetch_smod_id(size_t rows, smod_t *table) {
  for (size_t i = 0; i < rows; i++) {
    smod_t rows = {.id = i};
    table[i] = rows;
  }
}

static uint8_t read_fetch_rowmem(filed_t *driver) {

  uint8_t result = 0;

  switch(driver->model) {
  case MCLNT:
    result = (driver->table_client = malloc(sizeof(cmod_t) * driver->rows)) != NULL ? SUCC : FAIL;
    if (result) fetch_cmod_id(driver->rows, driver->table_client);
    break;
  case MSMPL:
    result = (driver->table_sample = malloc(sizeof(smod_t) * driver->rows)) != NULL ? SUCC : FAIL;
    if (result) fetch_smod_id(driver->rows, driver->table_sample);
    break;
  }
  return result;
}
/*-----------------------------------------------------------------------------------------------read routine logic part 2
info info info
------------------------------------------------------------------------------------------------------------------------*/

static uint8_t fetch_client_data(filed_t *driver) {

  uint8_t member = 0;
  size_t index = 0, row = 0;

  for (size_t i = 0; i < driver->file_size; i++) {
    char byte = driver->file_buffer[i];

    switch(member) {
    case 0:
      if (byte != DELIM) {
        driver->table_client[row].username[index] = byte;
        index++;
      } else {
        driver->table_client[row].username[index] = '\0';
        member = 1;
        index = 0;
      }
      break;

    case 1:
      if (byte != DELIM) {
        driver->table_client[row].password[index] = byte;
        index++;
      } else {
        driver->table_client[row].password[index] = '\0';
        member = 0;
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

  uint8_t state = STEMP;
  size_t index = 0, row = 0;

  for (size_t i = 0; i < driver->file_size; i++) {
    char byte = driver->file_buffer[i];

    switch(state) {
    case STEMP:
      if (byte != DELIM) {
        driver->table_sample[row].temperature[index] = byte;
        index++;
      } else {
        driver->table_sample[row].temperature[index] = '\0';
        state = SDTME;
        index = 0;
      }
      break;
    case SDTME:
      if (byte != DELIM) {
        driver->table_sample[row].datetime[index] = byte;
        index++;
      } else {
        driver->table_sample[row].datetime[index] = '\0';
        state = STEMP;
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

static uint8_t read_fetch_rowdata(filed_t *driver) {

  switch(driver->model) {
  case MCLNT:
    return fetch_client_data(driver);
    break;
  case MSMPL:
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
  {"failed to memalloc\n", read_fetch_rowmem}, {"failed copy data_rows\n", read_fetch_rowdata}
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
//-----------------------------------------------------------------------------------------------------write routine logic
static uint8_t run_write_routine(filed_t *driver) {
  printf("write routine test\n");
  return SUCC;
}

//-----------------------------------------------------------------------------------------------------write routine logic
//------------------------------------------------------------------------------------------------------------------------

uint8_t file_driver(uint8_t request, filed_t *driver) {
  
  decode_route(request, driver);

  switch(driver->route) {
  case RINIT:
    return run_read_routine(driver);
    break;
  case WINIT:
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