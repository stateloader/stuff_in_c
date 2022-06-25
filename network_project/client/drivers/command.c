/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   COMMAND
--------------------------------------------------------------------------------------------------------------------------
An "engine" of some sort during 'user-menu:ing' I came up with while playing around with function-pointers. Members of
'cmnd_item' helps (a lot) in guinding the user to the correct state depending on her/his commands. A neat caviat in this
solution is how bits being set (or cleared) simultaneously in the process which later being added to the request-protocol. 
------------------------------------------------------------------------------------------------------------------------*/

#include "scanner.h"
#include "cstring.h"
#include "command.h"

static uint8_t TASK = _MDEF;
static uint8_t EXEC = _MDEF;
static uint8_t FWRD = _MDEF;

typedef struct CommandItem {
  const uint8_t this_state;
  const uint8_t next_state;
  const char *cmnd;
} cmnd_item;

static int8_t state = _MAIN; 

static cmnd_item main[] = {
  {_MAIN, _MESG, "-message"}, {_MAIN, _DVCE, "-device"}, {_MAIN, _EXIT, "-exit"}
};
static cmnd_item mesg[] = {
  {_MESG, _EXIT, "-read"}, {_MESG, _EXIT, "-send"}, {_MESG, _MAIN, "-back"}
};
static cmnd_item dvce[] = {
  {_DVCE, _EXIT, "-red"}, {_DVCE, _EXIT, "-blue"}, {_DVCE, _EXIT, "-green"}, {_DVCE, _MAIN, "-back"}
};

static void static_cleanup(void) {
  TASK = _MDEF;
  EXEC = _MDEF;
  FWRD = _MDEF;
  state = _MAIN;
}

static void render_options(cmnd_item *items, size_t size_array) {
  for (size_t i = 0; i < size_array; i++)
    printf("\t\t\t%s\n", items[i].cmnd);
}

static void write_protocol(cmnd_item item, int8_t index) {

  switch(item.this_state) {
  case _MAIN:
    TASK &= ~(1 << TDVCE);
    TASK &= ~(1 << TMESG);
    TASK |= (1 << index);
    break;
  case _MESG:
    EXEC |= (index << RWBIT);
    break;
  case _DVCE:
    EXEC |= (1 << index) | (1 << RWBIT);
    break;
  default:
    System_Message("Some mishaps in bit");
    static_cleanup();
  }
  return;
}

static int8_t command_scan(cmnd_item *items, size_t size_array) {
  render_options(items, size_array);

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

void command_driver(uint8_t *protocol) {

  while (state != _EXIT) {

    switch(state) {
    case _MAIN:
      Render_Header("MAIN      |", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
      state = command_scan(main, ARRAY_SIZE(main));
      break;
    case _MESG:
      Render_Header("MESSAGE   |", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
      state = command_scan(mesg, ARRAY_SIZE(mesg));
      break;
    case _DVCE:
      Render_Header("DEVICE    |", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
      state = command_scan(dvce, ARRAY_SIZE(dvce));
      break;
    }
  }
  
  protocol[TINDX] = TASK;
  protocol[EINDX] = EXEC;
  protocol[FINDX] = FWRD;

  static_cleanup();
}