/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:13:14 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/15 12:13:23 by xchalle          ###   ########.fr       */
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

int	num_arg_error(t_data *data, t_cmd *cmd)
{	
	(void)data;
	(void)cmd;
	if (data->nbr_cmd == 1)
		ft_putendl_fd("exit", STDERR_FILENO);
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	return (1);
}

int	num_val_error(t_data *data, t_cmd *cmd)
{
	(void)data;
	if (data->nbr_cmd == 1)
		ft_putendl_fd("exit", STDERR_FILENO);
	print_free(ft_strjoin3("minishell: exit: ", cmd->arg[1],
			" : numeric argument required\n"), STDERR_FILENO);
	return (2);
}
