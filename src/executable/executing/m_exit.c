/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:12:22 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/10 14:12:23 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	exit_arg_1(char *str, t_data *data, t_cmd *cmd)
{
	int	val;
	int	i;

	(void)data;
	(void)cmd;
	i = 0;
	val = atoi_arg(str, &i, 1, 0);
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			return (-1);
		i++;
	}
	if (data->nbr_cmd == 1)
		ft_putendl_fd("exit", STDOUT_FILENO);
	free_data_cmd();
	return ((unsigned int)(val));
}

int	m_exit(t_data *data, t_cmd *cmd)
{
	int	status;
	int	last_status_code;

	last_status_code = 0;
	status = 0;
	if (cmd->arg[1])
	{
		status = check_isvalid_num(cmd->arg[1]);
		if (status == 0)
			exit(exit_arg_1(cmd->arg[1], data, cmd));
		else if (status != 0)
			exit(num_val_error(data, cmd));
		else if (cmd->arg[2])
			exit(num_arg_error(data, cmd));
		else
			return (0);
	}
	else
	{
		if (data->nbr_cmd == 1)
			ft_putendl_fd("exit", STDOUT_FILENO);
		free_data_cmd();
		exit(return_value(0, 1));
	}
	return (status);
}
