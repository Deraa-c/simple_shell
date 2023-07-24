#include "alx.h"

/**
 * exit_shell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(data_shell *datash)
{
	unsigned int mystatus;
	int digit;
	int str_len;
	int a_number;

	if (datash->args[1] != NULL)
	{
		mystatus = _atoi(datash->args[1]);
		digit = _isdigit(datash->args[1]);
		str_len = _strlen(datash->args[1]);
		a_number = mystatus > (unsigned int)INT_MAX;
		if (digit || str_len > 10 || a_number)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (mystatus % 256);
	}
	return (0);
}
