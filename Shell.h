#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define delim " \t\r\n\a\""
#define MAX_INPUT_SIZE 1024
extern char **environ;

char *_getCommand(void);
char **tokenCmd(char *line);
int execute(char **cmd, char **av);
ssize_t _getline(char **line, size_t *buffsize, FILE *stream);
void Comments(char ***cmd);

char *_env(char *args);
int _exxit_sh(char **toks, char *buff);
void _puts(char *str);
int _atoi(char *ptr);

void freeBuff(char **buff);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(const char *str);

int _putchar(char c);

#endif
