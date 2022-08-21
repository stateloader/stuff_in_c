/*-----------------------------------------------------------------------------------------Cstrings
My own little attempts in making some basic string-handeling functionality.
-------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include "cstrings.h"

typedef struct StringError {
	const uint8_t error_code;
	const char *func;
	const char *mesg;
} serr_item;

static const uint8_t BUFF_SIZE = 0; // BUFF_ERROR
static const uint8_t FROM_SIZE = 1; // FROM_ERROR
static const uint8_t DIFF_SIZE = 2; // DIFF_ERROR
static const uint8_t FAIL_TERM = 3;	// TERM_ERROR

static uint8_t error_check(uint8_t state, serr_item *items, size_t array_size) {
/*If state equals 0 (no errors) return 1. Else loop and print error(s), return 0.*/

  if (state == 0) return 1;  
  for (size_t i = 0; i < array_size; i++) {
  	if (state & (1 << items[i].error_code))
  	  CST_Error_Mesg(items[i].func, items[i].mesg);
  }
	return 0;
}

void buffer_flush(char *buffer, size_t size_buff) {
/*Flushes given buffer.*/

  for (size_t i = 0; i < size_buff; i++)
    buffer[i] = '\0';
  return;
}

size_t string_size(const char *string, size_t size_buff)  {
/*Returns 0 if terminator isn't found within the boundaries of 'size_buff'.*/

	for (size_t i = 0; i < size_buff; i++) {
    if (string[i] == '\0')
      return i + 1;
  }
  return 0;
}

static serr_item serr_copy[] = {

	{BUFF_SIZE, "string_copy", "copy-buffer too small."},
	{FROM_SIZE, "string_copy", "original string doesn't contain any data."},
	{DIFF_SIZE, "string_copy", "copy and original string are of different sizes."},
	{FAIL_TERM, "string_copy", "copy isn't null-terminated."},
};

size_t string_copy(char *copy, size_t size_buff, const char *from) {									// copy_buff
/*Copies string 'from' to 'copy'. Returns 'size_dest' or 0 if an error(s) accurs.*/
  
	uint8_t copy_check = 0x00;
  
  size_t size_from = string_size(from, CST_MAX_BUFF);

//'pre-copy' checks. 
	copy_check |= (size_from >= size_buff) ? (1 << BUFF_SIZE) : (0 << BUFF_SIZE);
	copy_check |= (size_from < 1) ? (1 << FROM_SIZE) : (0 << FROM_SIZE);
	if (!error_check(copy_check, serr_copy, array_size(serr_copy)))
	  return 0;

  size_t size_copy = 0;
  
	for (size_copy = 0; size_copy < size_from; size_copy++)
		copy[size_copy] = from[size_copy];

//'post-copy' checks.
	copy_check |= (size_from != size_copy) ? (1 << DIFF_SIZE) : (0 << DIFF_SIZE);
	copy_check |= (copy[size_copy - 1] != '\0') ? (1 << FAIL_TERM) : (0 << FAIL_TERM);
	if (!error_check(copy_check, serr_copy, array_size(serr_copy)))
	  return 0;

  return size_copy;
}

static serr_item serr_ccat[] = {

	{BUFF_SIZE, "string_ccat", "ccat-buffer too small for concatinating given strings."},
	{FROM_SIZE, "string_ccat", "string to merge doesn't contain any data."},
	{DIFF_SIZE, "string_ccat", "expected size on merged string is wrong."},
	{FAIL_TERM, "string_ccat", "merged string isn't null-terminated."},
};


