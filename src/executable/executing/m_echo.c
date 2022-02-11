/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:15:46 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/10 14:15:48 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	m_echo(t_data *data, t_cmd *cmd)
{
	(void)data;
	int	n_option;
	int	i;

	i = 1;
	n_option = 0;
	if (cmd->arg[1])
	{
		if (cmd->arg[1][0] == '-' && cmd->arg[1][1] == 'n')
		{
			n_option = 1;
			i++;
		}
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
