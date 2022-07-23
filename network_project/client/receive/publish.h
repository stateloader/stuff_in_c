#ifndef PUBLISH_H_
#define PUBLISH_H_

#include "../system/configs.h"
#include "receiver.h"

#define PUBL_MESG 0x81  //  Publish Message (Table).
#define PUBL_DVCE 0x82  //  Publish Device (Table).

#define MESG_FORM "Id\t\t\t%d\nUsername\t\t%s\nWritten\t\t\t%s\nSubject\t\t\t%s\nComment\t\t\t%s\n\n"
#define DVCE_FORM "Id\t\t\t%d\nUsername\t\t%s\nToggled\t\t\t%s\nColour\t\t\t%s\n\n"

void publish_driver(recv_t *receive, uint8_t *state, uint16_t *error);

#endif