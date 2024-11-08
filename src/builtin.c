#include "shell.h"

int		own_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("error in chdir");
		}
	}
	return (1);
}

int		own_env(char **args)
{
	(void)args;
	int		i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (1);
}

int		own_help(char **args)
{
	(void)args;
	printf("Welcome to the help section\n");
	printf("Here are the built-in commands:\n");
	printf("cd<directory> - Change the current directory\n");
	printf("exit - Exit the shell\n");
	printf("env - Display environment variables\n");
	printf("help - Display this help message\n");
	return (1);
}

int	own_exit(char **args)
{
	(void)args;
	exit (0);
}