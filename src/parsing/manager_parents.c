/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_parents.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:45:28 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/21 15:49:16 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

int	manage_parent(int pip[2])
{
	int			wstatus;

	close(pip[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(0, &wstatus, 0);
	if (WIFSIGNALED(wstatus) == 1
		&& (WTERMSIG(wstatus) == 2 || WTERMSIG(wstatus) == 3))
	{
		ft_putendl_fd("", STDOUT_FILENO);
		return_value(WTERMSIG(wstatus) + 128, 0);
		change_mind("yes", true);
		return (0);
	}
	return (1);
}

int	manage_pid(int pip[2], t_cmd *buff)
{
	pipe(pip);
	if (pip[0] == -1 || pip[1] == -1)
		return (error_pip());
	if (buff->infile != -1)
		close(buff->infile);
	buff->infile = pip[0];
	return (80);
}
