/*------------------------------------------------------------------------------------------------------------------PUBLISH
Publishes/Prints table created out of received data. For now ALL data. I'll probably implement a menu of some sort making
it possible to examine the table based on date, name, topic etc.                                                         
-------------------------------------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include "models.h"
#include "publish.h"

static void release_memo(mmod_t *mesg, dmod_t *dvce) {
/*Free memory.*/

  if (mesg) {
    System_Message("freeing message table.");
    free(mesg); mesg = NULL;
  }
  if (dvce) {
    System_Message("freeing device table.");
    free(dvce); dvce = NULL;
  }
}

static void publish_mesg(mmod_t *mesg, size_t rows) {
/*Publish message-data.*/
  Render_Header("RECORDS", "Messages");

  for (size_t i = 0; i < rows; i++)
    printf(MESG_FORM, mesg[i].id, mesg[i].user, mesg[i].datm, mesg[i].topc, mesg[i].mesg);
  return;
}

static void publish_dvce(dmod_t *dvce, size_t rows) {
/*Publish device-data (for now "led-history").*/
  Render_Header("RECORDS", "Device, LED colour");

  for (size_t i = 0; i < rows; i++)
    printf(DVCE_FORM, dvce[i].id, dvce[i].user, dvce[i].datm, dvce[i].push);
  return;
}

void publish_driver(recv_t *receive, uint8_t *state, uint16_t *error) {
/*Examines if read-request. If so, switch tatement checks which table to print in PROTOCOL.*/
  
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