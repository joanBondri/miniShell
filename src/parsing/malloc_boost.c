/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_boost.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:00:43 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/25 20:00:46 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

bool	check_tab_string_free(char **yop, void *mem)
{
	int		i;

	if (yop == mem)
		return (true);
	i = 0;
	while (yop[i] && yop[i] != mem)
		i++;
	if (yop[i] == mem)
		return (true);
	return (false);
}

bool	check_t_free(t_data *dt, void *mem)
{
	static t_data	*data = NULL;
	t_cmd			*lst;

	if (dt)
		data = dt;
	if (!mem || !data)
		return (false);
	if (check_tab_string_free(data->env, mem))
		return (true);
	lst = data->cmd;
	while (lst)
	{
		if (check_tab_string_free(lst->arg, mem))
			return (true);
		if (lst->path == mem || lst == mem)
			return (true);
		lst = lst->next;
	}
	return (false);
}

void	free_or_not(void *mem)
{
	if (!check_t_free(NULL, mem))
		free(mem);
}
