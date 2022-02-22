/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:54:04 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/21 11:56:54 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

void	handler_int_parser(int signal)
{
	(void)signal;
	return_value(-117, 0);
}

void	handler_quit_parser(int signal)
{
	(void)signal;
	return_value(-116, 0);
}

void	handler_int_heredoc(int signal)
{
	(void)signal;
	rl_on_new_line();
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line ("", 0);
	rl_redisplay();
	exit(return_value(130, 0));
}
