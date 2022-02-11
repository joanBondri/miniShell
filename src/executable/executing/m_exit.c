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

int	check_isvalid_num(char *str)
{
	int	i;
	int	v;

	i = 0;
	v = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i + v] >= '0' && str[i + v] <= '9')
		v++;
	while (str[i + v])
	{
		if (ft_isspace(str[i + v]) == 0)
			return (1);
		i++;
	}
	if (v > 18)
		return (1);
	return (0);
}

int	atoi_arg(char *str, int *i, int sign, int val)
{
	while (ft_isspace(str[*i]) == 1)
		*i += 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		*i += 1;
	}
	while (str[*i] == '0')
		*i += 1;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		val = val * 10 + str[*i] - '0';
		*i += 1;
	}
	return ((unsigned int)(val * sign));
}

int	exit_arg_1(char *str, t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
	int	val;
	int	i;

	i = 0;
	val = atoi_arg(str, &i, 1, 0);
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			return (-1);
		i++;
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_data_cmd();
	return ((unsigned int)(val));
}

int	num_arg_error(t_data *data, t_cmd *cmd)
{	
	(void)data;
	(void)cmd;
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
	free_data_cmd();
	return (2);
}

int	num_val_error(t_data *data, t_cmd *cmd)
{
	(void)data;
	ft_putendl_fd("exit", STDERR_FILENO);
	print_free(ft_strjoin3("bash: exit: ", cmd->arg[1],
			" : numeric argument required\n"), STDERR_FILENO);
	free_data_cmd();
	return (2);
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
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(last_status_code);
	}
	return (status);
}
