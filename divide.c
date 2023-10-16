#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
* token_len - Locates the delimiter index marking the end
*             of the first token contained within a string.
* @str: The string to be searched.
* @delim: The delimiter character.
* by: @Arlly and @Mohammed
* Return: The delimiter index marking the end of
*         the intitial token pointed to be string.
*/
int token_len(char *str, char *delim)
{
int index = 0, len = 0;

while (*(str + index) && *(str + index) != *delim)
{
len++;
index++;
}

return (len);
}

/**
* count_tokens - Counts the number of delimited
*                words contained within a string.
* @str: The string to be searched.
* @delim: The delimiter character.
*
* Return: The number of words contained within str.
*/
int count_tokens(char *str, char *delim)
{
int index, tokens = 0, len = 0;

for (index = 0; *(str + index); index++)
len++;

for (index = 0; index < len; index++)
{
if (*(str + index) != *delim)
{
tokens++;
index += token_len(str + index, delim);
}
}

return (tokens);
}

/**
* _strtok - Tokenizes a string.
* @line: The string.
* @delim: The delimiter character to tokenize the string by.
*
* Return: A pointer to an array containing the tokenized words.
*/
char **_strtok(char *line, char *delim)
{
char **ptr;
int index = 0, tokens, s, letters, n;

tokens = count_tokens(line, delim);
if (tokens == 0)
return (NULL);

ptr = malloc(sizeof(char *) * (tokens + 2));
if (!ptr)
return (NULL);

for (s = 0; s < tokens; s++)
{
while (line[index] == *delim)
index++;

letters = token_len(line + index, delim);

ptr[s] = malloc(sizeof(char) * (letters + 1));
if (!ptr[s])
{
for (index -= 1; index >= 0; index--)
free(ptr[index]);
free(ptr);
return (NULL);
}

for (n = 0; n < letters; n++)
{
ptr[s][n] = line[index];
index++;
}

ptr[s][n] = '\0';
}
ptr[s] = NULL;
ptr[s + 1] = NULL;

return (ptr);
}
