/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:46:25 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/18 01:38:32 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

void	handler_int(int signal)
{
	(void)signal;
	rl_on_new_line();
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line ("", 0);
	rl_redisplay();
	return_value(130, 0);
}

void	handler_int_child(int signal)
{
	(void)signal;
	rl_on_new_line();
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line ("", 0);
	rl_redisplay();
	exit(return_value(130, 0));
}

void	handler_quit_child(int signal)
{
	(void)signal;
	rl_on_new_line();
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line ("", 0);
	rl_redisplay();
	exit(return_value(131, 0));
}
