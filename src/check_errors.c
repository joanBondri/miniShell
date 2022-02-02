#include "pip.h"

void	parser_director(char *s, t_data **dt)
{
	t_cmd			*buff;

	(void)buff;
	(void)dt;
	check_pips(s);
	if (change_mind("yes", false))
		return ;
	check_quotes(s);
	if (change_mind("yes", false))
		return ;
	printf("-> %s\n", s);
	check_par(s);
	if (change_mind("yes", false))
		return ;
	check_redirection(s, *dt);
	if (change_mind("yes", false))
		return ;
	/*divide_pip(s, dt);
	buff = (*dt)->cmd[0];
	int		yaa = -1;
	while (buff)
	{
		get_redirection(s, buff, *dt);
		expand_rest_envvar(buff, *dt);
		interprate_sequence(buff);

		int i = -1;
		printf("\nje suis la cmd number %i:\n", ++yaa);
		while (buff->arg[++i])
			printf("arg %i : %s\n", i, buff->arg[i]);
		buff = buff->next;
		//heredoc
	}*/
	//fonction de xaviiiiiier
	return ;
}

void	interprate_sequence(t_cmd *buff)
{
	char	**strs;

	strs = ft_split_func(buff->path, " ", divide_with_quotes);
	buff->arg = strs;
}

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*buff1;
	char	*buff2;

	if (!s1 && !s2 && !s3)
		return (NULL);
	buff1 = ft_strjoin(s1, s2);
	buff2 = ft_strjoin(buff1, s3);
	free(buff1);
	return (buff2);
}

void	expand_rest_envvar(t_cmd *buff, t_data *dt)
{
	char	*str;
	int		i;
	char	*buff_s;
	t_token	t;

	str = buff->path;
	i = 0;
	while (str[i])
	{
		t = (t_token){0};
		next_token(str + i, &t, dt);
		if (t.status == MSVARENV || t.status == MSDQUOTE)
		{
			if (t.status == MSDQUOTE
					&& (t.sub_status != MSVOID || t.sub_status != MSNONE))
			{
				buff_s = ft_strjoin_three("'", t.copy, "'");
				free(t.copy);
				t.copy = buff_s;
			}
			buff_s = ft_strlreplace(buff->path, t.copy, i, t.length);
			free(buff->path);
			free(t.copy);
			buff->path = buff_s;
		}
		i+= t.length;
	}
}

void	no_such_file(char *name)
{
		printf("minishell: %s:  No such file or directory\n", name);
		free_all_lst_malloc();
		return (come_back_prompt(NULL));
}

void	get_2_redirection(char *s, t_cmd *yop, t_token t)
{
	int		flag;
	int		fd;

	if (!ft_strncmp(s, ">", 1))
	{
		flag = O_CREAT | O_RDWR;
		if (!ft_strncmp(s, ">>", 2))
			flag = flag | O_APPEND;
		else
			flag = flag | O_TRUNC;
		fd = open(t.copy, flag,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (!fd)
			return (no_such_file(t.copy));
		if (yop->outfile != 0)
			close(yop->outfile);
		yop->outfile = fd;
		return ;
	}
	fd = open(t.copy, O_RDONLY);
	if (fd < 1)
		return (no_such_file(t.copy));
	if (yop->infile)
		close(yop->infile);
	yop->infile = fd;
}

void	get_redirection(char *str, t_cmd *focus, t_data *dt)
{
	int			i;
	bool		q;
	bool		p;
	t_token		t;

	i = -1;
	q = false;
	p = false;
	while (str[++i])
	{
		if (str[i] == '\'' && !p)
			q = !q;
		if (str[i] == '"' && !q)
			p = !p;
		if (ft_strchr("<>", str[i]) && !q && !p)
		{
			t = (t_token){0};
			if (!ft_strncmp(">>", str + i, 2))
				assemblage_file_name_red(str + i + 2, &t, dt);
			else
				assemblage_file_name_red(str + i + 1, &t, dt);
			get_2_redirection(str + i, focus, t);
			if (!ft_strncmp(">>", str + i, 2))
				focus->path = ft_strlreplace(str, "", i, t.length + 2);
			else
				focus->path = ft_strlreplace(str, "", i, t.length + 1);
		}
	}
	
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
	if (!(t.copy))
		return (ft_unexpected_token('\0', ft_strdup("newline")));
	else
		return (ft_unexpected_token('\0', t.copy));
}

void	ambigus_redirect(char *s)
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
	res = ft_strndup(s + i, j);
	printf("minishell: %s: ambiguous redirect\n", res);
	free(res);
	free_all_lst_malloc();
	change_mind("yes", true);
}

