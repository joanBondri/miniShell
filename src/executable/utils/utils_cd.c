/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:09:24 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/15 12:09:58 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	free_cd(char *new, char *old, int ret)
{
	free(new);
	free(old);
	return (ret);
}

int	go_to_dir(char *new, char *old)
{
	if (chdir(new) == -1)
	{
		perror("minishell: cd: ");
		return (free_cd(new, old, 1));
	}
	return (0);
}
