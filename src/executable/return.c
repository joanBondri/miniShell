/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:36:45 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/25 18:32:20 by xchalle          ###   ########.fr       */
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

void	ft_exit_child_one_builtin(int val, t_data *data)
{
	dup2(data->save_out, STDOUT_FILENO);
	dup2(data->save_in, STDIN_FILENO);
	if (data->save_in != -1)
		close(data->save_in);
	if (data->save_out != -1)
		close(data->save_out);
	if (data->cmd->infile != -1)
		close(data->cmd->infile);
	if (data->cmd->outfile != -1)
		close(data->cmd->outfile);
	free_all_cmd(data->cmd);
	free_data(data);
	exit(val);
}
