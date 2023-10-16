#include "main.h"

/**
* clearPointers - free all variable
* @argc: number of agruments
*/

void clearPointers(int argc, ...)
{
	if (argc > 0)
	{
		int i = 0;

		va_list agruments;
		void **vari;

		va_start(agruments, argc);
		while (i < argc)
		{
			vari = va_arg(agruments, void **);
			if (*vari != NULL)
			{
				free(*vari);
				*vari = NULL;
			}
			i++;
		}
		va_end(agruments);
	}
}

/**
 * freeAllMat - free argv
 * @mat: matr
*/
void freeAllMat(char ***mat)
{
	char ***matPo = NULL;
	char **cell = NULL;
	char **cellPointer = NULL;

	if (mat == NULL)
		return;
	matPo = mat;
	while (*matPo != NULL)
	{
		cell = *matPo;
		if (cell != NULL)
		{
			cellPointer = cell;
			while (*cellPointer != NULL)
			{
				free(*cellPointer);
				cellPointer++;
			}
			free(cell);
		}
		matPo++;
	}
	free(mat);
}

/**
 * freeMartArgV - free matrix
 * @argv: matrix
 * @len: number of rows
*/
void freeMartArgV(char ***argv, int len)
{
	int i = 0;

	for (i = 0; i < len; i++)
	{
		free(argv[i]);
	}
	free(argv);
	argv = NULL;
}
