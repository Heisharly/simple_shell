#include "shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env - Display information of command 'env'.
 *
 * Description:a function to display env
 */
void help_env(void)
{
	char *ms = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, ms, _strlen(ms));
}

/**
 * help_setenv - Display information on command 'setenv'.
 *
 * Description:a function to display setenv information
 */
void help_setenv(void)
{
	char *ms = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, ms, _strlen(ms));
}

/**
 * help_unsetenv - Display information on command unsetenv
 *
 * Description: function to display unsetenv commands
 */
void help_unsetenv(void)
{
	char *ms = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "message to stderr.\n";
	write(STDOUT_FILENO, ms, _strlen(ms));
}
