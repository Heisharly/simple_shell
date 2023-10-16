#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
* _strlen - Returns length of a string.
* @s: A pointer to the characters string.
* by: @Arlly and Mohammed
* Return:length of the character string.
*/
int _strlen(const char *s)
{
int length = 0;

if (!s)
return (length);
for (length = 0; s[length]; length++)
;
return (length);
}

/**
* _strcpy - Copies the string pointed to by src, including the
*           terminating null byte, to the buffer pointed by des.
* @dest: Pointer to the destination of copied string.
* @src: Pointer to the src of the source string.
*
* Return: Pointer to dest.
*/
char *_strcpy(char *dest, const char *src)
{
size_t j;

for (j = 0; src[j] != '\0'; j++)
dest[j] = src[j];
dest[j] = '\0';
return (dest);
}

/**
* _strcat - Concantenates two strings.
* @dest: Pointer to destination string.
* @src: Pointer to source string.
*
* Return: Pointer to destination string.
*/
char *_strcat(char *dest, const char *src)
{
char *destTemp;
const char *srcTemp;

destTemp = dest;
srcTemp =  src;

while (*destTemp != '\0')
destTemp++;

while (*srcTemp != '\0')
*destTemp++ = *srcTemp++;
*destTemp = '\0';
return (dest);
}

/**
* _strncat - Concantenates two strings where n number
*            of bytes are copied from source.
* @dest: Pointer to destination string.
* @src: Pointer to source string.
* @m: m bytes to copy from src.
*
* Return: Pointer to destination string.
*/
char *_strncat(char *dest, const char *src, size_t m)
{
size_t dest_len = _strlen(dest);
size_t j;

for (j = 0; j < m && src[j] != '\0'; j++)
dest[dest_len + j] = src[j];
dest[dest_len + j] = '\0';

return (dest);
}
