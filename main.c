#include "main.h"

/**
 * token_creator - creates tokens from a string
 * @str: string to tokenize
 * Return: pointer to array of tokens
 */

char **token_creator(char *str)
{
	char *token;
	char **tokens;
	int i = 0;

	tokens = malloc(sizeof(char *) * 1024);
	if (tokens == NULL)
	{
		perror("Error");
		return (NULL);
	}
	token = strtok(str, " \n\t\r");
	while (token != NULL)
	{
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
		{
			perror("Error");
			free_tokens(tokens);
			return (NULL);
		}
		token = strtok(NULL, " \n\t\r");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * free_tokens - frees tokens
 * @tokens: array of tokens
 * Return: void
 */

void free_tokens(char **tokens)
{
	int i = 0;

	if (tokens == NULL)
		return;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

/**
 * main - prints stuff to the shell
 * @ac: argument count
 * @av: array of arguments
 * Return: 0
 */

int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	char *line = NULL;
	char **tokens;
	size_t len = 2048;
	int read;

	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}
		tokens = token_creator(line);
		if (tokens == NULL)
		{
			continue;
		}
		executor(tokens);
		free_tokens(tokens);
		free(line);
		line = NULL;
		len = 2048;
	}
	return (0);
}
