#include "alx.h"

/**
 * cmp_env_name - This compares the env variables names
 * with the name passed.
 * @nenv: This is the name of the environment variable
 * @name: This is the name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */

int cmp_env_name(const char *nenv, const char *name)
{
	int u;

	for (u = 0; nenv[u] != '='; u++)
	{
		if (nenv[u] != name[u])
		{
			return (0);
		}
	}

	return (u + 1);
}

/**
 * _getenv - This gets an environment variable
 * @name: This is the name of the environment variable
 * @_environ: This is the environment variable
 *
 * Return: Returns value of the environment variable if is found.
 * In other case, returns NULL.
 */

char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int u, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (u = 0; _environ[u]; u++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(_environ[u], name);
		if (mov)
		{
			ptr_env = _environ[u];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */

int _env(data_shell *datash)
{
	int u, b;

	for (u = 0; datash->_environ[u]; u++)
	{
		for (b = 0; datash->_environ[u][b]; b++)
			;

		write(STDOUT_FILENO, datash->_environ[u], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
