/*------------------------------------------------------------------------------------------------------------------MESSAGE
info info info                                                                                               
-------------------------------------------------------------------------------------------------------------------------*/

#include <string.h>
#include "../system/cstrings.h"
#include "../system/scanner.h"
#include "message.h"

static void mesg_scan(mesg_t *message) {
/*A subject and a comment being entered/created by client input/scan.*/ 
  Render_Header("COMPOSE", "Enter subject comment.");

  message->size_subj = scan_driver(message->subject, "subject", SBUFF);
  message->size_comm = scan_driver(message->comment, "comment", SBUFF);

  return;
}

static void mesg_push(mesg_t *message, reqt_t *request) {
/*Creates a Message push-request by binding all relevant data into a canonical string.*/
  System_Message("initiates message push request.");

  datetime_attach(request);

  request->size_pack = (request->size_user + request->size_datm + message->size_subj + message->size_comm + POFFS);

  request->username[request->size_user - 1] = DELIM;
  request->datetime[request->size_datm - 1] = DELIM;
  message->subject[message->size_subj - 1] = DELIM;
  message->comment[message->size_comm - 1] = DELIM;

  strncat(request->package, request->username, request->size_pack);
  strncat(request->package, request->datetime, request->size_pack);
  strncat(request->package, message->subject, request->size_pack);
  strncat(request->package, message->comment, request->size_pack);

  protocol_attach(request);

  return;
}

static void mesg_pull(reqt_t *request) {
/*Creates a Message pull-request. Only PROTOCOL (and terminator) necessary.*/
  System_Message("initializes message pull request.");

  request->size_pack = POFFS;
  protocol_attach(request);

  return;
}

void message_driver(reqt_t *request, uint8_t *state, uint16_t *error) {

  request->pack_delm = DMESG;
  mesg_t message = {.size_subj = 0};
  int32_t route = (request->protocol[EBIDX] & (1 << RWBIT)) ? MESGW : MESGR;

  switch (route) {
  case MESGR:
    mesg_pull(request);
  break;
  case MESGW:
    mesg_scan(&message);
    mesg_push(&message, request);
  break;
  default:
    *state |= (1 << ERROR); *error |= (1 << SDERR);
  }
  
  return;
}
