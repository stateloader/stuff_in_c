/*----------------------------------------------------------------------------------------------------------------RESPONSE
                                                                                                            
------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include "sstring.h"
#include "socket.h"
#include "response.h"

const char *WRITER_MESG = "\nServer - message successfully delivered\n";
const char *WRITER_DVCE = "\nServer - ledcolour successfully changed\n";
const char *PACKAGEWOOT = "\nServer Error - and it's undefined\n";

static const uint8_t LAST_RESORT[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x00};

static resp_item error_resp[] = {
  {WPROB, SMESG, "\nServer Error - failed to write deliver message\n"},
  {WPROB, SDVCE, "\nServer Error - failed to interacting with the device\n"},
  {WPROB, EMPTY, "\nServer Error - total farse (writer)\n"},
  {RPROB, SMESG, "\nServer Error - failed to read messages from database\n"},
  {RPROB, SDVCE, "\nServer Error - failed to read device records\n"},
  {RPROB, EMPTY, "\nServer Error - total farse (reader)\n"}
};

void lethal_response(server_t *server) {

  int8_t match = 0;
  buffer_flush(server->resp, FBUFF);

  for (size_t i = 0; i < ARRAY_SIZE(error_resp); i++) {
    if ((server->session & (1 << error_resp[i].flag1)) && \
       ((server->session & (1 << error_resp[i].flag2))))
    {
      server->size_resp = string_copy(server->resp, error_resp[i].response, SBUFF);
      match += 1;
    }
  } if (!match)
    server->size_resp = string_copy(server->resp, PACKAGEWOOT, SBUFF);
  server->resp[server->size_resp - 1] = '\0';

  server->protocol[SBYTE] &= ~(1 << VALID);
  return;
}

void writer_response(server_t *server) {

  buffer_flush(server->resp, FBUFF);

  if (server->protocol[TBYTE] & (1 << TMESG))
    server->size_resp = string_copy(server->resp, WRITER_MESG, SBUFF);
  else if (server->protocol[TBYTE] & (1 << TDVCE))
    server->size_resp = string_copy(server->resp, WRITER_DVCE, SBUFF);
  else
    server->size_resp = string_copy(server->resp, PACKAGEWOOT, SBUFF);
  server->resp[server->size_resp - 1] = '\0';

  server->protocol[SBYTE] |= (1 << VALID);
  return;
}

int8_t response_driver(server_t *server, int8_t control) {
  System_Message("Responding client");

  if (control < SUCC)
    lethal_response(server);
  else if (server->protocol[ABYTE] & (1 << RWBIT))
    writer_response(server);
  else
    server->protocol[SBYTE] |= (1 << VALID);
  
  server->size_resp += POFFS;
  
  int8_t result = protocol_append(server->resp, server->size_resp, server->protocol);
  if (result != SUCC)
    send(server->conn.sock_clnt, LAST_RESORT, 5, 0);
  else
    send(server->conn.sock_clnt, server->resp, server->size_resp, 0);

  return result;
}