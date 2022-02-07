#include "pip.h"

bool	check_pip_double(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (ft_strchr(" \t\v\f\n", s[i]) && i == 0)
		{
			while (s[i] && ft_strchr(" \t\v\f\n", s[i]))
				i++;
			if (!s[i])
				ft_exit("empty_line");
			if (s[i] == '|')
				return (true);
		}
		if (s[i] == '|')
		{
			if (i == 0)
				return (true);
			i++;
			while (s[i] && ft_strchr(" \t\v\f\n", s[i]))
				i++;
			if (!s[i] || s[i] == '|')
				return (true);
		}
	}
	return (false);
}

bool	divide_with_quotes(char *str, int index, char *c)
{
	bool	q;
	bool	dq;
	int		i;

	if (!str || !c || index < 0 || !ft_strchr(c, str[index]))
		return (false);
	q = false;
	dq = false;
	i = -1;
	while (str[++i] && i < index)
	{
		if (str[i] == '"')
		{
			if (!q)
				dq = !dq;
		}
		else if (str[i] == '\'')
		{
			if (!dq)
				q = !q;
		}
	}
	if (i != index)
		return (false);
	return (!q && !dq);
}

void	generate_cmds_strs(t_cmd **pips, char **strs)
{
	t_cmd	*buff;
	t_cmd	*prev;
	t_cmd	**end;
	int		i;

	i = -1;
	end = pips;
	prev = NULL;
	while (strs[++i])
	{
		buff = ft_malloc_conditional(sizeof(t_cmd));
		if (!buff)
			ft_exit("malloc foire");
		*buff = (t_cmd){0};
		buff->infile = -1;
		buff->outfile = -1;
		buff->path = strs[i];
		*end = buff;
		buff->prev = prev;
		prev = buff;
		end = &(buff->next);
		buff = NULL;
	}
	free(strs);
	*end = NULL;
}

void	ft_exit(char *str)
{
	printf("%s\n", str);
	exit (0);
}

int		count_double_tab(char **strs)
{
	int		i;

	i = 0;
	while (strs[i])
	{
		add_lst_malloc((void*)strs[i]);
		i++;
	}
	return (i);
}

void	divide_pip(char *s, t_data **data)
{
	char	**strs;
	t_cmd	**pips;

	strs = ft_split_func(s, "|", &divide_with_quotes);
	pips = ft_malloc_conditional(sizeof(t_cmd*));
	if (!strs || !pips)
		ft_exit("error_malloc\n");
	*pips = NULL;
	(*data)->nbr_cmd = count_double_tab(strs);
	generate_cmds_strs(pips, strs);
	(*data)->cmd = pips;
}
