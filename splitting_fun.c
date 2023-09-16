#include "btshell.h"

/**
 * split_string - Splits a string into words specified by a delimiter(s)
 * by storing pointer to each word in an array.
 * @str: String
 * @separators: Delimiter(s) to split the string.
 * @word_count: Number of words in the string (separated by the delimiters).
 *
 * Return: Vector of words
 */

char **split_string(char *str, char *separators, size_t *word_count)
{
	int k, number_words;
	char **words;
	char *str_ptr = str;
	unsigned int i, word_sizes[MAX_WORD_COUNT];

	set_zeros(word_sizes, MAX_WORD_COUNT);
	number_words = words_count(str, separators, word_sizes);

	if (number_words == 0)
		return (NULL);

	words = malloc((sizeof(char *) * number_words) + 1);
	if (!words)
		return (NULL);

	for (k = 0; k < number_words; k++)
	{
		words[k] = malloc((sizeof(char) * word_sizes[k]) + 1);
		if (!words[k])
		{
			for (k--; k >= 0; k--)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (i = 0; i < word_sizes[k]; i++, str_ptr++)
		{
			while (is_delimiter(*str_ptr, separators))
				str_ptr++;

			words[k][i] = *str_ptr;
		};
		words[k][i] = '\0';
	}
	*word_count = number_words;

	words[k] = NULL;

	return (words);
}

/**
 * **strtow - Splits a string into words. Delimiters are ignored
 * @str: Input string
 * @d: Delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimiter(str[i], d) && (is_delimiter(str[i + 1], d) || !str[i + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delimiter(str[i], d))
			i++;
		k = 0;
		while (!is_delimiter(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
