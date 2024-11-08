#include "shell.h"

char	*read_line(void)
{
	char	*line;
	size_t	bufsize;

	bufsize = 0;
	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free (line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free (line);
			perror("error in readline from stdin");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}

char	**split_line(char *line)
{
	int		bufsize;
	int		i;
	char	**tokens;
	char	*token;

	bufsize = 64;
	i = 0;
	tokens = malloc(bufsize * sizeof(char *));
	if (!tokens)
	{
		perror("allocation error");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		if (token[0] == '#')
			break;
		tokens[i] = token;
		i++;
		if (i >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf (stderr, "allocation error in split_line\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[i] = NULL;
	return (tokens);
}

int	execute(char **args)
{
	char	*builtin_func_list[] = {"cd", "exit", "env", "help"};
	int		(*builtin_func[]) (char **) = {&own_cd, &own_exit, &own_env, &own_help};
	unsigned long	i;

	if (args[0] == NULL)
		return (1);
	i = 0;
	while (i < sizeof(builtin_func_list) / sizeof(char *))
	{
		if (strcmp(args[0], builtin_func_list[i]) == 0)
			return ((*builtin_func[i])(args));
		i++;
	}
	return (new_process(args));
}

int	new_process(char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 1;
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("error in execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("error in fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			waitpid(pid, &status, WUNTRACED);
		}
	}
	return (1);
}

void shell_interactive(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		printf("simple_prompt$ ");
		line = read_line();
		args = split_line(line);
		status = execute(args);
		free(line);
		free(args);
	}
}

