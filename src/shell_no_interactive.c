#include "shell.h"

char	*read_stream(void)
{
	char	*line;
	size_t	bufsize;
	size_t	i;
	int		character;

	bufsize = 1024;
	i = 0;
	line = malloc(bufsize * sizeof(char));
	if (!line)
	{
		fprintf(stderr, "allocation error in read_stream\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		character = getchar();
		if (character == EOF)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else if (character == '\n')
		{
			line[i] = '\0';
			return (line);
		}
		else
			line[i] = character;
		i++;
		if (i >= bufsize)
		{
			bufsize += bufsize;
			line = realloc(line, bufsize * sizeof(char));
			if (!line)
			{
				fprintf(stderr, "allocation error in read_stream\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

void	shell_no_interactive(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status == -1)
	{
		line = read_stream();
		args = split_line(line);
		status = execute(args);
		free(line);
		free(args);
		if (status >= 0)
			exit(status);
	}
}