#include "btshell.h"

/**
 * set_zeros - Sets the bytes of an integer array to 0
 * @arr: Array to be initialized.
 * @size: Size of the array.
 *
 * Return: Nothing
 */

void set_zeros(unsigned int *arr, size_t size)
{
	size_t local_size;

	for (local_size = 0; local_size < size; local_size++)
		arr[local_size] = 0;
}

/**
 * set_nulls - Sets all the characters in a char array to nulls
 * @arr: Array to be initialized.
 * @size: Size of the array.
 *
 * Return: Nothing
 */

void set_nulls(char *arr, size_t size)
{
	size_t local_size;

	for (local_size = 0; local_size < size; local_size++)
		arr[local_size] = '\0';
}