size_t string_ccat(char *dest, size_t size_buff, const char *from) {
/*Merges 'from' to 'dest'. First byte in 'from' overwrites nullterminator in 'dest'.*/

  uint8_t ccat_check = 0x00;

  size_t size_from = string_size(from, CST_MAX_BUFF);
  size_t size_dest = string_size(dest, CST_MAX_BUFF);
  size_t size_totl = (size_from + size_dest) - 1;
  
//'pre-ccat' checks. 
	ccat_check |= (size_from < 1) ? (1 << FROM_SIZE) : (0 << FROM_SIZE);
	ccat_check |= (size_totl >= size_buff) ? (1 << BUFF_SIZE) : (0 << BUFF_SIZE);
	if (!error_check(ccat_check, serr_ccat, array_size(serr_ccat)))
	  return 0;

  size_t size_last = 0;
  size_t size_ccat = 0;

  for (size_last = size_dest - 1, size_ccat = 0; size_last < size_totl; size_last++, size_ccat++) {
  	dest[size_last] = from[size_ccat];
  }
  
//'post-ccat' checks.   
  ccat_check |= (size_last != size_totl) ? (1 << DIFF_SIZE) : (0 << DIFF_SIZE);
	ccat_check |= (dest[size_last - 1] != '\0') ? (1 << FAIL_TERM) : (0 << FAIL_TERM);
	if (!error_check(ccat_check, serr_ccat, array_size(serr_ccat)))
	  return 0;

	return size_last;
}

size_t string_mcat(char *dest, size_t size_buff, const char **from) {
/*Concatenates strings stored in 'from'-matrix to 'dest'.*/

  size_t size_mcat = 0;
  size_t size_this = 0;
   
  for (size_t i = 0; i < 4; i++) {
  	size_this = string_ccat(dest, size_buff, from[i]);
  	if (size_this < 1) return 0;
  	else size_mcat += size_this;
  }
  return size_mcat;
}

static serr_item serr_heap[] = {

	{BUFF_SIZE, "string_heap", "failed to allocate memory."},
	{FROM_SIZE, "string_heap", "original string doesn't contain any data."},
	{DIFF_SIZE, "string_heap", "heap and original string are of different sizes."},
	{FAIL_TERM, "string_heap", "heap-string isn't null-terminated."},
	
};

static void string_free(char *string) {
  if (string) free(string);
  string = NULL; return;
}

char *string_heap(const char *from, size_t *size_heap) {
/*Throws/copies given string on the heap and returns its pointer and *size.*/
  
  uint8_t heap_check = 0x00;  
  
  size_t size_from = string_size(from, CST_MAX_BUFF);
  char *heap = calloc(size_from, sizeof(char));

  heap_check |= (size_from < 1) ? (1 << FROM_SIZE) : (0 << FROM_SIZE);
	heap_check |= (heap == NULL) ? (1 << BUFF_SIZE) : (0 << BUFF_SIZE);
	if (!error_check(heap_check, serr_heap, array_size(serr_heap))) {
	  string_free(heap); return NULL;
  }
  
  *size_heap = string_copy(heap, size_from + 1, from);
   
  heap_check |= (*size_heap != size_from) ? (1 << DIFF_SIZE) : (0 << DIFF_SIZE);
	heap_check |= (heap[*size_heap - 1] != '\0') ? (1 << FAIL_TERM) : (0 << FAIL_TERM);
  if (!error_check(heap_check, serr_heap, array_size(serr_heap))) {
	  string_free(heap); return NULL;
  }
  return heap; 
}

int8_t string_comp(const char *str1, const char *str2, size_t comp_size) {
/*Compares two strings by increment 'equal' for every equal byte between str1, str2.*/

  size_t equal = 0;
  
  for (size_t i = 0; i < comp_size; i++)
    equal += (str1[i] == str2[i]) ? 1 : 0;
  if (equal == comp_size)
  	return 1; 
  return 0;
}

/*---------------------------------------------------------------------------------------"Screener"
Something that was born on the fly while playing around with the string-funcs above. Prints every
string fed into 'string_screen' in a quite detailed manner utilizing the ascii-table-struct-thingie
below. 
-------------------------------------------------------------------------------------------------*/
typedef struct AsciiTable {
	const int8_t lookup_hex;
	const int8_t lookup_dec;
	const int8_t lookup_oct;
	const int8_t lookup_bin;
	const char *display_hex;
	const char *display_dec;
	const char *display_oct;
	const char *display_bin;
	const char *display_chr;
	const char *display_key;
} ascii_table;

