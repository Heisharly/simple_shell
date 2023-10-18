#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t siz;
	int inde;

	for (siz = 0; environ[siz]; siz++)
		;

	new_environ = malloc(sizeof(char *) * (siz + 1));
	if (!new_environ)
		return (NULL);

	for (inde = 0; environ[inde]; inde++)
	{
		new_environ[inde] = malloc(_strlen(environ[inde]) + 1);

		if (!new_environ[inde])
		{
			for (inde--; inde >= 0; inde--)
				free(new_environ[inde]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[inde], environ[inde]);
	}
	new_environ[inde] = NULL;

	return (new_environ);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int inde;

	for (inde = 0; environ[inde]; inde++)
		free(environ[inde]);
	free(environ);
}

/**
 * _getenv - get environmental variable from PATH.
 * @var: name of environmental variable to get.
 *
 * Description:function to get variable
 * Return: environmental variable do not exist - NULL.
 *         Or - pointer to Environmental variable.
 */
char **_getenv(const char *var)
{
	int inde, le;

	le = _strlen(var);
	for (inde = 0; environ[inde]; inde++)
	{
		if (_strncmp(var, environ[inde], le) == 0)
			return (&environ[inde]);
	}

	return (NULL);
}
