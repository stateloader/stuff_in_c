/*----------------------------------------------------------------------------------------------------------------"BROWSER"
An "engine" of some sort during 'user-menu:ing' I came up with while playing around with function-pointers. Members of
'cmnd_item' guinding the user to the correct state depending on her/his commands. A neat caviat in this solution is how
bits being set (or cleared) simultaneously on the fly which finally being added to the request-protocol.
------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"
#include "scanner.h"  
#include "browser.h"

static int8_t state;// = BMAIN;

/*-------------------------------------------------------------------------------------------------------COMMAND STRUCTURE
3 (for now, more to come) menues being represented as 'command item'. Each item stores constants relevant for where the
user are now and where she/he's heading depending on which command being typed.
/-----------------------------------------------------------------------------------------------------------------------*/
typedef struct CommandItem {
  const uint8_t this_state;
  const uint8_t next_state;
  const char *cmnd;
} cmnd_item;

static cmnd_item main[] = {
  {BMAIN, BMESG, "-message"},
  {BMAIN, BDVCE, "-device"},
  {BMAIN, BEXIT, "-exit"}
};

static cmnd_item mesg[] = {
  {BMESG, BINIT, "-read"},
  {BMESG, BINIT, "-send"},
  {BMESG, BMAIN, "-back"}
};

static cmnd_item dvce[] = {
  {BDVCE, BINIT, "-read"},
  {BDVCE, BDLED, "-push"},
  {BDVCE, BMAIN, "-back"}
};

static cmnd_item dled[] = {
  {BDLED, BINIT, "-red"},
  {BDLED, BINIT, "-blue"},
  {BDLED, BINIT, "-green"},
  {BDLED, BMAIN, "-back"}
};
/*---------------------------------------------------------------------------------------------------------BYTE BlUEPRINTS
The static variables TABLE, ATTRB and FORWD are used as blueprints during the command-session. Like the protocol-array
they being assigned to when the user's done they're unsigned bytes; this because not being regarded as nullbytes (which
screwed things up for me while sending package to the server).
/-----------------------------------------------------------------------------------------------------------------------*/
static uint8_t TABLE = 0x80;
static uint8_t ATTRB = 0x80;

static void reset_protocol(void) {
  TABLE = 0x80, ATTRB = 0x80;
  state = BMAIN;
}

static void write_protocol(cmnd_item item, int8_t index) {
/*'item' and 'index' args determines which state/item we're currently in and which index (command) the user choosed in the
 *'command_scan'-function prior. This data makes it possible for bitwise operation on the 'blueprint-bytes'
 */
  switch(item.this_state) {

  case BMAIN:
    reset_protocol();
    TABLE |= (1 << index);
  break;
  case BMESG:
    ATTRB |= (index << RWBIT);
  break;
  case BDVCE:
    ATTRB |= (index << RWBIT);
  break;
  case BDLED:
    ATTRB |= (1 << index);
  break;
  default:
    System_Message("Something went south while writing protocol.");
    exit(EXIT_FAILURE);
  }
  return;
}

static int8_t command_scan(cmnd_item *items, size_t size_array) {

  for (size_t i = 0; i < size_array; i++)
    printf("\t\t\t%s\n", items[i].cmnd);

  char command[SBUFF] = {'\0'};
  size_t cmnd_size = scan_driver(command, SBUFF, "select");

  for (size_t i = 0; i < size_array; i++) {
    if (string_comp(command, items[i].cmnd, cmnd_size)) {
      if (i < size_array - 1)
        write_protocol(items[i], i);
      return items[i].next_state;
    }
  }
  System_Message("Not an option. try again");
  return state;
}

int8_t browse_driver(client_t *client) {

  state = BMAIN;

  while (state != BINIT) {
   
    switch(state) {
    case BMAIN:
      Render_Header("MAIN       ", "Main ipsum dolor sit amet, consectetur adipiscing elit");
      state = command_scan(main, ARRAY_SIZE(main));
      break;
    case BMESG:
      Render_Header("MESSAGE    ", "Message ipsum dolor sit amet, consectetur adipiscing elit");
      state = command_scan(mesg, ARRAY_SIZE(mesg));
      break;
    case BDVCE:
      Render_Header("DEVICE     ", "Device ipsum dolor sit amet, consectetur adipiscing elit");
      state = command_scan(dvce, ARRAY_SIZE(dvce));
      break;
    case BDLED:
      Render_Header("PUSH       ", "PUSH ipsum dolor sit amet, consectetur adipiscing elit");
      state = command_scan(dled, ARRAY_SIZE(dled));
      break;
    }
    if (state == BEXIT) {
      client->session &= ~(1 << ALIVE);
      System_Message("bye!");
      return EXIT;
    }
  }

  client->protocol[TBYTE] = TABLE;
  client->protocol[ABYTE] = ATTRB;

  return SUCC;
}
