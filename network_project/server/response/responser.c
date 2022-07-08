#include "reader.h"
#include "writer.h"
#include "responser.h"

static void database_reader(resp_t *response, uint16_t *state, uint16_t *error) {
  
  read_t reader = {.size_pack = response->size_recv};
  reader.protocol = response->protocol;
  reader.package = response->received;

  read_driver(&reader, state, error);

}
static void database_writer(resp_t *response, uint16_t *state, uint16_t *error) {

  write_t writer = {.size_pack = response->size_recv};
  writer.protocol = response->protocol;
  writer.package = response->received;

  write_driver(&writer, state, error);
}

void response_driver(resp_t *response, uint16_t *state, uint16_t *error) {
  System_Message("inside responser");

  int32_t route = (response->protocol[EBIDX] & (1 << RWBIT)) ? 1 : 0;

  switch (route) {
  case 0:
    database_reader(response, state, error);
    break;
  case 1:
    database_writer(response, state, error);
    break;
  default:
    *state |= (1 << ERROR); *error |= (1 << SWERR);
    break;
  }
  return;
}