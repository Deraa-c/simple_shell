#include "alx.h"

/**
 * cd_shell - this changes current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int cd_shell(data_shell *datash)
{
	char *dir;
	int ish, ish2, isdash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		ish = _strcmp("$HOME", dir);
		ish2 = _strcmp("~", dir);
		isdash = _strcmp("--", dir);
	}

	if (dir == NULL || !ish || !ish2 || !isdash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
