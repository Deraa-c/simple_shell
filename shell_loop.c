#include "alx.h"

/**
 * without_comment - This deletes comments from the input
 *
 * @in: This inputs string
 * Return: input without comments
 */

char *without_comment(char *in)
{
	int u, up_to;

	up_to = 0;
	for (u = 0; in[u]; u++)
	{
		if (in[u] == '#')
		{
			if (u == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[u - 1] == ' ' || in[u - 1] == '\t' || in[u - 1] == ';')
				up_to = u;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, u, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - This is the Loop of shell
 * @datash: This is relevant data (av, input, args)
 *
 * Return: no return.
 */

void shell_loop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
