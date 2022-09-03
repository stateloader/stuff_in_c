/*-------------------------------------------------------------------------------------------PUBLISH
Publishes/Prints table created out of received data. ALL DATA. I'll probably implement a menu of
some sort later on making it possible to examine the table based on date, name, topic etc.
--------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "models.h"
#include "publish.h"

static const char *MESG_FORM = \
	"Id\t\t\t%d\nUsername\t\t%s\nWritten\t\t\t%s\nSubject\t\t\t%s\nComment\t\t\t%s\n\n";
	
static const char *DVCE_FORM = \
	"Id\t\t\t%d\nUsername\t\t%s\nToggled\t\t\t%s\nColour\t\t\t%s\n\n";

static void release_memo(mmod_t *mesg, dmod_t *dvce) {
/*Freeing allocated memory.*/
  if (mesg) free(mesg);
  if (dvce) free(dvce);
}

static void publish_mesg(mmod_t *mesg, size_t size_rows) {
/*Publish message-data.*/

  Render_Header("RECORDS", "Messages");
  for (size_t i = 0; i < size_rows; i++)
    printf(MESG_FORM, mesg[i].id, mesg[i].user, mesg[i].datm, mesg[i].topc, mesg[i].mesg);
  return;
}

static void publish_dvce(dmod_t *dvce, size_t size_rows) {
/*Publish device-data ("led-switching-history").*/

  Render_Header("RECORDS", "Device, LED colour");
  for (size_t i = 0; i < size_rows; i++)
    printf(DVCE_FORM, dvce[i].id, dvce[i].user, dvce[i].datm, dvce[i].push);
  return;
}

void publish_driver(recv_t *receive) {
/*Which table being printed is decided by the value of the TINDX-byte (Table-byte) in 'protocol'.*/
  
  switch (receive->protocol[TINDX]) {
  case 0x81:
    publish_mesg(receive->table_mesg, receive->size_rows);
  break;
  case 0x82:
    publish_dvce(receive->table_dvce, receive->size_rows);
  break;
  default:
  	release_memo(receive->table_mesg, receive->table_dvce);
		Termination_Message("table_dvce_create", "default reached in switch-statement.");
  }
	release_memo(receive->table_mesg, receive->table_dvce);
  return;
}
