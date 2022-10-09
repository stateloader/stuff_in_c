#include "tasker.h"

const char PURE_ART[5][25] = {

    {'#','#','#','#','#',' ','#','#','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#','#','#'},
    {' ',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#','#',' ',' ','#',' ',' ',' ','#',' ','#'},
    {' ',' ','#',' ',' ',' ','#','#','#',' ','#','#','#',' ','#',' ',' ',' ','#','#',' ',' ','#','#','#'}, 
    {' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#','#',' ',' ','#',' ',' ',' ','#','#',' '},
    {' ',' ','#',' ',' ',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#'}
};

const char *INFO_PROGRAM	= "\nthis is taskhandler or something. Basically it's all about adding, removing and moving around\n"\
							  "tasks to your heart's content instead of actually complete them.\n\n\033[2;7;1mnote! when writing strings in "\
							  "in \"Tasker\", type \"$\" before hitting enter when done.\033[2;7;0m\n";

const char *MENU_FORM 		= "\n\033[1m%s\033[0m\n%s\n";

const char *MENU_SELECT		= "SELECT\t1) Add Task\t2) Swap Tasks\t\t3) Remove Task\t\t4) Read active Task(s)";
const char *INFO_SELECT		= "\tenter number\t\033[1m5) Complete Task\033[0m\t\033[1m6) Completed Tasks\033[0m\t\033[33m7) Exit Tasker\033[0m";

const char *MENU_MANAGE		= "DISPLAY\t1) All\t\t2) By List\t\t3) By Topic\t\t4) By Title";

const char *INFO_ADD		= "\033[2;7;1mAdd\033[2;7;0m\tcreate a new note/task by enter listname, topic, title and an entry.\n\n";
const char *INFO_SWAP		= "\033[2;7;1mSwap\033[2;7;0m\tsearch or display all tasks before swapping.\t\t\t\033[33m5) Back\033[0m\n";
const char *INFO_REMOVE		= "\033[2;7;1mRemove\033[2;7;0m\tsearch or display all tasks before removing.\t\t\t\033[33m5) Back\033[0m\n";
const char *INFO_READ		= "\033[2;7;1mRead\033[2;7;0m\tread active tasks.\t\t\t\t\t\t\033[33m5) Back\033[0m\n";
const char *INFO_FILING		= "\033[2;7;1mFiling\033[2;7;0m\tread active tasks before mark as completed.\t\t\t\033[33m5) Back\033[0m\n";
const char *INFO_FILED		= "\033[2;7;1mFiled\033[2;7;0m\tsearch or read all completed tasks.\t\t\t\t\033[33m5) Back\033[0m\n";

const char *WARN_FORM		= "\033[33m\t%s\033[0m\n";

const char *WARN_LESS1		= "database empty.";
const char *WARN_LESS2		= "nodeswaps requires at least two tasks in database.";
const char *WARN_FILED		= "no tasks completed yet, you rockstar!";
const char *WARN_SEEKN		= "no matches found";
const char *WARN_INPUT		= "\n\033[33minvalid input, try again.\033[0m";
const char *WARN_INPUTY		= "\n\t\033[33minvalid input, try again.\033[0m\n";
const char *WARN_ID			= "\033[33mid doesn't exist, try again.\033[0m\n";

const char *INFO_FORM		= "\033[33m%s\033[0m\n";

const char *INFO_REDUCE     = "remove task by enter its id.";
const char *INFO_VALIDATE	= "proceed\t1) yes 2) no";
const char *INFO_COMPLETE	= "enter id to declare task as completed.";
const char *INFO_SWAP_NODES = "swap tasks by id:s.";
const char *INFO_SEEK_LNAME = "enter search phrase for listname.";
const char *INFO_SEEK_TOPIC = "enter search phrase for topic.";
const char *INFO_SEEK_TITLE = "enter search phrase for title.";

const char *SHOW_FORM		= "\n\033[1m%s \"%s\"\033[0m\n\n";

const char *INFO_SHOW_ALL	= "Active Tasks in database";
const char *INFO_SHOW_LNAME = "Lists found";
const char *INFO_SHOW_TOPIC = "Topics found";
const char *INFO_SHOW_TITLE = "Titles found";		

const char *READ_FORM 		= "\033[2;7;1mID %d\033[2;7;0m  \033[33mDate Created \033[0m%d-%d-%d "\
							  "\033[33mList \033[0m%s \033[33mTopic \033[0m%s \033[33mTitle \033[0m%s\n\n%s\n\n";

int main() {

	char rc = 0;
	REFRESH();
	
	rc = DataBase_set();
	check(rc == 0, "failed set database");

	while (1) {
		
		run_info(MENU_FORM, MENU_SELECT, INFO_SELECT);
		IOSelect select = (int)std_numnwrap(ADD_TASK, IEND, WARN_INPUTY) - 1;
		
		if (select == QUIT) { break; }
		
		rc = tasker_run(&select);
		check(rc == 0, "failed while running session");
	}
	return 0;
error:
	return 1;
}

Connection *Connection_create() {

	Connection * conn = calloc(1, sizeof(Connection));
	check(conn != NULL, "failed to calloc conn");
	
	conn->ldata = calloc(1, sizeof(DataBase));
	check(conn->ldata != NULL, "failed to calloc ldata");
	
	return conn;
error:
	return NULL;
}

char tasker_run(IOSelect * select) {
//	reads data from db-files, alternates it and rewrites a modified version in the end.
	char rc = 0;
	
	Connection *conn = Connection_create();
	check(conn != NULL, "failed to create connection");
	
	rc = DataBase_read(conn);
	check(rc == 0, "failed to read database");

	switch(*select) {	
			
		case ADD_TASK:
			run_info("%s", INFO_ADD);	
			
			rc = node_array_expand(conn);
			check(rc == 0, "failed to resize node array");
			
			rc = node_array_add(conn);
			check(rc == 0, "failed to add node");
			break;	
	
		case MOV_TASK:
			if(run_warn(conn->ldata->end, 3)) { run_info(WARN_FORM, WARN_LESS2); break; }
			run_info(MENU_FORM, MENU_MANAGE, INFO_SWAP);			
			
			rc = DataBase_print(conn);	
			if (rc == - 1 || conn->hits < 2) { break; }
			
			rc = node_array_swap(conn);
			check(rc == 0, "failed to swap nodes");
			break;
			
		case RMV_TASK:
			if (run_warn(conn->ldata->end, 2)) { run_info(WARN_FORM, WARN_LESS1); break; }
			run_info(MENU_FORM, MENU_MANAGE, INFO_REMOVE);
			
			rc = DataBase_print(conn);
			if (rc == - 1 || conn->hits < 1) { break; }
			
			rc = node_array_reduce(conn);
			check(rc == 0, "failed remove record");
			break;

		case GET_TASK:
			if (run_warn(conn->ldata->end, 2)) { run_info(WARN_FORM, WARN_LESS1); break; }
			run_info(MENU_FORM, MENU_MANAGE, INFO_READ);
			DataBase_print(conn);
			break;

		case CMP_TASK:
			if (run_warn(conn->ldata->end, 2)) { run_info(WARN_FORM, WARN_LESS1); break; }
			run_info(MENU_FORM, MENU_MANAGE, INFO_FILING);

			rc = DataBase_print(conn);
			if (rc == - 1 || conn->hits < 1) { break; }

			rc = node_array_set_complete(conn);
			check(rc == 0, "failed to file task");
			break;
			
		case GET_CMP:
			if (run_warn(conn->ldata->cmp, 1)) { run_info(WARN_FORM, WARN_FILED); break; }
			run_info(MENU_FORM, MENU_MANAGE, INFO_FILED);
			
			conn->archive++;

			rc = DataBase_print(conn);
			if (rc == - 1 || conn->hits < 1) { break; }

			break;

		default:
			run_info(WARN_FORM, WARN_INPUT);
	}
	rc = DataBase_write(conn);
	check(rc == 0, "failed to update database");	
	
	conn_kill(conn);
	return 0;
error:
	conn_kill(conn);
	return 1;
}

char DataBase_set() {
//	sets (if new) database.
	char rc = 0;
	const char *database = "database.dat";	
	Connection *conn = Connection_create();
	check(conn != NULL, "failed to create connection");
	
	conn->file = fopen(database, "r");
	if (!conn->file) {
		rc = node_array_create(conn);
		check(rc == 0, "failed to set array");
		rc = DataBase_write(conn);
		check(rc == 0, "failed to set database");
	}
	conn_kill(conn);
	return 0;
error:
	conn_kill(conn);
	return 1;
}

char DataBase_write(Connection * conn) {
//	writing data to files.
	char rc = 0;

	rc = db_data_set(conn);
	check(rc == 0, "failed to write ldata");
	rc = db_node_set(conn);
	check(rc == 0, "failed to write ndata");
	
	return 0;
error:
	return 1;
}

char DataBase_read(Connection * conn) {
//	reading data from files.
	char rc = 0;
	
	rc = db_data_get(conn);
	check(rc == 0, "failed to read ldata");
	rc = db_node_get(conn);
	check(rc == 0, "failed to read ndata");
	
	return 0;
error:
	return 1;
}

char db_data_set(Connection * conn) {											//
//	writing database.
	const char *database = "database.dat";	
	short rc = 0;

	conn->file = fopen(database, "w");
	check(conn->file != NULL, "failed to open file");
	
	rewind(conn->file);
	
	rc = fwrite(conn->ldata, sizeof(DataBase), 1, conn->file);
	check(rc == 1, "failed to write file");
	
	rc = fflush(conn->file);
	check(rc == 0, "failed to flush");
	
	file_kill(conn);
	return 0;
error:
	file_kill(conn);
	return 1;
}

char db_node_set(Connection * conn) {
//	writing nodedata (separate file).
	const char *nodebase = "nodebase.dat";	
	short rc = 0;

	conn->file = fopen(nodebase, "w");
	check(conn->file != NULL, "failed to open file");

	rewind(conn->file);
	
	rc = fwrite(conn->ldata->ndata, sizeof(NodeData),
		conn->ldata->end, conn->file);
	check(rc == conn->ldata->end, "failed to write file");

	rc = fflush(conn->file);
	check(rc == 0, "failed to flush");
	
	file_kill(conn);
	return 0;
error:
	file_kill(conn);
	return 1;
}

char db_data_get(Connection * conn) {												//
//	reading database.
	const char *database = "database.dat";
	short rc = 0;

	conn->file = fopen(database, "r");
	check(conn->file, "failed to open file");
	
	rc = fread(conn->ldata, sizeof(DataBase), 1, conn->file);
	check(rc == 1, "failed to read file");
	
	file_kill(conn);
	return 0;
error:
	file_kill(conn);
	return 1;
}

char db_node_get(Connection * conn) {
//	reading nodedata (separate file).
	const char *nodebase = "nodebase.dat";	
	short rc = 0;

	conn->ldata->ndata = calloc(conn->ldata->end, sizeof(NodeData));
	check(conn->ldata->ndata != NULL, "failed to create ndata");
	
	conn->file = fopen(nodebase, "r");
	check(conn->file != NULL, "failed to open file");
	
	rc = fread(conn->ldata->ndata, sizeof(NodeData),
		conn->ldata->end, conn->file);
	check(rc == conn->ldata->end, "failed to read file");

	file_kill(conn);
	return 0;
error:
	file_kill(conn);
	return 1;
}

void NodeData_copy(NodeData * to, NodeData * from, int i) {
//	copy node. used inside for-loops.
	to->id = i;
	to->filed = from->filed;
	to->date_created[0] = from->date_created[0];
	to->date_created[1] = from->date_created[1];
	to->date_created[2] = from->date_created[2];

	for(i = 0; i < SLEN; i++) {
		to->lname[i] = from->lname[i];
		to->topic[i] = from->topic[i];
		to->title[i] = from->title[i];
	}
	for(i = 0; i < TELL; i++)
		to->entry[i] = from->entry[i];
}

char node_array_create(Connection * conn) {											
//	sets (first member) in an array of nodes.
	conn->ldata->end = 1;
	
	conn->ldata->ndata = calloc(conn->ldata->end, sizeof(NodeData));
	check(conn->ldata->ndata != NULL, "failed to alloc memory");
			
	NodeData ndata = { .filed = 0 };
	conn->ldata->ndata[conn->ldata->end - 1] = ndata;
	
	return 0;
error:
	return 1;
}

char node_array_add(Connection * conn) {
//	adding nodedata.	
	char rc = 0;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	check(conn->ldata->end < 65535, "max nodes reached");
	
	NodeData *new = &conn->ldata->ndata[conn->ldata->end - 1];
	check(new != NULL, "failed to create new node");
	new->id = conn->ldata->end - 1;
	
	new->date_created[0] = tm.tm_year + 1900;
	new->date_created[1] = tm.tm_mon + 1;
	new->date_created[2] = tm.tm_mday;

	printf("lname>\t");
	rc = std_strwrap(new->lname);
	check(rc == 0, "failed to set lname");
	
	printf("topic>\t");
	rc = std_strwrap(new->topic);
	check(rc == 0, "failed to set topic");
	
	printf("title>\t");
	rc = std_strwrap(new->title);
	check(rc == 0, "failed to set title");
	
	printf("\ndescribe task\n\n");
	rc = std_strwrap(new->entry);
	check(rc == 0, "failed to set entry");			

	conn->ldata->end++;

	return 0;
error:
	return 1;
}

char node_array_expand(Connection * conn) {
//	adding memory (for a new node).
	unsigned short i = 0;
	unsigned short new_size = conn->ldata->end + 1;
	unsigned short old_size = conn->ldata->end;

	NodeData *temp_buffer = calloc(new_size, sizeof(NodeData));
	check(temp_buffer != NULL, "failed to create temp_buffer");
	// copy old data.
	for (i = 0; i < old_size; i++) {
		NodeData *temp = &temp_buffer[i];
		NodeData *from = &conn->ldata->ndata[i];
		NodeData_copy(temp, from, i);
	}
	// kill old, rebuild++.
	prev_kill(conn);
	conn->ldata->ndata = calloc(new_size, sizeof(NodeData));
	check(conn->ldata->ndata != NULL, "failed to resize conn");
	// copy modified array in temp "back"++.
	for (i = 0; i < new_size; i++) {
		NodeData *temp = &temp_buffer[i];
		NodeData *update = &conn->ldata->ndata[i];
		NodeData_copy(update, temp, i);
	}
	free(temp_buffer);
	temp_buffer = NULL;
	return 0;
error:
	if(temp_buffer) free(temp_buffer);
	temp_buffer = NULL;	
	return 1;
}

char node_array_reduce(Connection * conn) {
// 	pops a given node before reducing the array.
	char val = 0;
	unsigned short i = 0, id = 0, jump = 0, rmv = 0;
	unsigned short arr_size = conn->ldata->end;

	run_info(INFO_FORM, INFO_REDUCE);
	printf("id>\t");
	id = std_numnwrap(0, arr_size - 2,
			"\t\033[33mid doesn't exist.\033[0m\nid>\t");
			
	run_info(INFO_FORM, INFO_VALIDATE);
	printf("tell>\t");
	val = std_validate("\033[33mwrong input, try again\033[0m\ntell>\t");
	if (val == 1) return 0;
	
	NodeData temp_buffer[arr_size];
	
	for(i = 0; i < arr_size; i++) {
		NodeData new = { .id = i };
		temp_buffer[i] = new;
	}
	// copy old data.	
	for (i = 0; i < arr_size; i++) {
		NodeData *from = &conn->ldata->ndata[i];	
		NodeData *to = &temp_buffer[i];
		NodeData_copy(to, from, i);
	}
	// kill old, rebuild.	
	prev_kill(conn);
	conn->ldata->ndata = calloc(arr_size, sizeof(NodeData));
	check(conn->ldata->ndata != NULL, "failed to resize conn");
	
	for (i = 0; i < arr_size; i++) {
	// if id of choosed rmv isn't "hit", carry on...	
		rmv = i < id ? 0 : 1;
		if (rmv == 0) {
			NodeData *from = &temp_buffer[i];
			check(from != NULL, "pointerfailure");	
			NodeData *to = &conn->ldata->ndata[i];
			check(to != NULL, "pointerfailure");	
			NodeData_copy(to, from, i);
		}
	//...else copy one node ahead from now on...	
		else {
			jump = i + 1;
			NodeData *from = &temp_buffer[jump];
			check(from != NULL, "pointerfailure");	
			NodeData *to = &conn->ldata->ndata[i];
			check(to != NULL, "pointerfailure");	
			NodeData_copy(to, from, i);
		}
	}
	//...and reduce arr_size ignoring the last "offsetnode". 
	conn->ldata->end--;
	return 0;
error:
	return 1;
}

char node_array_swap(Connection * conn) {
//	swapping nodes.
	unsigned short arr_size = conn->ldata->end;
	unsigned short n1 = 0, n2 = 0, i = 0;

	run_info(INFO_FORM, INFO_SWAP_NODES);
	
	printf("swap>\t");
	n1 = std_numnwrap(0, arr_size - 2,
		"\t\033[33mid doesn't exist\033[0m\nswap>\t");
	printf("with>\t");
	n2 = std_numnwrap(0, arr_size - 2,
		"\t\033[33mid doesn't exist\033[0m\nwith>\t");

	NodeData *origin = conn->ldata->ndata;
	NodeData *temp_buffer = calloc(arr_size, sizeof(NodeData));
	// copy old data while inserting "swapnodes" in right order.
	for (i = 0; i < arr_size; i++) {
		NodeData *from = &origin[i];
		NodeData *to = &temp_buffer[i];
		if (i == n1) {
			from = &origin[n2];
			NodeData_copy(to, from, i);			
		} else if (i == n2) {
			from = &origin[n1];		
			NodeData_copy(to, from, i);
		} else {
			NodeData_copy(to, from, i);
		}
	}
	// kill old, rebuild.	
	prev_kill(conn);
	conn->ldata->ndata = calloc(arr_size, sizeof(NodeData));
	check(conn->ldata->ndata != NULL, "failed alloc array");
	// copy modified array in temp "back".		
	for (i = 0; i < arr_size; i++) {
		NodeData *from = &temp_buffer[i];
		NodeData *to = &conn->ldata->ndata[i];
		NodeData_copy(to, from, i);
	}
	free(temp_buffer);
	temp_buffer = NULL;

	return 0;
error:
	if (temp_buffer)
		free(temp_buffer);
	temp_buffer = NULL;
	return 1;
}

char node_array_set_complete(Connection * conn) {
//	flags given node as complete.
	unsigned short arr_size = conn->ldata->end;
	unsigned short id = 0, i = 0;
	
	run_info(INFO_FORM, INFO_COMPLETE);
	
	printf("id>\t");
	id = std_numnwrap(0, arr_size - 2,
		"\t\033[33mid doesn't exist\033[0m\nswap>\t");

	NodeData *node_array = conn->ldata->ndata;

	for (i = 0; i < arr_size; i++) {
		NodeData *cur = &node_array[i];
		check(cur != NULL, "pointerfailure");			
		if (i == id) {
			cur->filed = 1;
		}
	}	
	conn->ldata->cmp++;
	return 0;
error:
	return 1;
}

char DataBase_print(Connection *conn) {
//	pointing to a given print/"display"-func by enum.
	void (*seek_arr_ptr[])(Connection *conn) = { seek_all, seek_lname, seek_topic, seek_title };
	LISelect select = (int)std_numnwrap(READ_ALL + 1, LEND, WARN_INPUT) - 1;
	
	if (select == LBACK)
		return -1;
	seek_arr_ptr[select](conn);
	return 0;
}

void seek_all(Connection *conn) {

	unsigned short i = 0;
	
	NodeData *ndata = conn->ldata->ndata;	
	
	REFRESH();
	run_info(SHOW_FORM, INFO_SHOW_ALL, "database.dat");

	if (!conn->archive) {
		for (i = 0; i < conn->ldata->end - 1; i++) {
			if (!ndata[i].filed) {
				node_print(ndata+i);
		 		conn->hits++;	
			}
		}
	} else if (conn->archive) {
		for (i = 0; i < conn->ldata->end - 1; i++) {
			if (ndata[i].filed) {
				node_print(ndata+i);
		 		conn->hits++;	
			}
		}			
	}
	if(!conn->hits)
		run_info(WARN_FORM, WARN_SEEKN);
}
	
void seek_lname(Connection *conn) {

	char seek[SLEN];
	unsigned short i = 0;
	run_info(INFO_FORM, INFO_SEEK_LNAME);
	NodeData * ndata = conn->ldata->ndata;
	
	printf("lname>\t");
	std_strwrap(seek);
	
	REFRESH();
	run_info(SHOW_FORM, INFO_SHOW_LNAME, seek);
	
	if (!conn->archive) {
		for (i = 0; i < conn->ldata->end - 1; i++) {
			if (strncmp(seek, ndata[i].lname, 4) == 0 && !ndata[i].filed) {
				node_print(ndata+i);
		 		conn->hits++;	
			}
		}
	} else {
		for (i = 0; i < conn->ldata->end - 1; i++) {
			if (strncmp(seek, ndata[i].lname, 4) == 0 && ndata[i].filed) {
				node_print(ndata+i);
			}
		}			
	}
	if(!conn->hits)
		run_info(WARN_FORM, WARN_SEEKN);
}

void seek_topic(Connection *conn) {

	char seek[SLEN];
	unsigned short i = 0;
	run_info(INFO_FORM, INFO_SEEK_LNAME);
	NodeData * ndata = conn->ldata->ndata;
	
	printf("topic>\t");
	std_strwrap(seek);

	REFRESH();
	run_info(SHOW_FORM, INFO_SHOW_TOPIC, seek);
	if (!conn->archive) {
		for (i = 0; i < conn->ldata->end - 1; i++) {
			if (strncmp(seek, ndata[i].topic, 4) == 0 && !ndata[i].filed) {
				node_print(ndata+i);
		 		conn->hits++;	
			}
		}
	} else {
		for (i = 0; i < conn->ldata->end - 1; i++) {
			if (strncmp(seek, ndata[i].topic, 4) == 0 && ndata[i].filed) {
				node_print(ndata+i);
			}
		}			
	}
	if(!conn->hits)
		run_info(WARN_FORM, WARN_SEEKN);
}

void seek_title(Connection *conn) {
	
	char seek[SLEN];
	unsigned short i = 0;
	run_info(INFO_FORM, INFO_SEEK_LNAME);
	NodeData * ndata = conn->ldata->ndata;
	
	printf("title>\t");
	std_strwrap(seek);
	
	REFRESH();
	run_info(SHOW_FORM, INFO_SHOW_TITLE, seek);
	
	if (!conn->archive) {
		for (i = 0; i < conn->ldata->end - 1; i++) {
			if (strncmp(seek, ndata[i].title, 4) == 0 && !ndata[i].filed) {
				node_print(ndata+i);
		 		conn->hits++;	
			}
		}
	} else {
		for (i = 0; i < conn->ldata->end - 1; i++) {
			if (strncmp(seek, ndata[i].title, 4) == 0 && ndata[i].filed) {
				node_print(ndata+i);
			}
		}			
	}
	if(!conn->hits)
		run_info(WARN_FORM, WARN_SEEKN);
}

void title() {
//	pure art.
	short i = 0, j = 0;
	for(i = 0; i < 5; i++) {
		for(j = 0; j < 25; j++) {
			printf("%c", PURE_ART[i][j]);
		}
		printf("\n");
	}
}
