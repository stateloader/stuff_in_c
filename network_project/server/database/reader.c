/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             READER MODULE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "../serverutils/serror.h"
#include "../serverutils/sstrings.h"
#include "reader.h"

/*-----------------------------------------------------------------------------------------------read routine logic part 0
before a table being crated (...) info info info
-------------------------------------------------------------------------------------------------------------------------*/

static route_item route_items[] = {
//custom datatype for mapping specific data given (...) [vilken model, därmed databas, ärendet rör etc].
  {MCLNT, CCLNT, PCLNT},
  {MSMPL, CSMPL, PSMPL},
  {MMSGE, CMSGE, PMSGE},
  {MDVCE, CDVCE, PDVCE}
};

static void decode_request(read_t *reader) {
//setups a "route-stack" (read or write, which table etc.) by parsing a route-byte sent from the response-module.

  uint8_t check_bit = 0;
  uint8_t reqmask = reader->request;
  while (check_bit < 7) {
    if (reqmask & 0x01)
      reader->item = route_items[check_bit];
    check_bit++;
    reqmask = reqmask >> 1;
  }
}
/*-----------------------------------------------------------------------------------------------read routine logic part 1
info info info
-------------------------------------------------------------------------------------------------------------------------*/
static uint8_t open_file(read_t *reader) {
//open file.

  uint8_t result = (reader->file = fopen(reader->item.file_path, "r")) != NULL ? SUCC : FAIL;
  return result;
}

static uint8_t alloc_filebuff(read_t *reader) {
//alloc memory of size FBUFF.

  uint8_t result = (reader->file_buffer = calloc(FBUFF, sizeof(char))) != NULL ? SUCC : FAIL;
  return result;
}

static uint8_t read_filedata(read_t *reader) {
//read file-content to file_buffer. fread-func returns "actual size" of file wich beeing stored in file_size.

  reader->file_size = fread(reader->file_buffer, sizeof(char), FBUFF, reader->file);

  uint8_t result = (reader->file_size > 0) ? SUCC : FAIL;
  return result;
}

static uint8_t fetch_tablerows(read_t *reader) {
//every struct-model/entry/row (semantics really fails me on this one) has N-size of members and every member has data.
//while stored in file, every member is separated by a delimiter (pipe character '|', constant DELIM in this source-code).

//for now, my solution for fetching correct amount of entries/rows of a given model from a given source-file is to count
//delimiters and just devide it with N number of DELIM in every model/entry/row.

  for (uint32_t i = 0; i < reader->file_size; i++)
    reader->rows += (reader->file_buffer[i] == DELIM) ? 1 : 0;

  if (reader->rows % reader->item.membr != 0)
    return FAIL;
  reader->rows = (reader->rows / reader->item.membr);
  return SUCC;
}
/*-----------------------------------------------------------------------------------------------read routine logic part 2
info info info
------------------------------------------------------------------------------------------------------------------------*/
static void fetch_cmod_id(uint32_t rows, cmod_t *table) {
  for (uint32_t i = 0; i < rows; i++) {
    cmod_t rows = {.id = i};
    table[i] = rows;
  }
}

static void fetch_smod_id(uint32_t rows, smod_t *table) {
  for (uint32_t i = 0; i < rows; i++) {
    smod_t rows = {.id = i};
    table[i] = rows;
  }
}

static uint8_t alloc_tablerows(read_t *reader) {

  uint8_t result = 0;

  switch(reader->item.model) {
  case MCLNT:
    result = (reader->table_client = malloc(sizeof(cmod_t) * reader->rows)) != NULL ? SUCC : FAIL;
    if (result) fetch_cmod_id(reader->rows, reader->table_client);
    break;
  case MSMPL:
    result = (reader->table_sample = malloc(sizeof(smod_t) * reader->rows)) != NULL ? SUCC : FAIL;
    if (result) fetch_smod_id(reader->rows, reader->table_sample);
    break;
  }
  return result;
}
/*-----------------------------------------------------------------------------------------------read routine logic part 2
info info info
------------------------------------------------------------------------------------------------------------------------*/

static uint8_t create_client_table(read_t *reader) {

  uint8_t member = 0;
  uint32_t index = 0, row = 0;

  for (uint32_t i = 0; i < reader->file_size; i++) {
    char byte = reader->file_buffer[i];

    switch(member) {
    case 0:
      if (byte != DELIM) {
        reader->table_client[row].username[index] = byte;
        index++;
      } else {
        reader->table_client[row].username[index] = '\0';
        member = 1;
        index = 0;
        printf("username [ld]%s\n", reader->table_client[row].username);
      }
      break;

    case 1:
      if (byte != DELIM) {
        reader->table_client[row].password[index] = byte;
        index++;
      } else {
        reader->table_client[row].password[index] = '\0';
        member = 0;
        printf("password [ld]%s\n\n", reader->table_client[row].password);
        index = 0, row++;
      }
      break;
    default:
      reader_free(reader);
      return FAIL;
    }
  }
  return SUCC;
}

static uint8_t create_sample_table(read_t *reader) {

  uint8_t state = STEMP;
  uint32_t index = 0, row = 0;

  for (uint32_t i = 0; i < reader->file_size; i++) {
    char byte = reader->file_buffer[i];

    switch(state) {
    case STEMP:
      if (byte != DELIM) {
        reader->table_sample[row].temperature[index] = byte;
        index++;
      } else {
        reader->table_sample[row].temperature[index] = '\0';
        state = SDTME;
        index = 0;
      }
      break;
    case SDTME:
      if (byte != DELIM) {
        reader->table_sample[row].datetime[index] = byte;
        index++;
      } else {
        reader->table_sample[row].datetime[index] = '\0';
        state = STEMP;
        index = 0, row++;
      }
      break;
    default:
      reader_free(reader);
      return FAIL;
    }
  }
  return SUCC;
}

static uint8_t create_table(read_t *reader) {

  switch(reader->item.model) {
  case MCLNT:
    return create_client_table(reader);
    break;
  case MSMPL:
    return create_sample_table(reader);
    break;
  default:
    return FAIL;
  }
  return SUCC;
}

static read_item read_items[] = {
  {"failed to open file", open_file},
  {"failed to create filebuffer\n", alloc_filebuff},
  {"failed to read file",read_filedata},
  {"failed to fetch amnt rows\n", fetch_tablerows},
  {"failed to memalloc", alloc_tablerows},
  {"failed copy data_rows\n", create_table}
};

static uint8_t reader_routine(read_t *reader) {

  for (uint32_t i = 0; i < ARRAY_SIZE(read_items); i++) {
    if (!read_items[i].func(reader)) {
      System_Error_Message(read_items[i].error_message);
      return FAIL;
    }
  }
  return SUCC;
}

uint8_t database_reader(read_t *reader) {
  
  decode_request(reader);
  return reader_routine(reader);
}

void reader_free(read_t *reader) {

  if (reader->file_buffer)
    free(reader->file_buffer);
  if (reader->table_client)
    free(reader->table_client);
  if (reader->table_sample)
    free(reader->table_sample);
  if (reader->file)
    fclose(reader->file);
}
//-------------------------------------------------------------------------------------------------------------------------