#include "pip.h"

void	ft_exit_malloc(void)
{
	printf("error_malloc");
	free_all_lst_malloc();
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
			add_lst_malloc((void*)res);
			free(t.copy);
			if (!res)
			{
				ft_exit_malloc();
				return (NULL);
			}
			str = res;
			i += t.length;
		}
		else
			i++;
	}
	return (str);
}

void	determine_content_herdoc(char *del, int fd, t_data *dt)
{
	char	*s;
	int		res;
	int		line;

	line = 0;
	while (true)
	{
		s = NULL;
		line++;
		write(1, "> ", 2);
		res = get_next_line(0, &s);
		rl_on_new_line();
		add_lst_malloc((void*)s);
		if (res == 0)
		{
			printf("minishell: warning: heredocument at line ");
			printf("%d delimited by end-of-file (wanted `%s')\n", line, del);
			return ;
		}
		if (res == -1 || (!ft_strncmp(s, del, ft_strlen(s)) &&
					!ft_strncmp(s, del, ft_strlen(del))))
			break ;
		s = switch_varenv(s, dt);
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
	}
	if (res == -1)
		change_mind("yes", true);
}

char	*next_del(char *s, t_token *tt, t_data *dt)
{
	int		i;
	t_token	t;

	i = 2;
	while (s[i] && ft_strchr(" \t\f\v", s[i]))
		i++;
	while (s[i])
	{
		t = (t_token){0};
		if (s[i] == '$')
			develope_word(&t, s);
		else
			next_token(s + i, &t, dt);
		add_lst_malloc((void*)t.copy);
		if ((t.status >= MSPIP && t.status <= MSRED_OUT)
				|| t.status == MSWHITESPACE)
			break ;
		i += t.length;
		if (t.copy)
			assemblage_concateneur(t.copy);
	}
	tt->copy = assemblage_concateneur(NULL);
	tt->length = i;
	if(!(tt->copy))
	{
		near_token(s, dt);
		return (0);
	}
	return (tt->copy);
}

int	go_heredoc(char *str, t_cmd *buff, t_data *dt)
{
	static int	pip[2];
	char		*del;
	t_token		tt;

	tt = (t_token){0};
	del = next_del(str, &tt, dt);
	if (!del)
		return (0);
	//secur pip
	pipe(pip);
	if (buff->infile != -1)
		close(buff->infile);
	buff->infile = pip[0];
	determine_content_herdoc(del, pip[1], dt);
	free(del);
	
	close(pip[1]);
	return (tt.length);
}
void	check_if_here_last(char *str, t_cmd *buff)
{
	int		i;

	i = 0;
	buff->change_in = false;
	while (str[i])
	{
		if (!ft_strncmp("<<", str + i, 2))
		{
			i++;
			buff->change_in = true;
		}
		else if (!ft_strncmp("<", str + i, 1))
			buff->change_in = false;
		i++;
	}
}

void	catch_heredoc(char *str, t_cmd *buff, t_data *dt)
{
	int		i;
	bool	q;
	bool	dq;
	int		res;

	q = false;
	dq = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !dq)
			q = !q;
		else if (str[i] == '"' && !q)
			dq = !dq;
		else if (!dq && !q && !ft_strncmp("<<", str + i, 2))
		{
			res = go_heredoc(str + i, buff, dt);
			if (res == 0)
				return ;
			buff->path = ft_strlreplace(str, "", i, res);
			add_lst_malloc((void*)buff->path);
			str = buff->path;
			i--;
		}
		i++;
	}
}

void	do_all_heredoc(t_data *dt)
{
	t_cmd	*buff;

	buff = dt->cmd;
	while (buff)
	{
		check_if_here_last(buff->path, buff);
		catch_heredoc(buff->path, buff, dt);
		if (change_mind("no", false))
			return ;
		buff = buff->next;
	}
}