static ascii_table table[] = {
/*Just handy (ASCII) items to print while experimenting with strings.*/

	{ 0x00, 0,  	000, 	0b00000000, "0x00", "0",		"000", "0000 0000",	"NUL",	"Null" },
	{ 0x01, 1,  	001, 	0b00000001, "0x01", "1",		"001", "0000 0001",	"SOH",	"Start of Heading" },
	{ 0x02, 2,  	002, 	0b00000010, "0x02", "2",		"002", "0000 0010",	"STX",	"Start of Text" },
	{ 0x03, 3,  	003, 	0b00000011, "0x03", "3",		"003", "0000 0011",	"ETX",	"End of Text" },
	{ 0x04, 4,  	004, 	0b00000100, "0x04", "4",		"004", "0000 0100",	"EOT",	"End of Transmission" },
	{ 0x05, 5,  	005, 	0b00000101, "0x05", "5",		"005", "0000 0101",	"ENQ",	"Enquiry" },
	{ 0x06, 6,  	006,  0b00000110, "0x06", "6",		"006", "0000 0110",	"ACK",	"Acknowledge" },
	{ 0x07, 7,  	007, 	0b00000111, "0x07", "7",		"007", "0000 0111",	"BEL",	"Bell" },
	{ 0x08, 8,  	010, 	0b00001000, "0x08", "8",		"010", "0000 1000",	"BS",		"Backspace" },
	{ 0x09, 9,  	011, 	0b00001001, "0x09", "9",		"011", "0000 1001",	"HT",		"Horizontal Tab" },
	{ 0x0A, 10, 	012, 	0b00001010, "0x0A", "10", 	"012", "0000 1010",	"LF",		"NL Line Feed, New Line" },
	{ 0x0B, 11, 	013, 	0b00001011, "0x0B", "11", 	"013", "0000 1011",	"VT",		"Vertical Tab" },
	{ 0x0C, 12, 	014, 	0b00001100, "0x0C", "12", 	"014", "0000 1100",	"FF",		"NP Form Feed, New Page" },
	{ 0x0D, 13, 	015, 	0b00001101, "0x0D", "13", 	"015", "0000 1101",	"CR",		"Carrige Return" },
	{ 0x0E, 14, 	016, 	0b00001110, "0x0E", "14", 	"016", "0000 1110",	"SO",		"Shift Out" },
	{ 0x0F, 15, 	017, 	0b00001111, "0x0F", "15", 	"017", "0000 1000",	"SI",		"Shift In" },
	{	0x10,	16,		020, 	0b00010000, "0x10", "16", 	"020", "0001 0000",	"DLE",	"Data Link Escape" },
	{	0x11,	17,		021,  0b00010001, "0x11", "17", 	"021", "0001 0001",	"DC1",	"Device Control 1" },
	{	0x12,	18,		022, 	0b00010010, "0x12", "18", 	"022", "0001 0010",	"DC2",	"Device Control 2" },
	{	0x13,	19,		023, 	0b00010011, "0x13", "19", 	"023", "0001 0011",	"DC3",	"Device Control 3" },
	{	0x14,	20,		024, 	0b00010100, "0x14", "20", 	"024", "0001 0100",	"DC4",	"Device Control 4" },
	{ 0x15,	21,		025, 	0b00010101, "0x15", "21", 	"025", "0001 0101",	"NAK",	"Negative Acknowledge" },
	{ 0x16,	22,		026, 	0b00010110, "0x16", "22", 	"026", "0001 0110",	"SYN",	"Synchronous Idle" },
	{ 0x17,	23,		027, 	0b00010111, "0x17", "23", 	"027", "0001 0111",	"ETB",	"End of Transmission Block" },
	{ 0x18,	24,		030, 	0b00011000, "0x18", "24", 	"030", "0001 1000",	"CAN",	"Cancel" },
	{ 0x19,	25,		031, 	0b00011001, "0x19", "25", 	"031", "0001 1001",	"EM",		"End of Medium" },
	{ 0x1A,	26,		032, 	0b00011010, "0x1A", "26", 	"032", "0001 1010",	"SUB",	"Substitute" },
	{ 0x1b, 27,		033, 	0b00011011, "0x1B", "27", 	"033", "0001 1011",	"ESC",	"Escape" },
	{ 0x1C, 28,		034, 	0b00011100, "0x1C", "28", 	"034", "0001 1100",	"FS",		"File Separator" },
	{ 0x1D, 29,		035, 	0b00011101, "0x1D", "29", 	"035", "0001 1101",	"GS",		"Group Separator" },
	{ 0x1E, 30,		036, 	0b00011110, "0x1E", "30", 	"036", "0001 1110",	"RS",		"Record Separator" },
	{ 0x1F, 31,		037, 	0b00011111, "0x1F", "31", 	"037", "0001 1111",	"US",		"Unit Separator" },
	{ 0x20, 32,		040, 	0b00100000, "0x20", "32", 	"040", "0010 0000",	" ",		"Space" },
	{ 0x21, 33, 	041,	0b00100001,	"0x21", "33", 	"041", "0010 0001",	"!",		"Exclamation Mark" },
	{ 0x22, 34,		042,	0b00100010,	"0x22", "34", 	"042", "0010 0010",	"\"\"",	"Double Quote" },
	{ 0x23, 35,		043,	0b00100011,	"0x23", "35", 	"043", "0010 0011",	"#",		"Hash or Number" },
	{ 0x24, 36,		044,	0b00100100,	"0x24", "36", 	"044", "0010 0100",	"$",		"Dollar Sign" },
	{ 0x25, 37,		045,	0b00100101,	"0x25", "37", 	"045", "0010 0101",	"%",		"Percentage" },
	{ 0x26, 38,		046,	0b00100110,	"0x26", "38", 	"046", "0010 0110",	"&",		"Ampersand" },
	{ 0x27, 39,		047,	0b00100111,	"0x27", "39", 	"047", "0010 0111",	"'",		"Single Quote" },
	{ 0x28, 40,		050,	0b00101000,	"0x28", "40", 	"050", "0010 1000",	"(",		"Left Parenthesis" },
	{ 0x29, 41,		051,	0b00101001,	"0x29", "41", 	"051", "0010 1001",	")",		"Right Parenthesis" },
	{ 0x2A, 42, 	052,	0b00101010,	"0x2A", "42", 	"052", "0010 1010",	"*",		"Asterisk" },
	{ 0x2B, 43, 	053,	0b00101011,	"0x2B", "43", 	"053", "0010 1011",	"+",		"Plus Sign" },
	{ 0x2C, 44,		054,	0b00101100,	"0x2C", "44", 	"054", "0010 1100",	";", 		"Comma" },
	{ 0x2D, 45,		055,	0b00101101,	"0x2D", "45", 	"055", "0010 1101",	"-",		"Minus Sign" },
	{ 0x2E, 46,		056,	0b00101110,	"0x2E", "46", 	"056", "0010 1110",	".",		"Period" },
	{ 0x2F, 47,	  057,	0b00101111,	"0x2F", "47", 	"057", "0010 1111",	"/",		"Slash" },
	{ 0x30, 48,	  060,	0b00110000,	"0x30", "48", 	"060", "0011 0000",	"0",		"Zero" },
	{ 0x31, 49,	  061,	0b00110001,	"0x31", "49", 	"061", "0011 0001",	"1",		"Number One" },
	{ 0x32, 50,	  062,	0b00110010,	"0x32", "50", 	"062", "0011 0010",	"2",		"Number Two" },
	{ 0x33, 51,	  063,	0b00110011,	"0x33", "51", 	"063", "0011 0011",	"3",		"Number Three" },
	{ 0x34, 52,	  064,	0b00110100,	"0x34", "52", 	"064", "0011 0100",	"4",		"Number Four" },
	{ 0x35, 53,	  065,	0b00110101,	"0x35", "53", 	"065", "0011 0101",	"5",		"Number Five" },
	{ 0x36, 54,	  066,	0b00110110,	"0x36", "54", 	"066", "0011 0110",	"6",		"Number Six" },
	{ 0x37, 55,	  067,	0b00110111,	"0x37", "55", 	"067", "0011 0111",	"7",		"Number Seven" },
	{ 0x38, 56,	  070,	0b00111000,	"0x38", "56", 	"070", "0011 1000",	"8",		"Number Eight" },
	{ 0x39, 57,	  071,	0b00111001,	"0x39", "57", 	"071", "0011 1001",	"9",		"Number Nine" },
	{ 0x3A, 58,	  072,	0b00111010, "0x3A", "58", 	"072", "0011 1010",	":",		"Colon" },
	{ 0x3B, 59,	  073,	0b00111011,	"0x3B", "59", 	"073", "0011 1011",	";",		"Semicolon" },
	{ 0x3C, 60,	  074,	0b00111100,	"0x3C", "60", 	"074", "0011 1100",	"<",		"Less Than" },
	{ 0x3D, 61,	  075,	0b00111101,	"0x3D", "61", 	"075", "0011 1101",	"=",		"Equals Sign" },
	{ 0x3E, 62,   076,  0b00111110,	"0x3E", "62", 	"076", "0011 1110",	">",		"Greater Than" },
	{ 0x3F, 63,	  077,	0b00111111,	"0x3F", "63", 	"077", "0011 1111",	"?",		"Question Mark" },
	{ 0x40, 64,	  100,	0b01000000,	"0x40", "64", 	"100", "0100 0000",	"@",		"At Sign" },
	{ 0x41, 65,	  101,	0b01000001,	"0x41", "65", 	"101", "0100 0001",	"A",		"Upper Case Letter A" },
	{ 0x42, 66,	  102,	0b01000010,	"0x42", "66", 	"102", "0100 0010",	"B",		"Upper Case Letter B" },
	{ 0x43, 67,	  103,	0b01000011,	"0x43", "67", 	"103", "0100 0011",	"C",		"Upper Case Letter C" },
	{ 0x44, 68,	  104,	0b01000100,	"0x44", "68", 	"104", "0100 0100",	"D",		"Upper Case Letter D" },
	{ 0x45, 69,	  105,	0b01000101,	"0x45", "69", 	"105", "0100 0101",	"E",		"Upper Case Letter E" },
	{ 0x46, 70,	  106,	0b01000110,	"0x46", "70", 	"106", "0100 0110",	"F",		"Upper Case Letter F" },
	{ 0x47, 71,	  107,	0b01000111,	"0x47", "71", 	"107", "0100 0111",	"G",		"Upper Case Letter G" },
	{ 0x48, 72,	  110,	0b01001000,	"0x48", "72", 	"110", "0100 1000",	"H",		"Upper Case Letter H" },
	{ 0x49, 73,	  111,	0b01001001,	"0x49", "73", 	"111", "0100 1001",	"I",		"Upper Case Letter I" },
	{ 0x4A, 74,	  112,	0b01001010,	"0x4A", "74", 	"112", "0100 1010",	"J",		"Upper Case Letter J" },
	{ 0x4B, 75,	  113,  0b01001011,	"0x4B", "75", 	"113", "0100 1011",	"K",		"Upper Case Letter K" },
	{ 0x4C, 76,	  114,	0b01001100,	"0x4C", "76", 	"114", "0100 1100",	"L",		"Upper Case Letter L" },
	{ 0x4D, 77,	  115,	0b01001101,	"0x4D", "77", 	"115", "0100 1101",	"M",		"Upper Case Letter M" },
	{ 0x4E, 78,	  116,	0b01001110,	"0x4E", "78", 	"116", "0100 1110",	"N",		"Upper Case Letter N" },
	{ 0x4F, 79,	  117,	0b01001111,	"0x4F", "79", 	"117", "0100 1111",	"O",		"Upper Case Letter O" },
	{ 0x50, 80,	  120,	0b01010000,	"0x50", "80", 	"120", "0101 0000",	"P",		"Upper Case Letter P" },
	{ 0x51, 81,	  121,	0b01010001,	"0x51", "81", 	"121", "0101 0001",	"Q",		"Upper Case Letter Q" },
	{ 0x52, 82,	  122,	0b01010010,	"0x52", "82", 	"122", "0101 0010",	"R",		"Upper Case Letter R" },
	{ 0x53, 83,	  123,	0b01010011,	"0x53", "83", 	"123", "0101 0011",	"S",		"Upper Case Letter S" },
	{ 0x54, 84,   124,	0b01010100, "0x54", "84", 	"124", "0101 0100",	"T",		"Upper Case Letter T" },
	{ 0x55, 85,	  125,	0b01010101,	"0x55", "85", 	"125", "0101 0101",	"U",		"Upper Case Letter U" },
	{ 0x56, 86,	  126,	0b01010110,	"0x56", "86", 	"126", "0101 0110",	"V",		"Upper Case Letter V" },
	{ 0x57, 87,	  127,	0b01010111,	"0x57", "87", 	"127", "0101 0111",	"W",		"Upper Case Letter W" },
	{ 0x58, 88,	  130,	0b01011000,	"0x58", "88", 	"130", "0101 1000",	"X",		"Upper Case Letter X" },
	{ 0x59, 89,	  131,	0b01011001,	"0x59", "89", 	"131", "0101 1001",	"Y",		"Upper Case Letter Y" },
	{ 0x5A, 90,	  132,	0b01011010,	"0x5A", "90", 	"132", "0101 1010",	"Z",		"Upper Case Letter Z" },
	{ 0x5B, 91,	  133,	0b01011011,	"0x5B", "91", 	"133", "0101 1011",	"[",		"Left Square Bracket" },
	{ 0x5C, 92,	  134,	0b01011100,	"0x5C", "92", 	"134", "0101 1100",	"\\",		"Backslash" },
	{ 0x5D, 93,	  135,	0b01011101,	"0x5D", "93", 	"135", "0101 1101",	"]",		"Right Square Bracket" },
	{ 0x5E, 94,	  136,	0b01011110,	"0x5E", "94", 	"136", "0101 1110",	"^",		"Caret or Circumflex" },
	{ 0x5F, 95,	  137,	0b01011111,	"0x5F", "95", 	"137", "0101 1111",	"_",		"Underscore" },
	{ 0x60, 96,	  140,	0b01100000,	"0x60", "96", 	"140", "0110 0000",	"`",		"Grave Accent" },
	{ 0x61, 97,   141,	0b01100001,	"0x61", "97", 	"141", "0110 0001",	"a",		"Lower Case Letter a" },
	{ 0x62, 98,		142,	0b01100010,	"0x62",	"98",		"142", "0110 0010",	"b",		"Lower Case Letter b" },
	{ 0x63, 99,	  143,	0b01100011,	"0x63", "99",		"143", "0110 0011",	"c",		"Lower Case Letter c" },
	{ 0x64, 100,	144,	0b01100100,	"0x64", "100",	"144", "0110 0100",	"d",		"Lower Case Letter d" },
	{ 0x65, 101,	145,	0b01100101,	"0x65", "101",	"145", "0110 0101",	"e",		"Lower Case Letter e" },
	{ 0x66, 102,	146,	0b01100110,	"0x66", "102",	"146", "0110 0110",	"f",		"Lower Case Letter f" },
	{ 0x67, 103,	147,	0b01100111,	"0x67", "103",	"147", "0110 0111",	"g",		"Lower Case Letter g" },
	{ 0x68, 104,	150,	0b01101000,	"0x68", "104",	"150", "0110 1000",	"h",		"Lower Case Letter h" },
	{ 0x69, 105,	151,	0b01101001,	"0x69", "105",	"151", "0110 1001",	"i",		"Lower Case Letter i" },
	{ 0x6A, 106,	152,	0b01101010,	"0x6A", "106",	"152", "0110 1010",	"j",		"Lower Case Letter j" },
	{ 0x6B, 107,	153,	0b01101011,	"0x6B", "107",	"153", "0110 1011",	"k",		"Lower Case Letter k" },
	{ 0x6C, 108,	154,	0b01101100,	"0x6C", "108",	"154", "0110 1100",	"l",		"Lower Case Letter l" },
	{ 0x6D, 109,	155,	0b01101101,	"0x6D", "109",	"155", "0110 1101",	"m",		"Lower Case Letter m" },
	{ 0x6E, 110,	156,	0b01101110,	"0x6E", "110",	"156", "0110 1110",	"n",		"Lower Case Letter n" },
	{ 0x6F, 111,	157,	0b01101111,	"0x6F", "111",	"167", "0110 1111",	"o",		"Lower Case Letter o" },
	{ 0x70, 112,	160,	0b01110000,	"0x70", "111",	"160", "0111 0000",	"p",		"Lower Case Letter p" },
	{ 0x71, 113,	161,	0b01110001,	"0x71", "113",	"161", "0111 0001",	"q",		"Lower Case Letter q" },
	{ 0x72, 114,	162,	0b01110010,	"0x72", "114",	"162", "0111 0010",	"r",		"Lower Case Letter r" },
	{ 0x73, 115,	163,	0b01110011,	"0x73", "115",	"163", "0111 0011",	"s",		"Lower Case Letter s" },
	{ 0x74, 116,	164,	0b01110100,	"0x74", "116",	"164", "0111 0100",	"t",		"Lower Case Letter t" },
	{ 0x75, 117,	165,	0b01110101,	"0x75", "117",	"165", "0111 0101",	"u",		"Lower Case Letter u" },
	{ 0x76, 118,	166,	0b01110110,	"0x76", "118",	"166", "0111 0110",	"v",		"Lower Case Letter v" },
	{ 0x77, 119,	167,	0b01110111,	"0x77", "119",	"167", "0111 0111",	"w",		"Lower Case Letter w" },
	{ 0x78, 120,	170,	0b01111000,	"0x78", "120",	"170", "0111 1000",	"x",		"Lower Case Letter x" },
	{ 0x79, 121,	171,	0b01111001,	"0x79", "121",	"171", "0111 1001",	"y",		"Lower Case Letter y" },
	{ 0x7A, 122,	172,	0b01111010,	"0x7A", "122",	"172", "0111 1010",	"z",		"Lower Case Letter z" },
	{ 0x7B, 123,	173,	0b01111011,	"0x7B", "123",	"173", "0111 1011",	"{",		"Left Curly Bracket" },
	{ 0x7C, 124,  174,	0b01111100,	"0x7C", "124",	"174", "0111 1100",	"|",		"Vertical Bar" },
	{ 0x7D, 125,	175,	0b01111101,	"0x7D", "125",	"175", "0111 1101",	"}",		"Right Curly Bracket" },
	{ 0x7E, 126,  176,	0b01111110,	"0x7E", "126",	"176", "0111 1110",	"~",		"Tilde" },
	{ 0x7F, 127,	177,	0b01111111,	"0x7F", "127",	"177", "0111 1111",	"DEL",	"Delete" },
};

void string_screen(const char *string) {

  size_t size_data = string_size(string, 4096);
	String_Head(string, size_data);
  for (size_t index = 0; index < size_data; index++)
    String_Data(index, table, (int8_t)string[index]);
	return;
}
