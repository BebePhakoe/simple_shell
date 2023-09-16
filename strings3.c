#include "btshell.h"

/**
 * _strcpy - copies a character of strings
 * @dest: destination
 * @src: source
 *
 * Return: destination
 */
char *_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *return_value;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	return_value = malloc(sizeof(char) * (len + 1));
	if (!return_value)
		return (NULL);
	for (len++; len--;)
		return_value[len] = *--str;
	return (return_value);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void _puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int index;
	static char buffer[BUFFER_SIZE_WRITE];

	if (c == NEGATIVE_ONE || index >= BUFFER_SIZE_WRITE)
	{
		write(1, buffer, index);
		i = 0;
	}
	if (c != NEGATIVE_ONE)
		buffer[index++] = c;
	return (1);
}
