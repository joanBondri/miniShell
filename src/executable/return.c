/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:36:45 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/10 13:37:57 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	return_value(int status, int change_val)
{
	static int	value;

	if (change_val == 0)
		value = status;
	return (value);
}

void	ft_exit_exec(int val, t_cmd *cmd)
{
	free_all_cmd(cmd);
	exit(val);
}

void	ft_exit_child(int val, t_data *data)
{
	free_all_cmd(data->cmd);
	free_data(data);
	exit(val);
}