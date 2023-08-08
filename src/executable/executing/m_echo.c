/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:15:46 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/21 14:03:24 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	good_n_option(char *yop)
{
	int	i;

	i = 1;
	if (ft_strlen(yop) < 2)
		return (0);
	if (yop[0] != '-')
		return (0);
	while (yop[i] && yop[i] == 'n')
		i++;
	if (yop[i] || i == 1)
		return (0);
	return (1);
}

int	m_echo(t_data *data, t_cmd *cmd)
{
	int	n_option;
	int	i;

	(void)data;
	i = 1;
	n_option = 0;
	while (cmd->arg[i])
	{
		if (good_n_option(cmd->arg[i]))
		{
			n_option = 1;
			i++;
		}
		else
			break ;
	}
	while (cmd->arg[i])
	{
		ft_putstr_fd(cmd->arg[i], STDOUT_FILENO);
		if (cmd->arg[++i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (n_option == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
