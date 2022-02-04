#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_cmd
{
    char *path;
    char **arg;
    int     infile;
    int     outfile;
    struct s_cmd	*next;
    struct s_cmd	*prev;
}               t_cmd;

typedef struct s_data
{
    int     here_doc;
    char    *delimiter;
    int     nbr_pipe;
    int     pipe_even[2];
    int     pipe_odd[2];
    char    **env;
    int     nbr_cmd;
    t_cmd   **cmd;
}               t_data;

void	exec_data(t_data data);

#endif