char	*assemblage_concateneur(char *s1, char *s2)
{
	static char	*str = NULL;
	char		*res;
	char		*res1;


	if (!s1 && !s2)
		return (NULL);
	if (!s2)
	{
		res = str;
		str = NULL;
		return (res);
	}
	if (s1)
		res = ft_strjoin(s1, s2);
	else
		res = s2;
	res1 = ft_strjoin(str, res);
	free(res);
	free(str);
	str = res1;
	return (NULL);
}

void	assemblage_file_name_red(char *s, t_token *tt,  t_data *dt)
{
	int		i;
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
		if ((t.status >= MSPIP && t.status <= MSRED_OUT)
				|| t.status == MSWHITESPACE)
			break ;
		i += t.length;
		if (t.status == MSVARENV && t.sub_status == MSNONE &&
				!ft_strncmp(t.copy, "", 23))
			p = true;
		else
			p = false;
		assemblage_concateneur(NULL, t.copy);
		printf("%s\n", t.copy);
	}
	tt->copy = assemblage_concateneur("rien", NULL);
	tt->length = i;
	if (t.copy)
		free(t.copy);
	if (p)
	{
//		free(tt->copy);
		ambigus_redirect(s);
	}
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

void	check_pips(char *s)
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
	while (s[i] && s[i] != '"')
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
		if (tok.status == MSVARENV)
		{
			res = ft_strlreplace(t->copy, tok.copy, i - 1, tok.length);
			if (!res)
				return((void)printf("malloc wsh\n"));
			printf("status = %i and sub = %i, str = %s\n", tok.status, tok.sub_status, tok.copy);
			printf("res = %s\n", res);
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
		t->copy = ft_strdup("");
		return ;
	}
	res = find_env(t->copy, dt);
	if (!res)
	{
		free(t->copy);
		t->copy = ft_strdup("");
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
			printf("minishell: syntax error near unexpected token `%s'\n", s);
		else
			printf("minishell: syntax error near unexpected token `%c'\n", c);
		free_all_lst_malloc();
		change_mind("yes", true);
}

void	ft_bad_substitution(char *s)
{
	int		i;
	int		j;
	char	*res;

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
	free_all_lst_malloc();
	change_mind("yes", true);
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
				if (i == j + 2 && ft_isdigit(s[i]))
					return (ft_bad_substitution(s + j));
				if (!ft_isalnum(s[i]) && s[i] != '_')
					return (ft_bad_substitution(s + j));
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

int		check_redirection_file(char *str, t_data *dt)
{
	int		i;
	int		len;
	t_token	t;

	if (ft_strlen(str) < 1)
	{
		ft_unexpected_token((char)0, strdup("newline"));
		return (0);
	}
	i = 0;
	if (ft_strchr("<>", str[1]))
	{
		i = 1;
		len = 2;
		if (str[1] != str[0])
		{
			ft_unexpected_token(str[1], NULL);
			return (2);
		}
	}
	else
		len = 1;
	assemblage_file_name_red(str + len, &t, dt);
	printf("yaa %s\n", t.copy);
	if (t.copy)
		free(t.copy);
	t.copy = NULL;
	return (len);
}

void	check_redirection(char *str, t_data *dt)
{
	int			i;
	bool		q;
	bool		p;

	i = -1;
	q = false;
	p = false;
	while (str[++i])
	{
		if (str[i] == '\'' && !p)
			q = !q;
		if (str[i] == '"' && !q)
			p = !p;
		if (ft_strchr("<>", str[i]) && !q && !p)
			i += check_redirection_file(str + i, dt);
		if (change_mind("no", false))
			return ;
		
	}
}

char	entanglement(char *s)
{
	char	c;
	int		i;
	bool	q;
	bool	dq;

	i = -1;
	dq = false;
	q = false;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			c = s[i];
			if (c == '\'')
				q = !q;
			else
				dq = !dq;
			i++;
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

void	check_quotes(char *s)
{
	char	c;

	c = entanglement(s);
	if (c)
		ft_unexpected_token(c, NULL);
}
