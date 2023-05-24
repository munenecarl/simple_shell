#include "main.h"

#ifndef SSIZE_MAX
#define SSIZE_MAX (SIZE_MAX >> 1)
#endif

#ifndef EINVAL
#define EINVAL 22
#endif

#ifndef ERANGE
#define ERANGE 34
#endif

/**
 * check_input_pointers - checks if the input pointers are all non-null.
 * @pline_buf: pointer to buffer that stores characters
 * @pn: size of the buffer
 * @fin: stream from which the file will be read
 * Return: path to command
 */

static int check_input_pointers(char **pline_buf, size_t *pn, FILE *fin)
{
	if ((pline_buf == NULL) || (pn == NULL) || (fin == NULL))
	{
		errno = EINVAL;
		return (-1);
	}
	return (0);
}

/**
 * allocate_buffer - finds the path to a command
 * @pline_buf: pointer to buffer that stores characters
 * @pn: size of the buffer
 * Return: path to command
 */

static int allocate_buffer(char **pline_buf, size_t *pn)
{
	const size_t INITALLOC = 16;

	if (*pline_buf == NULL)
	{
		*pline_buf = malloc(INITALLOC);
		if (*pline_buf == NULL)
		{
			/* Can't allocate memory. */
			return (-1);
		}
		else
		{
			/* Note how big the buffer is at this time. */
			*pn = INITALLOC;
		}
	}
	return (0);
}

/**
 * read_characters - reads characters from file and stores them in a buffer
 * @fin: stream from which the file will be read
 * @pline_buf: pointer to buffer that stores characters
 * @pn: size of the buffer
 * @num_read: number of characters read
 * Return: path to command
 */

static int read_characters(FILE *fin, char **pline_buf,
						   size_t *pn, size_t *num_read)
{
	const size_t ALLOCSTEP = 16;
	int c;

	while (EOF != (c = getc(fin)))
	{
		(*num_read)++;

		if (*num_read >= *pn)
		{
			size_t n_realloc = *pn + ALLOCSTEP;
			char *tmp = realloc(*pline_buf, n_realloc + 1);

			if (tmp != NULL)
			{
				*pline_buf = tmp;
				*pn = n_realloc;
			}
			else
			{
				free(*pline_buf);
				return (-1);
			}

			if (*pn > SSIZE_MAX)
			{
				errno = ERANGE;
				return (-1);
			}
		}

		(*pline_buf)[*num_read - 1] = (char)c;
		if (c == '\n')
		{
			break;
		}
	}

	if (c == EOF && *num_read == 0)
	{
		return (-1);
	}

	if (c == EOF)
	{
		if (*num_read >= *pn)
		{
			size_t n_realloc = *pn + 1;
			char *tmp = realloc(*pline_buf, n_realloc + 1);

			if (tmp != NULL)
			{
				*pline_buf = tmp;
				*pn = n_realloc;
			}
			else
			{
				free(*pline_buf);
				return (-1);
			}
		}

		(*pline_buf)[*num_read] = '\0';
		return ((*num_read == 0) ? (ssize_t)-1 : (ssize_t)*num_read);
	}

	(*pline_buf)[*num_read] = '\0';

	return ((*num_read == 0) ? (ssize_t)-1 : (ssize_t)*num_read);
}

/**
 * _getline - interface for reading a line of text from a file stream
 * @pline_buf: pointer to buffer that stores characters
 * @pn: size of the buffer
 * @fin: stream from which the file will be read
 * Return: path to command
 */

ssize_t _getline(char **pline_buf, size_t *pn, FILE *fin)
{
	size_t num_read = 0;

	if (check_input_pointers(pline_buf, pn, fin) != 0)
	{
		return (-1);
	}

	if (allocate_buffer(pline_buf, pn) != 0)
	{
		return (-1);
	}

	if (read_characters(fin, pline_buf, pn, &num_read) != 0)
	{
		return (-1);
	}

	/* Terminate the string by suffixing NUL. */
	(*pline_buf)[num_read] = '\0';

	return ((ssize_t)num_read);
}
