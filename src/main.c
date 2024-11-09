//main.c
#include "shell.h"

int main(void)
{
	read_history (".minishell_history");

	char	*line;

	while (1)
	{
		line = readline ("simple_prompt$");
		if (!line)
			break ;
		if (*line)
			add_history (line);
		free (line);
	}
	write_history (".minishell_history");
	// determines if file descriptor is associated with a terminal
	if (isatty(STDIN_FILENO) == 1)
	{
		shell_interactive();
	}
	else
	{
		shell_no_interactive();
	}
	return (0);
}