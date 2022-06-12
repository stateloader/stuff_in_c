#include "../serverutils/serror.h"
#include "../serverutils/sstring.h"
#include "dbconfig.h"
#include "database.h"

static uint8_t database_decode_route(uint8_t request) {

  uint8_t rwmask = request;
  uint8_t route = rwmask & (WINIT << 7) ? WINIT : RINIT;
  return route;
}

uint8_t database_driver(read_t *reader, write_t *writer, uint8_t request, const char *package) {

  uint8_t result = 0;
  uint8_t route = database_decode_route(request);

  switch(route) {
    
  case RINIT:
    System_Info_Message("initializing read path");
    reader->request = request;
    result = database_reader(reader);
    break;

  case WINIT:
    result = string_copy(&writer->package_size, writer->package, package);
    if (!result) {
      System_Info_Message("failed to copy package before writing.");
      break;
    } else {
      System_Info_Message("initializing write path");
      writer->request = request;
      result = database_writer(writer);
      break;
    }
  default:
    System_Info_Message("reached default in route-switch.\n");
    result = FAIL;
  }
  return result;
}