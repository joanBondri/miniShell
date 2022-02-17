/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 04:40:05 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/17 05:09:46 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

bool	check_pip_double(char *s)
{
	int		i;

	i = 0;
	if (ft_strchr(" \t\v\f\n", s[i]))
	{
		while (s[i] && ft_strchr(" \t\v\f\n", s[i]))
			i++;
		if (s[i] == '|')
			return (true);
	}
	while (s[++i])
	{
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

int	count_double_tab(char **strs)
{
	int		i;

	i = 0;
	while (strs[i])
	{
		add_lst_malloc((void *)strs[i]);
		i++;
	}
	return (i);
}

void	divide_pip(char *s, t_data **data)
{
	char	**strs;
	t_cmd	**pips;

	strs = ft_split_func(s, "|", &divide_with_quotes);
	pips = malloc(sizeof(t_cmd *));
	if (!strs || !pips)
		return ((void)ft_error(MALLOC));
	*pips = NULL;
	(*data)->nbr_cmd = count_double_tab(strs);
	generate_cmds_strs(pips, strs, *data);
	if (change_mind("no", false))
		return ;
	(*data)->cmd = *pips;
	free(pips);
}
