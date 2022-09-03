#ifndef SCANNER__H_
#define SCANNER__H_

#include <stddef.h>
#include <stdint.h>

#ifndef MIN_SIZE_LIMIT
#define MIN_SIZE_LIMIT 2
#endif

#define SIZE_ARRAY(arry) (sizeof(arry)/sizeof(arry[0]))

//--------------------------Conditional macros used within various check-functions in the source file

#define MINS_CHECK(size) (size < MIN_SIZE_LIMIT)

#define ASCI_CHECK(byte) (byte >= 0x00 && byte <= 0x7F)
#define INTG_CHECK(byte) (byte >= '0' && byte <= '9')

#define PERD_CHECK(byte) (byte == '.')
#define COLN_CHECK(byte) (byte == ':')

#define DECM_CHECK(byte) (INTG_CHECK(byte) || PERD_CHECK(byte))

#define IPV4_RANGE(size) (size >= 8 && size <= 16)
#define IPV4_CHECK(byte) (INTG_CHECK(byte) || PERD_CHECK(byte))

#define IPV6_CHECK(byte) (INTG_CHECK(byte) || COLN_CHECK(byte))

#define TERM_CHECK(byte) (byte == '\0')
#define SPAN_CHECK(plug, last) (plug >= 0 && plug < last)

//----------------------------Some check-functions using additional logic governed by these constants

#define ONLY_DELM 0 // upcoming byte (if loop not finished) must be a delim. 
#define ONLY_INTG 1 // upcoming byte (if loop not finished) must be a delim.
#define THIS_CONF 2 // upcoming byte expected to be either integer or (allowed) delimiter.

//-----------------------------------------------------------------------------------Plugin-constants

#define ASCI_PLUG 0 // ascii input plugin;    nothing except characters within ASCII-table allowed.
#define INTG_PLUG 1 // integer input plugin;  nothing except 0 - 9 allowed.
#define DECM_PLUG 3	// decimal input plugin;  nothing except 0 - 9 and (one) period allowed.
#define IPV4_PLUG 4 // IPv4 input plugin;     nothing except proper IPv4 format allowed.

typedef struct scanner {
  uint8_t state;
  uint8_t plugin;
  size_t size_buff;
  size_t size_scan;
  char *scan_buff;
} scan_t;

typedef struct FormatCheck {
  uint8_t plugin;
  size_t size_data;
  char *data_buff;
} formc_t;

typedef struct FormatGuard {
	uint8_t state;
	uint8_t intg_count;
	uint8_t delm_count;
	char byte;
} guard_t;

size_t scan_driver(uint8_t plugin, size_t size_buff, char *read_buff, char *message);

#endif
