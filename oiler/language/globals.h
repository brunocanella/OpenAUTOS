#ifndef LANGUAGE_GLOBALS_H
#define LANGUAGE_GLOBALS_H

#ifndef YYSTYPE
typedef union {	
	int ival;
	char* sval;
	double dval;  
//  struct symtab *symp;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
/* extern YYSTYPE yylval; */
YYSTYPE yylval;

////////////////////////
typedef struct {
	int type;
	yystype value;
} LiteralValue;
////////////////////////

typedef struct {
	char* type;
	char* name;
} Object;

#define RESOURCE_TYPE_UNDEFINED 0
#define RESOURCE_TYPE_STANDARD 1
#define RESOURCE_TYPE_LINKED 2
#define RESOURCE_TYPE_INTERNAL 3

typedef struct SResource{
	char name[255];
	int type;
	int priority;
	struct SResource* linked;
} Resource;

#define TASK_MAX 255
#define RESOURCE_MAX 255
#define TASK_RESOURCE_MAX 16

typedef struct {
	char name[255];
	int priority;
	int schedule; // If the SCHEDULE attribute is set to NON, no internal resources may be assigned to this task.
	int activation;
	int autostart;
	char* autostart_appmodes[16];
	int autostart_count;
	Resource* resources[TASK_RESOURCE_MAX];
	int resource_count;
} Task;

typedef struct {
	Task tasks[TASK_MAX];
	int task_count;
	Resource resources[RESOURCE_MAX];
	int resource_count;
} OS;

#endif//LANGUAGE_GLOBALS_H