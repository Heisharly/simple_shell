#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - Create error message for 'permission denied' failing.
 * @args: arguments array passed to the command.
 *
 * Description:function to create error message
 * Return:error string.
 */
char *error_126(char **args)
{
	char *error, *hist_st;
	int le;

	hist_st = _itoa(hist);
	if (!hist_st)
		return (NULL);

	le = _strlen(name) + _strlen(hist_st) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (le + 1));
	if (!error)
	{
		free(hist_st);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_st);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_st);
	return (error);
}

/**
 * error_127 - Create an error message for 'command not found' failing.
 * @args: arguments array passed to command.
 *
 * Description:function to create error message
 * Return: error string.
 */
char *error_127(char **args)
{
	char *error, *hist_st;
	int le;

	hist_st = _itoa(hist);
	if (!hist_st)
		return (NULL);

	le = _strlen(name) + _strlen(hist_st) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (le + 1));
	if (!error)
	{
		free(hist_st);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_st);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_st);
	return (error);
}
