#include "pip.h"

/*void	attach_end_lst_cell(t_cell *buff, t_cell **lst)
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
}*/

//on decompose deja les quotes
/*
t_cell	**decompose_quotes(char *s, t_cell **lst, char *comp)
{
	unsigned int	count;
	int				i;
	int				info;
	t_cell			*buff;
	t_cell			*buff_two;

	count = 0;
	i = -1;
	if (comp[0] == '\'')
	{
		info = MSQUOTE;
		while (s[++i] != '\'')
			count++;
	}
	else if (comp[0] == '"')
	{
		info = MSDQUOTE;
		while (s[++i] != '"')
			count++;
	}
	else
	{
		info = MSNOTHING;
		while (s[++i] && s[i] != '\'' && s[i] != '"')
			count++;
		if (only_char(s, s + i, " "))
			info = MSWHITESPACE;
	}
	if (count == 0)
		return (lst);
	buff = malloc(sizeof(t_cell));
	if (!buff)
		return (NULL);
	buff->next = NULL;
	buff->separator = info;
	buff->content = malloc(sizeof(char) * (count + 1));
	if (!buff->content)
		return (NULL);
	ft_strlcpy(buff->content, s, (size_t)count + 1);
	if (!(*lst))
		*lst = buff;
	else
	{
		buff_two = *lst;
		while (buff_two->next)
			buff_two = buff_two->next;
		buff_two->next = buff;
	}
	if (s[i] == 0)
		return (lst);
	if (info == MSNOTHING)
		return (decompose_quotes(s + i + 1, lst, s + i));
	return (decompose_quotes(s + i + 1, lst, " "));
}

bool	decompose_spaces(t_cell *current, t_cell *prev, t_cell **lst)
{
	int		i;
	char	*s;
	char	**strs;
	t_cell	*cell;

	i = -1;
	cell = NULL;
	if (!current)
		return (false);
	if (current->separator != MSNOTHING)
		return (decompose_spaces(current->next, current, lst));
	s = current->content;
	strs = ft_split(s, " ");
	if (!strs)
		return (true);
	else
		create_multiple_cells(strs, &cell);
	if (prev)
		prev->next = cell;
	else
		*lst = cell;
	while (cell->next)
		cell = cell->next;
	cell->next = current->next;
	free(current->content);
	free(current);
	return (decompose_spaces(cell->next, cell, lst));
}*/

void	ft_exit(char *str)
{
	printf("%s", str);
	exit(0);
}
/*
int		deconstruct(char *s, t_data **dt)
{
	t_cell		*lst;
	t_cell		*prev;
	t_cell		*current;
	char		c;

	lst = NULL;
	//a revoir dans lagestion d' erreur
	c = ' ';
	while (c)
		c = decompose_quotes(s, &lst, c);
	prev = NULL;
	current = lst;
	while (current)
	{
		decompose_spaces(current, prev);
		prev = current;
		current = current->next;
	}
	while (lst)
	{
		printf("lst->c = %s, lst->i = %i, lst->n = %p\n", lst->content, lst->separator, lst->next);
		lst = lst->next;
	}
	//find_replace_var(dt, &lst);
	(void)dt;
	return (0);
}
*/
void	know_your_token(char *s, t_data *dt)
{
	t_token		t;
	int			i = 0;

	while (s[i])
	{
		t = (t_token){0};
		next_token(s + i, &t, dt);
		printf("whats poppin, status = %i, substatus = %i, copy = %s, t_len = %i\n", t.status, t.sub_status, t.copy, t.length);
		if (t.copy)
			free(t.copy);
		if (t.length == 0)
			break ;
		i += t.length;
	}
}

t_data	*parse(char **env)
{
	t_data	*data;
	char	*str;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	*data = (t_data){0};
	data->env = &env;
	come_back_prompt(str, &data);
	return (data);
}
