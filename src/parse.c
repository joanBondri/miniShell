#include "minishell.h"

int		entanglement(char *s)
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
				q = (q + 1) % 2;
			else
				dq = (dq + 1) % 2;
			while (s[i] && s[i] != c)
				++i;
			if (!s[i])
				break ;
			if (c == '\'')
				q = (q + 1) % 2;
			else
				dq = (dq + 1) % 2;
		}
	}
	return (q + dq);
}

void	attach_end_lst_cell(t_cell *buff, t_cell **lst)
{
	t_cell	*end;

	if (!*lst)
		*lst = buff;
	else
	{
		end = *lst;
		while (end->next)
			end = end->next;
		end->next = buff;
	}
}

//on decompose deja les quotes
t_cell	**decompose_quotes(char *s, t_cell **lst, char *comp)
{
	unsigned int	count;
	int				i;
	int				info;
	t_cell			*buff;

	count = 0;
	i = -1;
	if (comp[0] == '\'')
	{
		info = QUOTE;
		while (s[++i] != '\'')
			count++;
	}
	else if (comp[0] == '"')
	{
		info = DQUOTE;
		while (s[++i] != '"')
			count++;
	}
	else
	{
		info = NOTHING;
		while (s[++i] && s[i] != '\'' && s[i] != '"')
			count++;
	}
	if (count == 0)
		return (lst);
	buff = malloc(sizeof(t_cell));
	if (!buff)
		return (NULL);
	*buff = {0};
	buff->separator = info;
	buff->content = malloc(sizeof(char) * (count + 1));
	if (!buff->content)
		return (NULL);
	strlcpy(buff->content, s, (t_size)count);
	if (s[i] == 0)
		return (lst);
	if (info == NOTHING)
		return (decompose_quotes(s + i + 1, lst, s + i));
	return (decompose_quotes(s + i + 1, lst, ""));
}

void	create_multiple_cells(char **strs, t_cell **lst)
{
	t_cell	*buff;
	t_cell	*end;

	strs--;
	end = NULL;
	while (*(++strs))
	{
		buff = malloc(sizeof(t_cell));
		if (!buff)
			return ;
		*buff = {0};
		buff->content = *strs;
		buff->separator = MSSPACE;
		if (!end)
			*lst = buff;
		else
			end->next = buff;
		end = buff;
	}
}

void	ft_exit(charr *str)
{
	printf(str);
	exit(0);
}

bool	decompose_spaces(t_cell *current, t_cell *prev, t_cell **lst)
{
	int		i;
	char	*s;
	char	**strs;
	t_cell	*cell;

	i = -1;
	if (!current)
		return ;
	if (current->separator != NOTHING)
		return (decompose_spaces(current->next));
	s = current->content;
	strs = ft_split(s, " ");
	if (!strs)
		return (true);
	else
		create_multiple_cells(strs, &cell);
	if (prev)
		prev->next = cell;
	if (!prev)
		*lst = cell;
	while (cell->next)
		cell = cell->next;
	cell->next = current->next;
	free(current->content);
	free(current);
	return (cell->next, cell, lst);
}

int		deconstruct(char *s, t_data **dt)
{
	t_cell		*lst;

	lst = NULL;
	if (entanglement(s));
		ft_exit("unexpected character\n");
	*lst = {0};
	if (!decompose_quotes(s, &lst))
		ft_exit("error with malloc\n");
	decompose_spaces(&lst);
	while (lst)
	{
		printf("%s = %i\n", lst->content, lst->separator);
		lst = lst->next;
	}
	ft_exit("bizzare l'ambiance\n");
}

t_data	parse(int ac, char **av, char **env)
{
	t_data	*data;
	char	*str;
	t_cell	lst;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	data->env = list_env(env);

//to delete
	t_env	*buff;
	char	**s;
	buff = *(data->env);
	while (buff)
	{
		printf("%s = ", buff->var);
		s = buff->val;
		--s;
		while (*++s)
			printf("%s:", *s);
		printf("\n");
		buff = buff->next;
	}
	return (NULL);
	//end of delete
/*		
	while (true)
	{
		str = readline(get_prompt());
		add_history(str);
		deconstruct(str, data, &lst);
	}
	*/
}
