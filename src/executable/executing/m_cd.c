/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:34:44 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/10 16:26:00 by xchalle          ###   ########.fr       */
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
		if (errno == ENOENT)
			print_free(ft_strjoin3("minishell: cd: ", new,
					": Aucun fichier ou dossier de ce type\n"), STDERR_FILENO);
		return (free_cd(new, old, 1));
	}
	return (0);
}

int	m_cd(t_data *data, t_cmd *cmd)
{
	char	*old;
	char	*new;
	int		lenght;

	old = NULL;
	if (cmd->arg[1] && cmd->arg[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	lenght = 512;
	old = getcwd(old, lenght);
	while ((!old) && (errno == ERANGE))
	{
		lenght = lenght * 2;
		old = getcwd(old, lenght);
	}
	if (!old)
		old = ft_strdup("");
	if (cmd->arg[1])
		new = ft_strdup(cmd->arg[1]);
	else
		new = find_env("HOME", data);
	if (!new)
		return (free_cd(new, old, 1));
	if (go_to_dir(new, old) == 1)
		return (1);
	new = realloc(new, lenght);
	new = getcwd(new, lenght);
	while ((!new) && (errno == ERANGE))
	{
		lenght = lenght * 2;
		new = realloc(new, lenght);
		new = getcwd(new, lenght);
	}
	if (!new)
		return (free_cd(new, old, 1));
	if (put_val_tab(data, "PWD", new) == -1)
		return (free_cd(new, old, 1));
	if (put_val_tab(data, "OLDPWD", old) == -1)
		return (free_cd(new, old, 1));
	return (free_cd(new, old, 0));
}
