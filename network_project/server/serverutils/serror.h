#ifndef SERROR_H_
#define SERROR_H_

#define SYSTEM_INFO_FORMAT "INFO\t\t\t\t%s\n"
#define System_Info_Message(info) (printf(SYSTEM_INFO_FORMAT, info))

#define STRING_ERROR_FORMAT "STRING ERROR----\nFUNC: %s\nNOTE %s\n\n'%s'\n"     
#define String_Error_Message(errfunc, errnote, errstr) printf(STRING_ERROR_FORMAT, errfunc, errnote, errstr)

#define INTEGER_INFO_FORMAT "INTEGER - %d NOTE %s\n"
#define Integer_Info_Message(integer, note) (printf(INTEGER_INFO_FORMAT, integer, note))

#define RETVAL_VALID_FORMAT "DESIRED: %d \t OUTCOME: %d \t NOTE: OK\n"
#define Retval_Valid_Message(desired, outcome) printf(RETVAL_VALID_FORMAT, desired, outcome)     

#define RETVAL_ERROR_FORMAT "RETVAL ERROR----DESIRED %d - OUTCOME - %d - NOTE: %s\n"     
#define Retval_Error_Message(desired, outcome, note) printf(RETVAL_ERROR_FORMAT, desired, outcome, note)

#endif