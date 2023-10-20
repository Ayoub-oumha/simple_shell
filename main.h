#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
extern char **environ;
/* split */
#define NORM	0
#define ORC		1
#define ANDC		2
#define CHNN	3
/* split */
#define OUTPUT_BUF_SIZE 1024
#define EXITT -1

/**
 * struct stringLis - list of string
 * @str: string
 * @num: index
 * @next: adress of next
 */
typedef struct stringLis
{
	char *str;
	int num;
	struct stringLis *next;
} list_t;

/**
 *struct shellVars - variable of shell
 *@arg: agrument
 *@argv: an array of agruments
 *@path: original path
 *@executableName: executableName when gcc
 *@environ: workable environ
 *@cmdBuffe: adress to buffer
 *@lenAgrument: number of agrument
 *@errorCode: code of exit error
 *@isNonVide: if there is lines
 *@isEnvChanged: is env changed or nor
 *@execStatues: exec statue
 *@CMDORAND: type if and or extra
 *@filedesiptor: filedesiptor
 *@historyNLines: len of lines in hist
 *@lCount: number
 *@envLisst: list of env
 *@history: node header of history
 *@alias: alias list header
 */
typedef struct shellVars
{
	char *arg;
	char **argv;
	char *path;
	char *executableName;
	char **environ;
	char **cmdBuffe;
	int lenAgrument;
	int errorCode;
	int isNonVide;
	int isEnvChanged;
	int execStatues;
	int CMDORAND;
	int filedesiptor;
	int historyNLines;
	unsigned int lCount;
	list_t *envLisst;
	list_t *history;
	list_t *alias;
} shellVarsStru;

#define INIT_VARS_SHELL \
{NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
	NULL, NULL, NULL}

/**
 *struct func_struct - contains a func_struct string ANDC related function
 *@command: the func_struct command flag
 *@func: the function
 */

typedef struct func_struct
{
	char *command;
	int (*func)(shellVarsStru *);
} func_node;

int isEqualsOne(char c, char *check);
int isInt(char *s);
int exitFunc(shellVarsStru *shellVars);
void handleBACKDIR(shellVarsStru *shellVars);
int handleCD(shellVarsStru *shellVars);
int printHistory(shellVarsStru *shellVars);
int printAl(list_t *alias);
int handleAliasCmd(shellVarsStru *shellVars);
int PrintCurrentEnv(shellVarsStru *shellVars);
char *getVariableOfEnv(shellVarsStru *shellVars, const char *name);
int removeVariableOfEnv(shellVarsStru *shellVars);
int setVarInEnv(shellVarsStru *shellVars);
void showError(shellVarsStru *shellVars, char *errorString);
int printErrorChar(char c);
void printError(char *str);
int writeToFd(char c, int file_dispotor);
int writeStringToFd(char *str, int file_dispotor);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *searchFirstOcc(char *s, char c);
char *converNumber(long int number, int base);
ssize_t readInput(char *buffer, size_t *i, shellVarsStru *shellVars);
int getLIneCustom(char **c_buffer, size_t *sizze, shellVarsStru *shellVars);
void newLineCmd(int sign);
ssize_t getLineee(char **buffer, size_t *len, shellVarsStru *shellVars);
ssize_t getLinee(shellVarsStru *shellVars);
char *getShellH(shellVarsStru *shellVars);
int addToHistFile(shellVarsStru *shellVars);
char **getEnvironVars(shellVarsStru *shellVars);
int setVarsEnvs(char *nameVar, char *valueVar, shellVarsStru *shellVars);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int n);
int delete_nodeint_at_index(list_t **head, unsigned int index);
size_t tortoiseAndHaret(const list_t *head);
void free_listint_safe(list_t **h);
size_t getLengthList(const list_t *h);
char **listString(list_t *head);
ssize_t get_node_index(list_t *head, list_t *currentNode);
list_t *getNodeSta(list_t *head, char *start, char c);
void freeTable(char **toFree);
void clearShellVasrs(shellVarsStru *shellVars, int clearr);
int isCommand(char *path);
char *getPath(char *pathDir, char *cammand);
char *_memset(char *s, char b, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int setCmdType(char *buffer, size_t *currentPos, shellVarsStru *ShVar);
int setAliasVar(shellVarsStru *ShVar);
void InitilizeShellVars(char **argvM, shellVarsStru *shellVars);
int executeCMD(char **argvM, shellVarsStru *shellVars);
int runUserCommand(shellVarsStru *shellVars);
void handleFork(shellVarsStru *shellVars);
void cmdINEnv(shellVarsStru *shellVars);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *findInS(const char *s, const char *toFind);
char *_strcat(char *dest, char *src);
char **strokCustom(char *str, char *d);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void putString(char *s);
int _putchar(char c);
int HlistBuild(char *buffer, int linecount, shellVarsStru *shellVars);

#endif

