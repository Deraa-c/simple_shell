#include "alx.h"

/**
 * _strdup - This duplicates a str in the heap memory.
 * @s: This is a Type char pointer str
 *
 * Return: Returns duplicated str
 */

char *_strdup(const char *s)
{
	char *fox;
	size_t fix;

	fix = _strlen(s);
	fox = malloc(sizeof(char) * (fix + 1));
	if (fox == NULL)
		return (NULL);
	_memcpy(fox, s, fix + 1);
	return (fox);
}

/**
 * _strlen - This returns the lenght of a string.
 * @s: This is the type char pointer
 * Return: This is always 0.
 */

int _strlen(const char *s)
{
	int fix;

	for (fix = 0; s[fix] != 0; fix++)
	{
	}
	return (fix);
}

/**
 * cmp_chars - This compares chars of strings
 * @str: This is the input string.
 * @delim: This is a delimiter.
 *
 * Return: Returns 1 if equals and 0 if not.
 */

int cmp_chars(char str[], const char *delim)
{
	unsigned int u, b, k;

	for (u = 0, k = 0; str[u]; u++)
	{
		for (b = 0; delim[b]; b++)
		{
			if (str[u] == delim[b])
			{
				k++;
				break;
			}
		}
	}
	if (u == k)
		return (1);
	return (0);
}

/**
 * _strtok - This splits a string by some delimiter.
 * @str: This is the input string.
 * @delim: This is a delimiter.
 *
 * Return: This returns the splited string.
 */

char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int u, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /*Store first address*/
		u = _strlen(str);
		str_end = &str[u]; /*Store last address*/
	}
	str_start = splitted;
	if (str_start == str_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (u = 0; delim[u]; u++)
		{
			if (*splitted == delim[u])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - This defines if string passed is a number
 *
 * @s: This is the input string
 * Return: Returns 1 if string is a number. 0 in other case.
 */

int _isdigit(const char *s)
{
	unsigned int u;

	for (u = 0; s[u]; u++)
	{
		if (s[u] < 48 || s[u] > 57)
			return (0);
	}
	return (1);
}
