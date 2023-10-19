#include "shell.h"

char *fill_path_dir(char *pat);
list_t *get_path_dir(char *pat);

/**
* get_location - Locates a command in the PATH.
* @command:command to locate.
*
* Return: If an error occurs or the command cannot be located - NULL.
*         Otherwise - the full pathname of the command.
*/
char *get_location(char *command)
{
char **pat, *tem;
list_t *dirs, *head;
struct stat st;

pat = _getenv("PATH");
if (!pat || !(*pat))
return (NULL);

dirs = get_path_dir(*pat + 5);
head = dirs;

while (dirs)
{
tem = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
if (!tem)
return (NULL);

_strcpy(tem, dirs->dir);
_strcat(tem, "/");
_strcat(tem, command);

if (stat(tem, &st) == 0)
{
free_list(head);
return (tem);
}

dirs = dirs->next;
free(tem);
}

free_list(head);

return (NULL);
}

/**
* fill_path_dir - Copies path but also replaces leading/sandwiched/trailing
*   colons (:) with current working directory.
* @path: The colon-separated list of directories.
*
* Return: A copy of path with any leading/sandwiched/trailing colons replaced
*   with the current working directory.
*/
char *fill_path_dir(char *pat)
{
int v, lengt = 0;
char *path_copy, *pwd;

pwd = *(_getenv("PWD")) + 4;
for (v = 0; pat[v]; v++)
{
if (pat[v] == ':')
{
if (pat[v + 1] == ':' || v == 0 || pat[v + 1] == '\0')
lengt += _strlen(pwd) + 1;
else
lengt++;
}
else
lengt++;
}
path_copy = malloc(sizeof(char) * (lengt + 1));
if (!path_copy)
return (NULL);
path_copy[0] = '\0';
for (v = 0; pat[v]; v++)
{
if (pat[v] == ':')
{
if (v == 0)
{
_strcat(path_copy, pwd);
_strcat(path_copy, ":");
}
else if (pat[v + 1] == ':' || pat[v + 1] == '\0')
{
_strcat(path_copy, ":");
_strcat(path_copy, pwd);
}
else
_strcat(path_copy, ":");
}
else
{
_strncat(path_copy, &pat[v], 1);
}
}
return (path_copy);
}

/**
* get_path_dir - Tokenizes a colon-separated list of
*                directories into a list_s linked list.
* @path: The colon-separated list of directories.
*
* Return: A pointer to the initialized linked list.
*/
list_t *get_path_dir(char *pat)
{
int inde;
char **dirs, *path_copy;
list_t *head = NULL;

path_copy = fill_path_dir(pat);
if (!path_copy)
return (NULL);
dirs = _strtok(path_copy, ":");
free(path_copy);
if (!dirs)
return (NULL);

for (inde = 0; dirs[inde]; inde++)
{
if (add_node_end(&head, dirs[inde]) == NULL)
{
free_list(head);
free(dirs);
return (NULL);
}
}

free(dirs);

return (head);
}
