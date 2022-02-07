#include "pip.h"

void	ft_exit_malloc(void)
{
	printf("error_malloc");
	free_lst_malloc();
	exit(1);
}

char	*switch_varenv(char *str, t_data *dt)
{
	int		i;
	t_token	t;
	char	*res;

	i = 0;
	while (str[i])
	{
		t = (t_token){0};
		if (str[i] == '$')
		{
			next_token(str + i, &t, dt);
			if (t.status != MSVARENV)
			{
				free(t.copy);
				i++;
				continue ;
			}
			res = ft_strlreplace(str, t.copy, i, t.length);
			free(str);
			free(t.copy);
			if (!res)
				ft_exit_malloc();
			str = res;
			i += t.length;
		}
		else
			i++;
	}
	return (str);
}

void	determine_content_herdoc(char *del, int fd, t_cmd *buff, t_data *dt)
{
	char	*s;
	int		res;
	int		line;

	line = 0;
	while (true)
	{
		s = NULL;
		line++;
		write(1, ">", 1);
		res = get_next_line(0, &s);
		if (res == 0)
		{
			printf("minishell: warning: heredocument at line ");
			printf("%d delimited by end-of-file (wanted `%s')\n", line, del);
			free_lst_malloc();
			return (-1)	;	
		}
		if (res == -1 || (!ft_strncmp(s, del, ft_strlen(s)) &&
					!ft_strncmp(s, del, ft_strlen(del))))
			break ;
		write(fd, switch_varenv(s, dt), ft_strlen(s));
		write(fd, "\n", 1);
		free(s);
	}
	if (res != -1)
		ft_exit_malloc();
}

char	*go_heredoc(char *str, t_cmd *buff, t_data *dt)
{
	static int	pip[2];
	int			id;

	pipe(pip);
	id = fork();
/*	if (id == 0)
	{
		wait
	}*/
}

void	catch_heredoc(char *str, t_cmd *buff, t_data *dt)
{
	int		i;
	bool	q;
	bool	dq;
	char	*res;

	q = false;
	dq = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !dq)
			q = !q;
		else if (str[i] == '"' && !q)
			dq = !dq;
		else if (!dq && !q && ft_strncmp("<<", str + i, 2))
		{
			res = go_heredoc(str + i, buff, dt);
			buff->path = ft_strlreplace(str, "", i, ft_strlen(res));
			free(str);
			str = buff->path;
			if (res)
				free(res);
		}
	}
}
