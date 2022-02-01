#include "pip.h"

void	parser_director(char *s, t_data *dt)
{
	check_pips(s, dt);
	check_quotes(s, dt);
	check_par(s);
	check_redirection(s, dt);
	divide_pip(s, &dt);
	get_redirection(dt);
	replace_redirection(dt);
	expand_rest_anvvar(dt);
	interprate_sequence(dt);
	// fonction qui relie 
}

void	near_token(char *s, t_data *dt)
{
	int		i;
	int		j;
	t_token	t;

	i = 0;
	while (s[i] && ft_strchr(" \t\f\v", s[i]))
		i++;
	j = i;
	next_token(s, &t, dt);
	if (!(t->copy))
		ft_unexpected_token('\0', ft_strdup("newline"));
	else
		ft_unexpected_token('\0', t.copy);	
}

void	ambigus_redirect(char *str, t_data *dt)
{	
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (s[i] && ft_strchr(" \t\f\v", s[i]))
		i++;
	while (s[i + j] && !ft_strchr(" \t\f\v", s[i + j]))
		j++;
	res = ft_strndup(str + i, j);
	printf("minishell: %s: ambiguous redirect\n", res);
	free_all_malloc();
	come_back_prompt(dt);
}

void	assemblage_file_name_red(char *s, t_token &tt,  t_data *dt)
{
	int		i;
	char	*res_buff;
	bool	p;
	t_token	t;

	i = 0;
	p = false;
	while (s[i] && ft_strchr(" \t\f\v", s[i]))
		i++;
	while (s[i])
	{
		t = (t_token){0};
		next_token(s + i, &t, dt);
		if (!t.status == MSWHITESPACE)
			add_lst_malloc((void*)t.copy);
		if ((t.status >= PIP && t.status >= MSRED_OUT)
				|| t.status == MSWHITESPACE)
			break ;
		if (t.sub_status == NONE && t.copy == NULL)
			p = true;
		else
			p = false;
		else if (t.sub_status == NONE || t.sub_status == VOID)
			continue ;
		res_buff = ft_strjoin(res, t.copy);
		if (res)
			free(res);
		res = res_buff;
		i += t.length;
	}
	tt->length = i;
	if (!(tt->copy) && p)
		ambigus_redirect(s, dt);
	else if(!(tt->copy))
		near_token(s, dt);
}

char	*ft_strndup(char *s, int size)
{
	int		i;
	char	*res;

	i = 0;
	if (size < 0 || !s)
		return (NULL);
	i = ft_strlen(s);
	if (size < i)
		i = size;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, i + 1);
	return (res);
}

void	check_pips(char *s, t_data *dt)
{
	if (check_pip_double(s))
		ft_unexpected_token('|', NULL);
}

char	*ft_strlreplace(char *s1, char *s2, int index, int len)
{
	char	*start;
	char	*end;
	char	*buff;
	char	*res;

	if (!s1 || len < 0 || index < 0)
		return (NULL);
	if (index + len > ft_strlen(s1))
		end = NULL;
	else
		end = ft_strdup(s1 + index + len);
	start = ft_strndup(s1, index);
	buff = ft_strjoin(start, s2);
	res = ft_strjoin(buff, end);
	if (end)
		free(end);
	if (start)
		free(start);
	if (buff)
		free(buff);
	return (res);
}

void	develope_dquote(t_token *t, char *s, t_data *dt)
{
	int		i;
	t_token	tok;
	char	*res;

	i = 1;
	while (s[i] != '"')
		i++;
	t->start = s;
	t->length = i + 1;
	if (i == 1)
		t->sub_status = MSVOID;
	else
		t->sub_status = MSWORD;
	t->copy = ft_strndup(s + 1, i - 1);
	while (s[--i] != '\"')
	{
		if (s[i] != '$')
			continue ;
		next_token(s + i, &tok, dt);
		if (tok.length == -1)
			continue ;
		if (tok.status == MSVARENV && (tok.sub_status != MSNONE
				|| tok.status == MSWORD))
		{
			res = ft_strlreplace(t->copy, tok.copy, i, tok.length);
			if (!res)
				ft_exit("malloc wsh\n");
			free(t->copy);
			free(tok.copy);
			t->copy = res;
		}
	}
	return ;
}

void	develope_word(t_token *t, char *s)
{
	int		i;

	if (!s[0])
	{
		t->length = 0;
		t->sub_status = MSVOID;
		return ;
	}

	i = 1;
	while (s[i] && !ft_strchr("<>|$'\" ", s[i]))
		i++;
	t->copy = ft_strndup(s, i);
	t->length = ft_strlen(t->copy);
	return ;
}

void	develope_quote(t_token *t, char *s)
{
	int		i;

	i = 1;
	while (s[i] != '\'')
		i++;
	t->start = s;
	t->length = i + 1;
	if (i == 1)
		t->sub_status = MSVOID;
	else
		t->sub_status = MSWORD;
	t->copy = ft_strndup(s + 1, i - 1);
	return ;
}

