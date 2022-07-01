#include <string.h>
#include "sstring.h"
#include "socket.h"
#include "response.h"

/*-----------------------------------------------------------------------------------------------------SERVER SESSION BYTE
BIT(N)                              |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
CONSTANT                            |  ALIVE  |         |    -    |    -    |  DSUCC  |   DWRTE  |   DREAD   |   ACCCL  | 
------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------TABLE BYTE
BIT(N)                              |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
CONSTANT                            |  UNBIT  |    -    |    -    |    -    |    -    |     -    |   TDVCE   |   TMESG   |
------------------------------------------------------------------------------------------------------------ATTRIBUTE BYTE
BIT(N)                              |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
CONSTANT                            |  UNBIT  |  RWBIT  |  ATTR5  |  ATTR4  |  ATTR3  |   ATTR2  |   ATTR1   |   ATTR0   |
-------------------------------------------------------------------------------------------------------------- STATUS BYTE
                                    |  UNBIT  |  VALID  |  SETUP  |  LOGIN  |    -    |     -    |     -     |     -     |
------------------------------------------------------------------------------------------------------------------------*/


static void server_reset(server_t *server) {
  buffer_flush(server->pack, SBUFF);
  buffer_flush(server->resp, SBUFF);
}

/*

static int8_t response_ACCCL(server_t *server) {

  server->size_resp = POFFS;
  server->resp[0] = server->protocol[TBYTE];
  server->resp[1] = server->protocol[ABYTE];
  server->resp[2] = server->protocol[SBYTE];
  server->resp[3] = '\0';

  if (!check_term(server->resp, server->size_resp))
    return FAIL;
  return SUCC;
}

static int8_t response_DWRTE(server_t *server) {

  server->size_resp = POFFS;
  server->resp[0] = server->protocol[TBYTE];
  server->resp[1] = server->protocol[ABYTE];
  server->resp[2] = server->protocol[SBYTE];
  server->resp[3] = '\0';

  if (!check_term(server->resp, server->size_resp))
    return FAIL;
  return SUCC;
}

static int8_t response_DREAD(server_t *server) {
  return SUCC;
}

static resp_item resp_items[] = {
  {ACCCL, response_ACCCL},
  {DWRTE, response_DWRTE},
  {DREAD, response_DREAD},
}

static int8_t response_create(server_t *server) {
  Message_Info("inside response create");

  for(size_t i = 0; i < ARRAY_SIZE(resp_items); i++) {
    if (server->session & (1 << resp_items[i].byte))
      return resp_items[i].func(server); 
  }

  return FAIL;
}
*/
int8_t response_driver(server_t *server, int8_t control) {
  
  uint32_t size_send = send(server->conn.sock_clnt, server->resp, server->size_resp, 0);

  server_reset(server);

  return response_driver_check(size_send, server->size_resp);
}
  


  /*
typedef struct ACCCL_item {
  const uint8_t flag_valid;
  const uint8_t flag_resut;
  const char *response;
} acccl_item;

static ACCCL_item acccl_items[] = {
  SETUP, , ""
}
*/