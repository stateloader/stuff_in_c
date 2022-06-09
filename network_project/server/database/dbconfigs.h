/*------------------------------------------------------------------------------------------------------------------------
                                                                                                           DBCONFIG HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef DBCONFIGS_H_
#define DBCONFIGS_H_

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

#define SUCC 1
#define FAIL 0
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define ERROR_MESSAGE_FORMAT "[action] (%s) \t [topic] (%s) \t [result] (%s)\n\n"
//-------------------------------------------------------------------------------------------------------------dbresources
#define PATH_CLIENT "resources/client.txt"
#define PATH_SAMPLE "resources/sample.txt"
//-------------------------------------------------------------------------------------------------------------explanation
#define READ_ROUTINE 0
#define WRITE_ROUTINE 1
//-------------------------------------------------------------------------------------------------------------explanation
#define CLIENT 0
#define SAMPLE 1
//-------------------------------------------------------------------------------------------------------------explanation
#define DELIM '|'
#define DMNUM_CLIENT 2
#define DMNUM_SAMPLE 2
#define DMNUM_MESSAGE 4
//------------------------------------------------------------------------------------------------------------------------
#define FILE_BUFFER 4096
#define MESG_BUFFER 512
#define DATA_BUFFER 64
#define TIME_BUFFER 24
//-------------------------------------------------------------------------------------------------------------explanation
#define STATE_USER 0
#define STATE_PASS 1

#define STATE_TEMP 0
#define STATE_DTME 1

#endif