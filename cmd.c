#include "main.h"

/**
 * printEnv - print current envirenment
 * @endCode: current exit code
*/

void printEnv(int *endCode)
{
	char **environe = environ;

	while (*environe != NULL)
	{
		write(STDOUT_FILENO, *environe, _strlen(*environe));
		write(STDOUT_FILENO, "\n", 1);
		environe++;
	}
	*endCode = EXIT_SUCCESS;
}

/**
 * exitProgram - end program
 * @inputCommand: user cmd
 * @argv: argv
 * @validPath: the path
 * @executeName: name of executable file
 * @Perror: Perror
 * @line_number: line_number
*/
int exitProgram(char *inputCommand, char ***argv, char **validPath, 
	char *executeName, int Perror, int line_number)
{
	int code;

	if (validPath[1])
	{
		code = _atoi(validPath[1]);
		if (code == -1)
		{
			code = 2;
			dynamicPrintError((enum ERROR_TYPE)NOVALID_PAR, 4, executeName,
								line_number, validPath[0], validPath[1]);
			return (code);
		}
		freeAllMat(argv);
		free(inputCommand);
		exit(code);
	}
	if (Perror == 0 || (isatty(STDIN_FILENO)
			&& Perror > 0))
	{
		freeAllMat(argv);
		free(inputCommand);
		exit(EXIT_SUCCESS);
	}
	else
	{
		return (Perror);
	}
}

/**
 * executeCommand - run command
 * @argv: matrix agrument
 * @executeName: name of executable file
 * @line_number: currnt line
 * Return: end Code to exit
*/
int executeCommand(char **argv, char *executeName, int line_number)
{
	int endCode, status;
	char *validPath;
	pid_t PID;

	validPath = getValidPath(argv[0]);
	if (validPath)
	{
		PID = fork();
		if (PID == -1)
			exit(EXIT_FAILURE);
		else if (PID == 0)
		{
			endCode = execve(validPath, argv, environ);
			if (endCode == -1)
			{
				perror("execve");
				exit(-1);
			}
		}
		else
		{
			waitpid(PID, &status, 0);
			if (WIFEXITED(status))
			{
				endCode = WEXITSTATUS(status);
				if (endCode != 0)
					endCode =  2;
			}
			else
				endCode = 3;
		}
	}
	else
	{
		dynamicPrintError((enum ERROR_TYPE)NO_PATH, 3, executeName,
						line_number, argv[0]);
		endCode = 127;
	}

	return (endCode);
}

/**
 * runCmd - runCmd
 * @executeName: name of executable file
 * @inputCommand: inputCommand
 * @argv: matrix agrument
 * @endCode: end Code to exit
*/
void runCmd(char *executeName, char *inputCommand, char ***argv, int *endCode)
{
	int i;
	char *validPath;

	if (argv != NULL && executeName != NULL)
	{
		for (i = 0; argv[i] != NULL; i++)
		{
			validPath = argv[i][0];
			if (_strcmp(validPath, EXIT) == 0)
			{
				*endCode = exitProgram(inputCommand, argv, argv[i], executeName,
											*endCode, i+1);
			}
			else if (_strcmp(validPath, ENVIREN) == 0)
			{
				printEnv(endCode);
			}
			else
			{
				*endCode = executeCommand(argv[i], executeName, i + 1);
			}
		}
		freeAllMat(argv);
	}
}

