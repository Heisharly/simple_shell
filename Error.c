#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - Count digit length of number.
 * @num: measuring number.
 *
 * Return:digit length.
 */
int num_len(int num)
{
	unsigned int nu1;
	int le = 1;

	if (num < 0)
	{
		le++;
		nu1 = num * -1;
	}
	else
	{
		nu1 = num;
	}
	while (nu1 > 9)
	{
		le++;
		nu1 /= 10;
	}

	return (le);
}

/**
 * _itoa - Convert integer to string.
 * @num: Integer.
 *
 * Description:a function to convert integer to sting
 * Return:Converted string.
 */
char *_itoa(int num)
{
	char *buffer;
	int le = num_len(num);
	unsigned int nu1;

	buffer = malloc(sizeof(char) * (le + 1));
	if (!buffer)
		return (NULL);

	buffer[le] = '\0';

	if (num < 0)
	{
		nu1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		nu1 = num;
	}

	le--;
	do {
		buffer[le] = (nu1 % 10) + '0';
		nu1 /= 10;
		le--;
	} while (nu1 > 0);

	return (buffer);
}


/**
 * create_error - Write custom error message to stderr.
 * @args: arguments arrays.
 * @err: value of error.
 *
 * Description:a function to write custom error message
 * Return:Error value.
 */
int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
