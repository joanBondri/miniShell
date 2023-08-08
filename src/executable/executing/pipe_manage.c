/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:21:32 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/21 11:21:45 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	fd_pipe_child(t_data *data, t_cmd *cmd, int i)
{
	if (i == 0)
		first_pipe_c(data, cmd);
	else if (i == data->nbr_cmd - 1)
		last_pipe_c(data, cmd, i);
	else
		random_pipe_c(data, cmd, i);
}

void	fd_pipe_parent(t_data *data, t_cmd *cmd, int i)
{
	if (i == 0)
	{
		first_pipe_p(data, cmd);
	}
	else if (i == data->nbr_cmd - 1)
	{
		last_pipe_p(data, cmd, i);
	}
	else
		random_pipe_p(data, cmd, i);
}

void	piper(t_data *data, int i)
{
	if (i == data->nbr_cmd - 1)
	{
		return ;
	}
	else if ((i % 2 == 0))
	{
		if (pipe(data->pipe_odd) < 0)
			ft_exit_child(ft_error(PIPE), data);
	}
	else
	{
		if (pipe(data->pipe_even) < 0)
			ft_exit_child(ft_error(PIPE), data);
	}
}

int	pipe_fork(t_data *data, int i, int child)
{
	piper(data, i);
	child = fork();
	if (child == -1)
		ft_exit_child(ft_error(FORK), data);
	return (child);
}
