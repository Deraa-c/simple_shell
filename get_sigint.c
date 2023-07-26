#include "alx.h"

/**
 * get_sigint - This handles the crtl + c call in prompt
 * @sig: This is the signal handler
 */

void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
