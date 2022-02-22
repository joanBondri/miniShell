/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:08:30 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/10 14:08:31 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	m_pwd(t_data *data, t_cmd *cmd)
{
	char	*print;
	size_t	lenght;

	(void)data;
	(void)cmd;
	lenght = 512;
	print = NULL;
	print = getcwd(print, lenght);
	while ((!print) && (errno == ERANGE))
	{
		lenght = lenght * 2;
		print = getcwd(print, lenght);
	}
	if (!print)
		perror("minishell: pwd: ");
	if ((!print) && (errno != ERANGE))
		return (0);
	ft_putendl_fd(print, STDOUT_FILENO);
	free(print);
	return (0);
}	
