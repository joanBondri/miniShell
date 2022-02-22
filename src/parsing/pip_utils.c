/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 05:06:32 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/22 14:40:42 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

t_cmd	*set_cmd_null(t_cmd *buff, char *str)
{
	*buff = (t_cmd){0};
	buff->infile = -1;
	buff->outfile = -1;
	buff->path = str;
	return (buff);
}

void	generate_cmds_strs(t_cmd **pips, char **strs, t_data *dt)
{
	t_cmd	*buff;
	t_cmd	*prev;
	t_cmd	**end;
	int		i;

	end = pips;
	prev = NULL;
	i = -1;
	while (strs[++i])
	{
		buff = ft_malloc_conditional(sizeof(t_cmd));
		if (!buff)
			return ((void)ft_error(MALLOC));
		*end = set_cmd_null(buff, strs[i]);
		buff->prev = prev;
		prev = buff;
		end = &(buff->next);
		buff = NULL;
	}
	dt->nbr_pipe = i - 1;
	free(strs);
	*end = NULL;
}

void	ft_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit (0);
}
