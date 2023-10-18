#include "shell.h"

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

/**
 * help_all - Displays all possible commands.
 *
 * Description:a function to display all commands
 */
void help_all(void)
{
	char *ms = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, ms, _strlen(ms));
}

/**
 * help_alias - Display information of command 'alias'.
 *
 * Description:a function to display alias
 */
void help_alias(void)
{
	char *ms = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, ms, _strlen(ms));
}

/**
 * help_cd - Display information of command 'cd'.
 *
 * Description:a function to display cd
 */
void help_cd(void)
{
	char *ms = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "after a change of directory.\n";
	write(STDOUT_FILENO, ms, _strlen(ms));
}

/**
 * help_exit - Display information of command 'exit'.
 *
 * Description:a function to display exit
 */
void help_exit(void)
{
	char *ms = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = " exit 0.\n";
	write(STDOUT_FILENO, ms, _strlen(ms));
}

/**
 * help_help - Display information of command 'help'
 *
 * Description:a function to display help
 */
void help_help(void)
{
	char *ms = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, ms, _strlen(ms));
	ms = "builtin command.\n";
	write(STDOUT_FILENO, ms, _strlen(ms));
}
