#include "shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line from standard input.
 * @read: The length of line.
 * by: @Arlly and Mohammed
 * Descriptions: Spaces are input to separate ";", "||", and "&&".
 *              Replaces the symbol "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
char *old_line, *new_line;
char previous, current, next;
size_t j, k;
ssize_t new_len;

new_len = get_new_len(*line);
if (new_len == read - 1)
return;
new_line = malloc(new_len + 1);
if (!new_line)
return;
k = 0;
old_line = *line;
for (j = 0; old_line[j]; j++)
{
current = old_line[j];
next = old_line[j + 1];
if (j != 0)
{
previous = old_line[j - 1];
if (current == ';')
{
if (next == ';' && previous != ' ' && previous != ';')
{
new_line[k++] = ' ';
new_line[k++] = ';';
continue;
}
else if (previous == ';' && next != ' ')
{
new_line[k++] = ';';
new_line[k++] = ' ';
continue;
}
if (previous != ' ')
new_line[k++] = ' ';
new_line[k++] = ';';
if (next != ' ')
new_line[k++] = ' ';
continue;
}
else if (current == '&')
{
if (next == '&' && previous != ' ')
new_line[k++] = ' ';
else if (previous == '&' && next != ' ')
{
new_line[k++] = '&';
new_line[k++] = ' ';
continue;
}
}
else if (current == '|')
{
if (next == '|' && previous != ' ')
new_line[k++]  = ' ';
else if (previous == '|' && next != ' ')
{
new_line[k++] = '|';
new_line[k++] = ' ';
continue;
}
}
}
else if (current == ';')
{
if (j != 0 && old_line[j - 1] != ' ')
new_line[k++] = ' ';
new_line[k++] = ';';
if (next != ' ' && next != ';')
new_line[k++] = ' ';
continue;
}
new_line[k++] = old_line[j];
}
new_line[k] = '\0';

free(*line);
*line = new_line;
}

/**
 * get_new_len - Gets the new length of the line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: line to check.
 *
 * Return: New length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
size_t j;
ssize_t new_len = 0;
char current, next;

for (j = 0; line[j]; j++)
{
current = line[j];
next = line[j + 1];
if (current == '#')
{
if (j == 0 || line[j - 1] == ' ')
{
line[j] = '\0';
break;
}
}
else if (j != 0)
{
if (current == ';')
{
if (next == ';' && line[j - 1] != ' ' && line[j - 1] != ';')
{
new_len += 2;
continue;
}
else if (line[j - 1] == ';' && next != ' ')
{
new_len += 2;
continue;
}
if (line[j - 1] != ' ')
new_len++;
if (next != ' ')
new_len++;
}
else
logical_ops(&line[j], &new_len);
}
else if (current == ';')
{
if (j != 0 && line[j - 1] != ' ')
new_len++;
if (next != ' ' && next != ';')
new_len++;
}
new_len++;
}
return (new_len);
}
/**
* logical_ops - Checks a line for logical operators "||" or "&&".
* @line: A pointer to the character to check in the line.
* @new_len: Pointer to new_len in get_new_len function.
*/
void logical_ops(char *line, ssize_t *new_len)
{
char previous, current, next;

previous = *(line - 1);
current = *line;
next = *(line + 1);

if (current == '&')
{
if (next == '&' && previous != ' ')
(*new_len)++;
else if (previous == '&' && next != ' ')
(*new_len)++;
}
else if (current == '|')
{
if (next == '|' && previous != ' ')
(*new_len)++;
else if (previous == '|' && next != ' ')
(*new_len)++;
}
}
