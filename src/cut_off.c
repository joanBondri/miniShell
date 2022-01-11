#include "minishell.h"

t_cell	*attribute_cell(char *s, int i, int info)
{
	t_cell	*res;

	res = malloc(sizeof(t_cell));
	if (!res)
		return (NULL);
	res->next = NULL;
	res->separator = info;
	if (ft_strlcpy(res->content, s, (size_t)i + 1))
		return (NULL);
	return (res);
}

t_cell *assign_cell(t_cell **lst, t_cell *last)
{
	t_cell		*buff;

	if (!lst || !*lst || !last)
		return (NULL);
	buff = *lst;
	while (buff->next)
		buff = buff->next;
	buff->next = last;
	last->next = NULL;
	return (last);
}

char decompose_quotes(char *s, t_cell **lst, char comp)
{
	int		i;
	int		info;
	char	c;

	i = 0;
	printf("str = %s\n", s);
	if (!*s)
		return ('\0');
	c = ' ';
	if (comp == '\'')
	{
		info = MSQUOTE;
		while (s[i] != '\'')
			i++;
	}
	else if (comp == '"')
	{
		info = MSDQUOTE;
		while (s[i] != '"')
			i++;
	}
	else if (comp == ' ')
	{
		info = MSNOTHING;
		while (s[i] && s[i] != '\'' && s[i] != '"')
			i++;
		c = '\0';
		if (s[i])
			c = s[i];
	}
	else
		return ('\0');
	if (i == 0)
		return (' ');
	s = s + i;
	assign_cell(lst, attribute_cell(s, i, info));
	return (c);
}

t_cell	*add_space_cell(t_cell *lst)
{
	t_cell	*to_add;
	t_cell	*buff;

	to_add = malloc(sizeof(t_cell));
	buff = lst;
	while (buff && buff->next)
		buff = buff->next;
	if (!buff)
		buff = malloc(sizeof(t_cell));
	if (!to_add || !buff)
		return (NULL);
	buff->next = to_add;
	*to_add = (t_cell){0};
	to_add->separator = MSWHITESPACE;
	return (lst);
}

t_cell	*create_multiple_cells(char **strs, t_cell **lst)
{
	t_cell	*buff;
	t_cell	*end;

	strs--;
	end = *lst;
	while (*(++strs))
	{
		buff = malloc(sizeof(t_cell));
		if (!buff)
			return (NULL);
		*buff = (t_cell){ 0 };
		buff->content = *strs;
		buff->separator = MSSPACE;
		if (!end)
			*lst = buff;
		else
			end->next = buff;
		end = buff;
	}
	return (buff);
}

void	chain_cell(t_cell *to_add, t_cell *next, t_cell *prev)
{
	if (!to_add)
		return ;
	if (prev)
		prev->next = to_add;
	while (to_add->next)
		to_add = to_add->next;
	to_add->next = next;
}

bool	only_char(char *start, char *end, char *find)
{
	int		i;
	int		j;

	i = -1;
	if (start >= end)
		return (false);
	while (start + ++i < end)
	{
		j = -1;
		while (find[++j])
		{
			if (find[j] == start[i])
				break ;
		}
		if (!find[j])
			return (false);
	}
	return (true);
}

t_cell	*decompose_spaces(t_cell *current, t_cell *prev)
{
	char	*s;
	char	**strs;
	int		i;
	t_cell	*to_add;

	s = current->content;
	printf("str = %s\n", s);
	i = 0;
	while (s[i])
		i++;
	if (only_char(s, s + i, " "))
	{
		current->separator = MSWHITESPACE;
		return (current->next);
	}
	i = 0;
	to_add = NULL;
	while (s[i] != ' ' && s[i])
		i++;
	if (i != 0)
	{
		if (!add_space_cell(to_add))
			return (NULL);
	}
	strs = ft_split(s, " ");
	if (!strs)
		return (NULL);
	create_multiple_cells(strs, &to_add);
	while (s[i])
		i++;
	if (i > 0 && s[i - 1] == ' ')
	{
		if (!add_space_cell(to_add))
			return (NULL);
	}
	chain_cell(to_add, current->next, prev);
	return (to_add->next);
}

