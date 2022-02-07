#include "pip.h"

char	switch_varenv(char *str, t_data *dt)
{
	int		i;
	t_token	t;
	char	*res;

	i = -1;
	while (str[++i])
	{
		t = (t_token){0};
		if (str[i] == '$')
			next_token(str + i, &t, dt);
		if (``)
	}
}

void	determine_content_herdoc(char *del, int fd, t_cmd *buff, t_data *dt)
{
	char	*s;
	int		res;
	int		line;

	s = NULL;
	line = 0;
	write(1, ">", 1);
	res = get_next_line(0, &s);
	while (res != -1)
	{
		if (res == 0)
		{
			printf("minishell: warning: heredocument at line ");
			printf("%d delimited by end-of-file (wanted `%s')\n", line, del);
		}
		write(1, ">", 1);
		res = get_next_line(0, &s);
	}

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
