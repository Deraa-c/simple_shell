#include "alx.h"

/**
 * read_line - This reads the input string.
 *
 * @i_eof: This returns the value of getline function
 * Return: input string
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
