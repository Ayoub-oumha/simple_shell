#include "main.h"

const ERROR_TEXT errorArray[] = {
	{NO_PATH, "%s: %d: %s: No such file or directory\n"},
	{NOVALID_PAR, "%s: %d: %s: Illegal Command: %s\n"},
	{ERROR_MALLOC, "%s: %d: %s: Can't Allocate: %s\n"}
};

/**
 * printfError - print error
 * @ERROR_TYPE: error type
 * @argError: list of parametr
*/

void printfError(enum ERROR_TYPE ERROR_TYPE, va_list argError)
{
	char *toPrint = malloc(1024), *finalMessage = malloc(1024);
	int i = 0, len = 0;
	char *addString = NULL;
	int int_value;

	if (toPrint != NULL && finalMessage != NULL)
	{
		_memset(finalMessage, 0, 1024);
		_strcpy(toPrint, errorArray[ERROR_TYPE].text);
		while (toPrint[i] != '\0')
		{
			if (toPrint[i] == '%')
			{
				if (toPrint[i + 1] == 'd')
				{
					int_value = va_arg(argError, int);
					addString = _itos(int_value);
				}
				else if (toPrint[i + 1] == 's')
				{
					addString = va_arg(argError, char *);
				}
				finalMessage = strcat(finalMessage, addString);
				i += 2;
			}
			else if (toPrint[i] != '%')
			{
				len = _strlen(finalMessage);
				finalMessage[len] = toPrint[i];
				i++;
			}
		}
		va_end(argError);
		write(STDERR_FILENO, finalMessage, _strlen(finalMessage));
		free(finalMessage);
		free(toPrint);
	}
}

/**
* dynamicPrintError - print error can take more inputs
* @ERROR_TYPE: error type in number
* @argc: number of other inputs
*/

void dynamicPrintError(enum ERROR_TYPE ERROR_TYPE, int argc, ...)
{
	va_list argError;

	if ((int)ERROR_TYPE >= 0 && (int)ERROR_TYPE < MAX_CODE)
	{
		if (argc > 0)
		{
			va_start(argError, argc);
			printfError(ERROR_TYPE, argError);
			va_end(argError);
		}
		else
		{
			write(STDERR_FILENO, errorArray[ERROR_TYPE].text,
				  _strlen(errorArray[ERROR_TYPE].text));
		}
	}
}

