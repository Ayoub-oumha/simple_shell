#include "main.h"
/**
 * getEnv - get specefic variable from env
 * @varEn: name of variable
 * Return: value of variable
 */

char *getEnv(char *varEn)
{
	int len, i = 0, j = 0;
	char *envir;

	for (; environ[i] != NULL; ++i)
	{
		envir = environ[i];
		len = _strlen(varEn);
		for (j = 0; j < len; j++)
		{
			if (envir[j] != varEn[j])
				break;
		}
		if (j == len && envir[j] == '=')
		{
			return (envir + j + 1);
		}
	}
	return (NULL);
}

/**
 * getValidPath - get valide path
 * @line: location
 * Return: final path
 */

char *getValidPath(char *line)
{
	char *path, *pathDup, *pathSplit, *file_path;
	size_t cmdLen, splitLen;
	struct stat envir;

	if (stat(line, &envir) == 0)
		return line;
	cmdLen = _strlen(line);
	path = getEnv("PATH");
	pathDup = strdup(path);
	pathSplit = strtok(pathDup, ":");
	while(pathSplit)
	{
		splitLen = _strlen(pathSplit);
		file_path = malloc(splitLen + cmdLen + 2);
		if (file_path == NULL)
		{
			free(pathDup);
			perror("Memory allocated error");
			exit(1);
		}
		_strcpy(file_path, pathSplit);
		strcat(file_path, "/");
		strcat(file_path, line);
		strcat(file_path, "\0");
		if (stat(file_path, &envir) == 0)
		{
			free(pathDup);
			return (file_path);
		}
		else
		{
			free(file_path);
			pathSplit = strtok (NULL, ":");
		}
	}
	free(pathDup);
	return (NULL);
}

