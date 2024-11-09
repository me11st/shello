#include "shell.h"

char    *read_line(void)
{
    char    *line;

    line = readline("simple_prompt$");
    if (line && *line)
        add_history(line);
    return (line);
}