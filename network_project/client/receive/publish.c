/*------------------------------------------------------------------------------------------------------------------PUBLISH
Table created being printed. For now ALL its data but I'll in time implement a menu of some sort making it possible to
examine the data based on date, name, topic etc. Guess "CRUDE" of some sort could work from here as well, making it
possiblefor clients/users to manage earlier entries before throwing the request (for change) back to the server. We'll see.                                                             
-------------------------------------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include "models.h"
#include "publish.h"

static void release_memo(mmod_t *mesg, dmod_t *dvce) {

  if (mesg) {
    System_Message("Freeing message table.");
    free(mesg); mesg = NULL;
  }
  if (dvce) {
    System_Message("Freeing device table.");
    free(dvce); dvce = NULL;
  }
}

static void publish_mesg(mmod_t *mesg, size_t rows) {
  Render_Header("RECORDS", "Messages");

  for (size_t i = 0; i < rows; i++)
    printf(MESG_FORM, mesg[i].id, mesg[i].user, mesg[i].datm, mesg[i].topc, mesg[i].mesg);
  return;
}

static void publish_dvce(dmod_t *dvce, size_t rows) {
  Render_Header("RECORDS", "Device, LED colour");

  for (size_t i = 0; i < rows; i++)
    printf(DVCE_FORM, dvce[i].id, dvce[i].user, dvce[i].datm, dvce[i].push);
  return;
}

void publish_driver(recv_t *receive, uint8_t *state, uint16_t *error) {
  
  if (receive->protocol[EBIDX] & (1 << RWBIT)) return;

  switch (receive->protocol[TBIDX]) {
  case PUBL_MESG:
    publish_mesg(receive->table_mesg, receive->amnt_rows);
  break;
  case PUBL_DVCE:
    publish_dvce(receive->table_dvce, receive->amnt_rows);
  break;
  default:
    *state |= (1 << ERROR); *error |= (1 << SDERR);
  }
  release_memo(receive->table_mesg, receive->table_dvce);
  return;
}