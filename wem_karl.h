#ifndef WEM_KARL_H
#define WEM_KARL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - information about the shell's state
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated which is arguments
 * @path: a string path for the command type
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* sh_loop.c */
int runShell(info_t *, char **);
int findBuiltInCommand(info_t *);
void findExecutable(info_t *);
void executeCommand(info_t *);

/* command_parser.c */
int isCommandInPath(info_t *, char *);
char *copySubstring(char *, int, int);
char *findExecutablePath(info_t *, char *, char *);

/* errors.c */
void printInputString(char *str);
int printChar(char c);
int writeCharToFile(char c, int fd);
int writeStringToFile(char *str, int fd);

/* handle_string.c */
int getStrLen(char *str);
int compareStr(char *str1, char *str2);
char *starts_with(const char *, const char *);
char *concatStr(char *dest, char *src);

/* handle_string1.c */
char *copyStr(char *destination, char *source);
char *duplicateStr(const char *original);
void putStr(char *str);
int putChar(char c);

/* exit.c */
char *copyNChar(char *dest, char *src, int n);
char *concatNChar(char *dest, char *src, int n);
char *findChar(char *str, char target);

/* tokenisation.c */
char **splitStringByDelim(char *str, char *delimiter);
char **splitStringByChar(char *str, char c);

/* realloc.c */
char *fillMemory(char *dest, char value, unsigned int size);
void freeStringArray(char **strArray);
void *reallocMemory(void *ptr, unsigned int oldSize, unsigned int newSize);

/* memory.c */
int bfree(void **);

/* our_atoi.c */
int isInteractive(info_t *info);
int isDelimiter(char character, char *delimiters);
int isAlpha(int character);
int StringToInteger(char *str);

/* errors1.c */
int ErrorStringToInteger(char *str);
void printErrorMessage(info_t *info, char *message);
int printDecimalNumber(int num, int fd);
char *NumberToString(long int number, int base, int isSigned);
void removeComments(char *str);

/* builtin.c */
int exitCommand(info_t *info);
int changeDirectory(info_t *info);
int help(info_t *info);

/* builtin1.c */
int history(info_t *);
int alias(info_t *);

/* our_getline.c */
ssize_t readInput(info_t *info);
int getLine(info_t *info, char **line, size_t *len);
void handleSIGINT(int signal);

/* getinfo.c */
void clearInfo(info_t *);
void setInfo(info_t *, char **);
void freeInfo(info_t *, int);

/* environ.c */
char *getEnvironVariable(info_t *info, const char *name);
int EnvCommand(info_t *info);
int SetEnvCommand(info_t *info);
int UnsetEnvCommand(info_t *info);
int populateEnvironmentList(info_t *info);

/* our_getenv.c */
char **getEnvList(info_t *info);
int unsetEnvVariable(info_t *info, char *name);
int setEnvVariable(info_t *info, char *name, char *value);

/* history.c */
char *getHistoryFileName(info_t *info);
int writeHistoryToFile(info_t *info);
int readHistoryFromFile(info_t *info);
int buildHistoryList(info_t *info, char *buffer, int lineCount);
int renumberHistory(info_t *info);

/* lists.c */
list_t *insertNode(list_t **head, const char *data, int value);
list_t *insertNodeAtEnd(list_t **head, const char *data, int value);
size_t printStringList(const list_t *head);
int deleteNodeAtIndex(list_t **head, unsigned int index);
void freeLinkedList(list_t **head);

/* lists1.c */
size_t getListLength(const list_t *);
char **convertListToStringArray(list_t *);
size_t printListElements(const list_t *);
list_t *findNodeStartingWith(list_t *head, char *prefix, char character);
ssize_t getNodeIndex(list_t *head, list_t *nodeToFind);

/* vars.c */
int isChain(info_t *info, char *str, size_t *position);
void checkChain(info_t *info, char *str, size_t *start, size_t length, size_t maxLength);
int replaceAliases(info_t *info);
int replaceVariables(info_t *info);
int replaceStringInArray(char **array, char *replacement);

#endif
