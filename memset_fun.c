#include "btshell.h"
/**
 * _memset - Fills memory with a constant byte
 * @s: Pointer to the memory area
 * @b: Byte to fill *s with
 * @n: Amount of bytes
 * Return: s- a pointer to the memory area of s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * free_vector -Frees memory allocated to a 2D character array
 * @vec: Vector to be freed.
 *
 * Return: Nothing.
 */

void free_vector(char **vec)
{
	char **ptr = vec;

	if (!vec)
		return;
	while (*vec)
		free(*vec++);

	free(ptr);
}

/**
 * _realloc - Reallocates a block of memory
 * @ptr: Pointer to previous memory
 * @old_size: Byte size of previous block
 * @new_size: Byte size of new block
 *
 * Return: Pointer of old block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * bfree - Frees a pointer and NULLs the address
 * @ptr: Address of pointer
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
