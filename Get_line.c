#include "shell.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - Re-allocate memory block by malloc and free.
 * @ptr:pointer to memory previously allocated.
 * @old_size:bytes of the allocated space for ptr size.
 * @new_size: bytes size for the new memory block.
 *
 * Description:function that re allcoate memory block
 * Return: new_size == old_size - ptr.
 *         new_size == 0 and ptr not NULL - NULL.
 *         Or - pointer to reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *me;
	char *ptr_copy, *filler;
	unsigned int inde;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		me = malloc(new_size);
		if (me == NULL)
			return (NULL);

		return (me);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	me = malloc(sizeof(*ptr_copy) * new_size);
	if (me == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = me;

	for (inde = 0; inde < old_size && inde < new_size; inde++)
		filler[inde] = *ptr_copy++;

	free(ptr);
	return (me);
}

/**
 * assign_lineptr - Re-assign lineptr variable to _getline.
 * @lineptr: buffer that store or save input string.
 * @n:lineptr size.
 * @buffer:lineptr string.
 * @b:buffer size.
 *
 * Description:function that re assign variable to getline
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Read input from main stream.
 * @lineptr:buffer that store the input.
 * @n:lineptr size.
 * @stream:stream to get information  from.
 *
 * Description:function to get input from stream
 * Return:number of bytes read.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t inpu;
	ssize_t re;
	char c = 'x', *buffer;
	int v;

	if (inpu == 0)
		fflush(stream);
	else
		return (-1);
	inpu = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		v = read(STDIN_FILENO, &c, 1);
		if (v == -1 || (v == 0 && inpu == 0))
		{
			free(buffer);
			return (-1);
		}
		if (v == 0 && inpu != 0)
		{
			inpu++;
			break;
		}

		if (inpu >= 120)
			buffer = _realloc(buffer, inpu, inpu + 1);

		buffer[inpu] = c;
		inpu++;
	}
	buffer[inpu] = '\0';

	assign_lineptr(lineptr, n, buffer, inpu);

	re = inpu;
	if (v != 0)
		inpu = 0;
	return (re);
}
