#include "main.h"

/**
 * path_finder - finds the path to a command
 * @cmd: command to find
 * Return: path to command
 */

char *path_finder(char *cmd)
{
	char *path, *path_env, *path_to_cmd, *dir;
	size_t len = 0;

	if (strchr(cmd, '/') != NULL) 
	{ 
		if (access(cmd, X_OK) == 0) 
			return strdup(cmd);
		else
		{
			perror("Error");
			return NULL;
		}
	}
	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		perror("Error");
		return (NULL);
	}
	path = strdup(path_env);
	if (path == NULL)
	{
		perror("Error");
		return (NULL);
	}
	dir = strtok(path, ":");
	while (dir != NULL)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		path_to_cmd = malloc(sizeof(char) * len);
		if (path_to_cmd == NULL)
		{
			perror("Error");
			return (NULL);
		}
		snprintf(path_to_cmd, len, "%s/%s", dir, cmd);
		if (access(path_to_cmd, X_OK) == 0)
		{
			free(path);
			return (path_to_cmd);
		}
		free(path_to_cmd);
		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}
