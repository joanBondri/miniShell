/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:24:39 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/15 12:25:14 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	(void)argc;
	signal(SIGINT, handler_int);
	signal(SIGQUIT, SIG_IGN);
	data = parse(envp);
	if (!data)
		return (1);
	return (0);
}
