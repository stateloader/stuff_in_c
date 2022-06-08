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

#define ERROR_MESSAGE_FORMAT "[action] (%s) \t [topic] (%s) \t [result] (%s)\n\n"
//-------------------------------------------------------------------------------------relative file-path to client/sample
#define PATH_CLIENT "resources/client.txt"
#define PATH_SAMPLE "resources/sample.txt"
//-------------------------------------------------------------------------------------relative file-path to client/sample
#define READ_CLIENT_ROUTINE 0
#define READ_SAMPLE_ROUTINE 1
#define WRITE_CLIENT_ROUTINE 2
#define WRITE_SAMPLE_ROUTINE 3

//#define check_bill(byte, bit) (byte &= (1 << bit))
//--------------------------------------------------------------------"frequenzy" in which (N)delimiter flags for "new row"
#define DELIM '|'
#define FREQ_DELIM_CLIENT 2
#define FREQ_DELIM_SAMPLE 4
//------------------------------------------------------------------------------------------------------------------------
#define FILE_BUFFER 4096
#define DATA_BUFFER 64
#define TIME_BUFFER 64
//---------------------------------------------------------------------interval in which (N) delimiter flags for "new row"
#define STATE_USERNAME 0
#define STATE_PASSWORD 1
#endif