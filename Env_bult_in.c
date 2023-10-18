#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - Print Current Environments.
 * @args: arguments inside of array passed to shell.
 * @front: Double pointer to start of args.
 *
 * Description:a function to print environments
 * Return: error occurs - -1.
 *	   Or - 0.
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int inde;
	char n = '\n';

	if (!environ)
		return (-1);

	for (inde = 0; environ[inde]; inde++)
	{
		write(STDOUT_FILENO, environ[inde], _strlen(environ[inde]));
		write(STDOUT_FILENO, &n, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - Change or add  environmental variable to PATH.
 * @args: arguments inside array pass to shell.
 * @front: double pointer to start of args.
 *
 * Description:a function to change or add to variables
 * Return: error occurs - -1.
 *         Or - 0.
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t siz;
	int inde;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (siz = 0; environ[siz]; siz++)
		;

	new_environ = malloc(sizeof(char *) * (siz + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (inde = 0; environ[inde]; inde++)
		new_environ[inde] = environ[inde];

	free(environ);
	environ = new_environ;
	environ[inde] = new_value;
	environ[inde + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - erase an environmental variable from PATH.
 * @args: arguments inside array that passed to shell.
 * @front: Double pointer to beginning of args.
 *
 * Descriptio: a function to erase environmantal
 * Return: error occur - -1.
 *         Or - 0.
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t siz;
	int inde, inde2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (siz = 0; environ[siz]; siz++)
		;

	new_environ = malloc(sizeof(char *) * siz);
	if (!new_environ)
		return (create_error(args, -1));

	for (indx = 0, inde2 = 0; environ[inde]; inde++)
	{
		if (*env_var == environ[inde])
		{
			free(*env_var);
			continue;
		}
		new_environ[inde2] = environ[inde];
		inde2++;
	}
	free(environ);
	environ = new_environ;
	environ[siz - 1] = NULL;

	return (0);
}
