#include "main.h"

/**
 * env_finder - finds the environment variables
 * Return: 0 if successful
 */
int env_finder(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}

/**
 * executor - executes commands
 * @tokens: array of tokens
 * Return: 0
 */
int executor(char **tokens, char **av)
{
	char *cmd, *path_to_cmd;
	__pid_t pid;
	int status;
	static char *current_directory;

	if (tokens[0] == NULL)
		return (0);

	cmd = tokens[0];
	if (strcmp(cmd, "exit") == 0)
	{
		free_tokens(tokens);
		free(current_directory);
		exit(0);
	}
	else if (strcmp(cmd, "cd") == 0)
	{
		printf("%s\n", getcwd(current_directory, 1024));
	}
	else if (strcmp(cmd, "env") == 0)
	{
		env_finder();
	}
	else
	{
		path_to_cmd = path_finder(cmd);
		pid = fork();
		if (pid == 0)
		{
			if (execve(path_to_cmd, tokens, NULL) == -1)
			{
				fprintf(stderr, "%s: 1: %s: not found\n", av[0], cmd);
				exit(0);
			}
		}
		else if (pid < 0)
		{
			perror("Error");
			exit(0);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
			{
				fprintf(stderr, "%s: 1: %s: not found\n", av[0], cmd);
			}
		}
		free(path_to_cmd);
	}
	return (0);
}
