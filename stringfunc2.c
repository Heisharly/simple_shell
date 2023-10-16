#include "shell.h"

char *_strchr(char *p, char b);
int _strspn(char *p, char *accept);
int _strcmp(char *p1, char *p2);
int _strncmp(const char *p1, const char *p2, size_t m);

/**
* _strchr - find a character in a string.
* @p: string to be searched.
* @b: character to be located.
* by: @Arlly and @Mohammed
* Return: If b is found - a pointer to the first occurence.
*         If b is not found - NULL.
*/
char *_strchr(char *p, char b)
{
int index;

for (index = 0; p[index]; index++)
{
if (p[index] == b)
return (s + index);
}

return (NULL);
}

/**
* _strspn - find the length of a prefix substring.
* @p:  string to be searched.
* @accept:  prefix to be measured.
*
* Return: The number of bytes in s which
*         consist only of bytes from accept.
*/
int _strspn(char *p, char *accept)
{
int bytes = 0;
int index;

while (*p)
{
for (index = 0; accept[index]; index++)
{
if (*p == accept[index])
{
bytes++;
break;
}
}
p++;
}
return (bytes);
}

/**
* _strcmp - Compares two strings.
* @p1:  first string to be compared.
* @p2:  second string to be compared.
*
* Return: Positive byte difference if p1 > p2
*         0 if p1 = p2
*         Negative byte difference if p1 < p2
*/
int _strcmp(char *p1, char *p2)
{
while (*p1 && *p2 && *p1 == *p2)
{
p1++;
p2++;
}

if (*p1 != *p2)
return (*p1 - *p2);

return (0);
}

/**
* _strncmp - Compare two strings.
* @p1: Pointer to a string.
* @p2: Pointer to a string.
* @m: The first n bytes of the strings to compare.
* by: @Arlly and mohammed
* Return: Less than 0 if p1 is shorter than p2.
*         0 if p1 and p2 match.
*         Greater than 0 if s1 is longer than p2.
*/
int _strncmp(const char *p1, const char *p2, size_t m)
{
size_t j;

for (j = 0; p1[j] && p2[j] && j < m; j++)
{
if (p1[j] > p2[j])
return (p1[j] - p2[j]);
else if (p1[j] < p2[j])
return (p1[j] - p2[j]);
}
if (j == m)
return (0);
else
return (-15);
}
