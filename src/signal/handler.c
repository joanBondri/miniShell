/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:46:25 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/15 11:48:00 by xchalle          ###   ########.fr       */
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
}

void	handler_quit(int signal)
{
	handler_int(signal);
}
