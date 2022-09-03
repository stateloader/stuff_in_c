/*------------------------------------------------------------------------------------------MESSAGE
Logic dealing with message requests.
-------------------------------------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include "../jackIO/cstrings.h"
#include "../jackIO/scanner.h"
#include "message.h"

static void datetime_attach(reqt_t *request) {
/*Attaches a timestamp to request-packages.*/

  strncat(request->datetime, __DATE__, TBUFF);
  strncat(request->datetime, " ", TBUFF);
  strncat(request->datetime, __TIME__, TBUFF);
  request->size_datm = string_size(SBUFF, request->datetime);

  return;
}

static void protocol_attach(reqt_t *request) {
/*Attaches the PROTOCOL (and nullterminator) to request-packages.*/

  request->package[request->size_pack - 4] = request->protocol[TINDX];
  request->package[request->size_pack - 3] = request->protocol[PINDX];
  request->package[request->size_pack - 2] = request->protocol[CINDX];
  request->package[request->size_pack - 1] = '\0';

  return;
}

static void scan_message(mesg_t *message) {
/*A subject and a comment being entered/created by user-input/scan.*/ 

  Render_Header("COMPOSE", "Enter Subject and Comment.");
  message->size_subj = scan_driver(ASCI_PLUG, SBUFF, message->subject, "subject");
  message->size_comm = scan_driver(ASCI_PLUG, SBUFF, message->comment, "comment");

  return;
}

static void push_message(mesg_t *message, reqt_t *request) {
/*Creates a Message push-request by binding all relevant data into a canonical string.*/

  datetime_attach(request);

  request->size_pack = (
    request->size_user + request->size_datm + message->size_subj + message->size_comm + POFFS
  );

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

static void pull_message(reqt_t *request) {
/*Creates a Message pull-request. Only 'protocol' (and terminator) necessary for this request.*/

  request->size_pack = POFFS;
  protocol_attach(request);
  
  return;
}

void message_driver(reqt_t *request) {

  mesg_t message = {.size_subj = 0};
  
  if ((request->protocol[CINDX] & (1 << PPREQ))) {
    scan_message(&message);
    push_message(&message, request);
  } else {
  	pull_message(request);
  }
  return;
}
