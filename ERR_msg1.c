#include "shell.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
/**
 * error_env - Create an error message for shellbyenv error.
 * @args:arguments array passed to the command.
 *
 * Description:a function to create error message
 * Return: error string.
 */
char *error_env(char **args)
{
	char *error, *hist_st;
	int le;

	hist_st = _itoa(hist);
	if (!hist_st)
		return (NULL);

	args--;
	le = _strlen(name) + _strlen(hist_st) + _strlen(args[0]) + 45;
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
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_st);
	return (error);
}

/**
 * error_1 - Create error message for shellbyalias error.
 * @args: arguments array  passed to the command.
 *
 * Description:a function that create error message
 * Return: error string.
 */
char *error_1(char **args)
{
	char *error;
	int le;

	le = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (le + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - Create error message for shellbyexit error.
 * @args:arguments array that  passed to the command.
 *
 * Description:function to create error message
 * Return:error string.
 */
char *error_2_exit(char **args)
{
	char *error, *hist_st;
	int le;

	hist_st = _itoa(hist);
	if (!hist_st)
		return (NULL);

	le = _strlen(name) + _strlen(hist_st) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (le + 1));
	if (!error)
	{
		free(hist_st);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_st);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist_st);
	return (error);
}

/**
 * error_2_cd - Create error message for shellbycd error.
 * @args:arguments array that is passed to the command.
 *
 * Description:error message for shellbycd
 * Return:error string.
 */
char *error_2_cd(char **args)
{
	char *error, *hist_st;
	int le;

	hist_st = _itoa(hist);
	if (!hist_st)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist_st);
	return (error);
}

/**
 * error_2_syntax - Create error message for syntax error.
 * @args: arguments inside passed to the command.
 *
 * Description:function to create error message
 * Return:error string.
 */
char *error_2_syntax(char **args)
{
	char *error, *hist_st;
	int le;

	hist_st = _itoa(hist);
	if (!hist_st)
		return (NULL);

	le = _strlen(name) + _strlen(hist_st) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (le + 1));
	if (!error)
	{
		free(hist_st);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_st);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(hist_st);
	return (error);
}
