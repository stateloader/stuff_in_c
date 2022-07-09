#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "../system/configs.h"
#include "requester.h"

#define MESGR 0           //Message Read
#define MESGW 1           //Message Write

typedef struct Message {
  size_t size_subj;
  size_t size_comm;
  char subject[SBUFF];
  char comment[SBUFF];
} mesg_t;


void message_driver(reqt_t *request, uint8_t *state, uint16_t *error);

#endif


  //printf("subject: %s, size: %ld\n", message->subject, message->size_subj);
  //printf("comment: %s, size: %ld\n", message->comment, message->size_comm);
  //printf("datetime: %s, size: %ld\n", request->datetime, request->size_datm);
  //printf("package: %s, size: %ld\n", request->package, request->size_pack);
  //printf("username: %s, size: %ld\n", request->username, request->size_user);
  //printf("datetime: %s, size: %ld\n", request->datetime, request->size_datm);
  //printf("subject: %s, size: %ld\n", message->subject, message->size_subj);
  //printf("comment: %s, size: %ld\n", message->comment, message->size_comm);
  //printf("package: %s, size: %ld\n", request->package, request->size_pack);
  //printf("size_pack: %ld \t size_ctrl: %ld\n", request->size_pack, size_ctrl);
