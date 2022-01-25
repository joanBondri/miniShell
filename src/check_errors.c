#include "pip.h"

void	check_pips(char *s)
{
	if (check_pip_double(s))
		ft_exit("Error with pip\n");
}

void	find_type_token(char *tb, char *s, t_token *t)
{
	char	*copy;

	if (ft_strncmp(tb, s, ft_strlen(tb)) && ft_strchr("<>|$\'\"", str[0]))
			return ;
	t->start = s;
	if (!ft_strncmp(tb, s, ft_strlen(tb)))
		i = MSWORD;
	else if (s[0] == '$' && (!s[1] || ft_strchr(" \t\v\n\f", s[1])))
		i == MSWORD;
	t->status = i;
	if (-1 == find_variable_in_str(s, t->copy))
		t->sub_status = MSNONE;
	if ()

		
}

void	next_token(char *s, t_token *t)
{
	int		i;
	char	*str;
	t_token	tok;
	static	char tb[][] = {"|", "<<",  ">>, <", ">", "'", "\"", "$"};

	i = 0;
	while (ft_strchr(" \t\v\f\n", s[i]))
		i++;
	t->start = s + i;
	str = s + i;
	i = -1;
	while(++i < 8)
	{
		tok = (t_token){0};
		tok->status = i;
		find_type_token(tb[i], i, str, &tok);
		if (!tok.start)
			break ;
	}
}

void	check_redirection_file(char *str)
{
	int		i;
	t_token	t;

	if (ft_strlen(str) < 1)
		return ;
	i = 0;
	if (ft_strchr("<>", str[1]))
	{
		i = 1;
		if (str[1] != str[0])
			ft_unexpected_token(str[1], NULL);
		if (str[0] == "<")
			return (check_heredoc(str));
	}
	tokenise(str + i, &t);
}

void	check_redirection(char *s)
{
	int			i;
	static bool	q[2] = {0};

	while (str[++i])
	{
		if (str[i] == '\'' && !q[1])
			q[0] = !q[0];
		if (str[i] == '"' && !q[0])
			q[1] = !q[1];
		if (ft_strchr("<>", str[i] && !q[0] && !q[1]))
			check_redirection(str + i);
}

bool	entanglement(char *s)
{
	char	c;
	int		i;
	int		q;
	int		dq;

	i = -1;
	dq = 0;
	q = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			c = s[i];
			if (c == '\'')
				q = !q;
			else
				dq = !dq;
			while (s[i] && s[i] != c)
				++i;
			if (!s[i])
				break ;
			if (c == '\'')
				q = !q;
			else
				dq = !dq;
		}
	}
	return (q || dq);
}

void	check_quotes(char *s)
{
	if (etanglement(s))
		ft_exit("quotes : still open\n");
}

void	check_errors_cmd(char *s)
{
	check_pips(s);
}
