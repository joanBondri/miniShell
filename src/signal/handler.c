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

void	handler_int_child(int signal)
{
	(void)signal;
	//kill(-1, SIGTERM);
	rl_on_new_line();
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line ("", 0);
	rl_redisplay();
	// rl_redisplay();
	exit(return_value(130, 0));
}

void	handler_int_heredoc(int signal)
{
	(void)signal;
	//kill(-1, SIGTERM);
	rl_on_new_line();
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line ("", 0);
	rl_redisplay();
	// rl_redisplay();
	exit(return_value(130, 0));
}

void	handler_int(int signal)
{
	t_data *data;

	data = get_data(NULL);
	(void)signal;
	rl_on_new_line();
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line ("", 0);
	rl_redisplay();
	// rl_redisplay();
	// change_mind("yes", true);
	// break_loop(false);
	return_value(130, 0);
	// come_back_prompt(&data);
	// parse(data->env);
}

void	handler_quit(int signal)
{
	(void)signal;
	rl_on_new_line();
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line ("", 0);
	rl_redisplay();
	exit(return_value(131, 0));
}
