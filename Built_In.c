#include "shell.h"
int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - Matche command with one corresponding
 *               shellby Built in Function.
 * @command: Command to do the match.
 *
 * Description:a function to match command
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "setenv", shellby_setenv },
		{ "unsetenv", shellby_unsetenv },
		{ "cd", shellby_cd },
		{ "alias", shellby_alias },
		{ "help", shellby_help },
		{ NULL, NULL }
	};
	int k;

	for (k = 0; funcs[k].name; k++)
	{
		if (_strcmp(funcs[k].name, command) == 0)
			break;
	}
	return (funcs[k].f);
}

/**
 * shellby_exit - Cause a process terminat
 *                for shellby shell.
 * @args: arguments inside of an array.
 * @front: Double pointer the beginning of args.
 *
 * Description:a function that cause a trmination
 * Return: If  no arguments - -3.
 *         If Exit value invalid - 2.
 *         O/w - Exits with the status value
 */
int shellby_exit(char **args, char **front)
{
	int k, len_int = 10;
	unsigned int nu = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			k = 1;
			len_int++;
		}
		for (; args[0][k]; k++)
		{
			if (k <= len_int && args[0][k] >= '0' && args[0][k] <= '9')
				nu = (nu * 10) + (args[0][k] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (nu > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(nu);
}

/**
 * shellby_cd - Change current directory of shellby process.
 * @args:arugments inside array.
 * @front:double pointer to beginning of args.
 *
 * Description:a function that change directory
 * Return: If the given string not a directory - 2.
 *         If error occurs - -1.
 *         Other - 0.
 */
int shellby_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpw = NULL, *pw = NULL;
	struct stat dir;

	oldpw = getcwd(oldpw, 0);
	if (!oldpw)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpw);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpw);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pw = getcwd(pw, 0);
	if (!pw)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpw;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pw;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pw, _strlen(pw));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpw);
	free(pw);
	free(dir_info);
	return (0);
}

/**
 * shellby_help - Display information of the shellby built in command.
 * @args: arguments in array.
 * @front: pointer for the array beginning.
 *
 * Description:a function that display information
 * Return: If error occurs then -1.
 *         Other - 0.
 */
int shellby_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
