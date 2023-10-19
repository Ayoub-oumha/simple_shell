#ifndef _simple_shell_
#define _simple_shell_
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define EXIT "exit"
#define ENVIREN "env"
#define LS "ls"
#define spaceChar  " "
#define newLineChar  "\n"
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define EXIT_INVALID 2

extern char **environ;

/**
 * enum ERROR_TYPE - error types
 * @NO_PATH: no file found
 * @NOVALID_PAR: invalid parametre
 * @MAX_CODE: max number in error
 * Description: array of types
*/
typedef enum ERROR_TYPE
{
	NO_PATH = 0,
	NOVALID_PAR = 1,
	ERROR_MALLOC = 2,
	MAX_CODE
} ERROR_TYPE;

/**
* struct ERROR_TEXT - struct of error text
* @type: type of error
* @text: text
* Description: struct of text of errror
*/
typedef struct ERROR_TEXT
{
	enum ERROR_TYPE type;
	char *text;
} ERROR_TEXT;

void dynamicPrintError(enum ERROR_TYPE ERROR_TYPE, int argc, ...);
void clearPointers(int argc, ...);
void free_matrix(char **mat);
void runCmd(char *executeName, char *inputCommand, char ***argv, int *endCode);
int exitProgram(char *inputCommand, char ***argv, char **validPath,
	char *executeName, int Perror, int line_number);
void printEnv(int *endCode);
char ***getCommands(char *commandLine);
char *getValidPath(char *line);
void freeAllMat(char ***mat);
void freeMartArgV(char ***argv, int len);
char *getEnv(char *varEn);
char *_memset(char *s, char b, unsigned int n);
char *_itos(int number);
char *_strdup(char *str);
int _atoi(char *s);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);

#endif

