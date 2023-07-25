#include "alx.h"

/**
 * check_env- this checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, q, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (q = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, q, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[q] == _envr[row][chr])
				q++;
			else
				break;
		}
	}

	for (q = 0; in[q]; q++)
	{
		if (in[q] == ' ' || in[q] == '\t' || in[q] == ';' || in[q] == '\n')
			break;
	}

	add_rvar_node(h, q, NULL, 0);
}

/**
 * check_vars - this checks if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input strings
 * @st: contain last status of the Shell
 * @data: displays data structure
 * Return: no return
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int cia, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (cia = 0; in[cia]; cia++)
	{
		if (in[cia] == '$')
		{
			if (in[cia + 1] == '?')
				add_rvar_node(h, 2, st, lst), cia++;
			else if (in[cia + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), cia++;
			else if (in[cia + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[cia + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[cia + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[cia + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[cia + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + cia, data);
		}
	}

	return (cia);
}

/**
 * replaced_input - this replaces string into variables
 *
 * @head: head of the linked list
 * @input: input strings
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int a, b, c;

	indx = *head;
	for (b = a = 0; a < nlen; a++)
	{
		if (input[b] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[a] = input[b];
				b++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (c = 0; c < indx->len_var; c++)
					b++;
				a--;
			}
			else
			{
				for (c = 0; c < indx->len_val; c++)
				{
					new_input[a] = indx->val[c];
					a++;
				}
				b += (indx->len_var);
				a--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[a] = input[b];
			b++;
		}
	}

	return (new_input);
}

/**
 * rep_var - this calls functions to replace string into vars
 *
 * @input: input strings
 * @datash: data structure
 * Return: replaced string
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