void	develope_varenv(t_token *t, char *s, t_data *dt)
{
	char	*res;
	int		i;
	bool	start;

	t->length = find_variable_in_str(s, &(t->copy));
	if (-1 == t->length)
	{
		t->sub_status = MSNONE;
		return ;
	}
	res = find_env(t->copy, dt);
	if (!res)
	{
		t->sub_status = MSNONE;
		return ;
	}
	start = false;
	free(t->copy);
	t->copy = res;
	i = 0;
	while (res[i] && ft_strchr(" \t\f\v\n", res[i]))
		i++;
	if (ft_strlen(res) == 0)
		t->sub_status = MSVOID;
	else if (i == ft_strlen(res))
		t->sub_status = MSWHITESPACE;
	else if (i != 0)
		start = true;
	while (res[i] && !ft_strchr(" \t\f\v\n", res[i]))
		i++;
	if (i != ft_strlen(res))
	{
		while (res[i] && ft_strchr(" \t\f\v\n", res[i]))
			i++;
		if (i != ft_strlen(res))
			t->sub_status = MSAMBIGOUS;
		else if (start)
			t->sub_status = MSAMBIGOUSLR;
		else
			t->sub_status = MSAMBIGOUSR;
	}
	else if (start)
		t->sub_status = MSAMBIGOUSL;
	else
		t->sub_status = MSWORD;
}

void	develope_redirection(t_token *t, char *s)
{
	t->start = s;
	if (t->status == MSRED_HER || t->status == MSRED_APP)
		t->copy = ft_strndup(s, 2);
	else
		t->copy = ft_strndup(s, 1);
	t->length = ft_strlen(t->copy);
}
//il rest a faire les tokens de < > | ' ", et tout ce qui est mot simple puis gerer la concatenation
//mais j'avance puisqu'il rest maintenant a faire les okens les plus simpl il y aura juste la cancatenation qui sera un peut galere
//ensuite il faudra ouvrir les fichiers puis les refermer
//faire toutes les redirection puis il faudra interpreter
void	find_type_token(char *tb, char *s, t_token *t, t_data *dt)
{
	if (ft_strncmp(tb, s, ft_strlen(tb)) && ft_strchr("<>|$\'\"", s[0]))
			return ;
	t->start = s;
	if (!ft_strchr("<>|$\'\"", s[0]))
		t->status = MSWORD;
	else if (s[0] == '$' && (!s[1] || ft_strchr(" \t\v\n\f", s[1])))
		t->status = MSWORD;
	if (t->status == MSVARENV)
		return (develope_varenv(t, s, dt));
	else if (t->status == MSQUOTE)
		return (develope_quote(t, s));
	else if (t->status == MSDQUOTE)
		return (develope_dquote(t, s, dt));
	else if (t->status == MSWORD)
		return (develope_word(t, s));
	else
		return (develope_redirection(t, s));
}

void	ft_unexpected_token(char c, char *s)
{
		(void)s;
		if (s)
			printf("minishell: syntax error near unexpected token `%s'", s);
		else
			printf("minishell: syntax error near unexpected token `%c'", c);
		exit(2);
}

void	ft_bad_substitution(char *s)
{
	int		i;

	i = 1;
	j = ft_strlen(s);
	while (s[++i])
	{
		if (s[i] == '}')
		{
			while (s[++i])
			{
				if (s[i] == ' ')
				{
					j = i;
					i = ft_strlen(s);
				}
			}
		}
	}
	res = ft_strndup(s, j);
	printf("minishell: %s: bad substitution\n", res);
	free(res);
	ft_exit(1);
}

void	check_par(char *s)
{
	int		i;
	int		j;

	i = -1;
	while (s[++i])
	{
		if(s[i] == '$' && s[i + 1] == '{')
		{
			j = i;
			i += 1;
			while (s[++i])
			{
				if (s[i] == '}')
					break ;
				if (!ft_isalnum(s[i]) && s[i] != '_')
					ft_bad_substitution(s + j);
			}
		}
	}
	return ;
}

void	next_token(char *s, t_token *t, t_data *dt)
{
	int		i;
	static	char *tb[] = {"|", "<<",  ">>", "<", ">", "'", "\"", "$"};

	i = 0;
	while (s[i] && ft_strchr(" \t\v\f\n", s[i]))
		i++;
	if (i != 0)
	{
		t->status = MSWHITESPACE;
		t->length = i;
		return ;
	}
	t->start = s;
	i = -1;
	while(++i < 8)
	{
		*t = (t_token){0};
		t->status = i;
		find_type_token((char*)tb[i], s, t, dt);
		if (t->start)
			break ;
	}
}

void	check_heredoc(char *s)
{
	(void)s;
}

void	check_redirection_file(char *str, t_data *dt)
{
	int		i;
	t_token	t;

	if (ft_strlen(str) < 1)
		ft_unexpected_token((char)0, strdup("newline"));
	i = 0;
	if (ft_strchr("<>", str[1]))
	{
		i = 1;
		if (str[1] != str[0])
			ft_unexpected_token(str[1], NULL);
		if (str[0] == '<')
			return (check_heredoc(str));
	}
	assemblage_file_name_red(str, &t, dt);
	free(t.copy);
}

void	check_redirection(char *str, t_data *dt)
{
	int			i;
	static bool	q[2] = {0};

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && !q[1])
			q[0] = !q[0];
		if (str[i] == '"' && !q[0])
			q[1] = !q[1];
		if (ft_strchr("<>", str[i] && !q[0] && !q[1]))
			check_redirection_file(str + i, dt);
	}
}

char	entanglement(char *s)
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
	if (q || dq)
		return (c);
	return (0);
}

void	check_quotes(char *s, t_data *dt)
{
	char	c;

	c = entanglement(s);
	if (c)
		ft_unexpected_token(c, NULL);
}

void	check_errors_cmd(char *s)
{
	check_pips(s);
}
