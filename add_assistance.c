#include "shell.h"

char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);

/**
* get_args - Gets a command from standard input.
* @line: A buffer to store the command.
* @exe_ret: The return value of the last executed command.
* by: @Arlly and Mohammed
* Return: If an error occur - NULL.
*         Otherwise - return pointer to the stored command.
*/
char *get_args(char *line, int *exe_ret)
{
size_t v = 0;
ssize_t rea;
char *prompt = "$ ";

if (line)
free(line);

rea = _getline(&line, &v, STDIN_FILENO);
if (rea == -1)
return (NULL);
if (rea == 1)
{
hist++;
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, prompt, 2);
return (get_args(line, exe_ret));
}

line[rea - 1] = '\0';
variable_replacement(&line, exe_ret);
handle_line(&line, rea);

return (line);
}

/**
* call_args - Partitions operators from commands and calls them.
* @args: An array of arguments.
* @front: A double pointer to the beginning of args.
* @exe_ret: The return value of the parent process' last executed command.
*
* Return: The return value of last executed command.
*/
int call_args(char **args, char **front, int *exe_ret)
{
int re, inde;

if (!args[0])
return (*exe_ret);
for (inde = 0; args[inde]; inde++)
{
if (_strncmp(args[inde], "||", 2) == 0)
{
free(args[inde]);
args[inde] = NULL;
args = replace_aliases(args);
re = run_args(args, front, exe_ret);
if (*exe_ret != 0)
{
args = &args[++inde];
inde = 0;
}
else
{
for (inde++; args[inde]; inde++)
free(args[inde]);
return (re);
}
}
else if (_strncmp(args[inde], "&&", 2) == 0)
{
free(args[inde]);
args[inde] = NULL;
args = replace_aliases(args);
re = run_args(args, front, exe_ret);
if (*exe_ret == 0)
{
args = &args[++inde];
inde = 0;
}
else
{
for (inde++; args[inde]; inde++)
free(args[inde]);
return (re);
}
}
}
args = replace_aliases(args);
re = run_args(args, front, exe_ret);
return (re);
}

/**
 * run_args - Calls the execution of a command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_args(char **args, char **front, int *exe_ret)
{
int re, x;
int (*builtin)(char **args, char **front);

builtin = get_builtin(args[0]);

if (builtin)
{
re = builtin(args + 1, front);
if (re != EXIT)
*exe_ret = re;
}
else
{
*exe_ret = execute(args, front);
re = *exe_ret;
}

hist++;

for (x = 0; args[x]; x++)
free(args[x]);

return (re);
}

/**
 * handle_args - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_args(int *exe_ret)
{
int re = 0, inde;
char **args, *line = NULL, **front;

line = get_args(line, exe_ret);
if (!line)
return (END_OF_FILE);

args = _strtok(line, " ");
free(line);
if (!args)
return (re);
if (check_args(args) != 0)
{
*exe_ret = 2;
free_args(args, args);
return (*exe_ret);
}
front = args;

for (inde = 0; args[inde]; inde++)
{
if (_strncmp(args[inde], ";", 1) == 0)
{
free(args[inde]);
args[inde] = NULL;
re = call_args(args, front, exe_ret);
args = &args[++inde];
inde = 0;
}
}
if (args)
re = call_args(args, front, exe_ret);

free(front);
return (re);
}

/**
* check_args - Checks if there are any leading ';', ';;', '&&', or '||'.
* @args: 2D pointer to tokenized commands and arguments.
*
* Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
*   Otherwise - 0.
*/
int check_args(char **args)
{
size_t v;
char *cur, *nex;

for (v = 0; args[v]; v++)
{
cur = args[v];
if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
{
if (v == 0 || cur[1] == ';')
return (create_error(&args[v], 2));
nex = args[v + 1];
if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
return (create_error(&args[v + 1], 2));
}
}
return (0);
}
