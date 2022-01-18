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
		buff = malloc(sizeof(t_list));
		if (!buff)
			ft_exit("malloc foire");
		*buff = (t_cmd){0};
		buff->path = strs[i];
		*end = buff;
		buff->prev = prev;
		prev = buff;
		end = &(buff->next);
	}
	*end = NULL;
}

void	divide_pip(char *s, t_data **data)
{
	char	**strs;
	t_cmd	*pips;

	strs = ft_split_func(s, "|", &divide_with_quotes);
	if (!strs)
		ft_exit("the end\n");
	pips = NULL;
	generate_cmds_strs(&pips, strs);
	printf("je suis la %p -> %p\n", *data, (*data)->cmd);
	(*data)->cmd = NULL;
	(*data)->cmd = malloc(sizeof(t_cmd*));
	if (!(*data)->cmd)
		ft_exit("je suis das al rue, dans le business");
	(*data)->cmd = &pips;
	while (pips)
	{
		printf("%p = %s\n", pips, pips->path);
		pips = pips->next;
	}
}
