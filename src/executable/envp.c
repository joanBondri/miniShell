/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:42:25 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/10 14:42:27 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*char	*get_env(char *var, t_env *lst)
{
	t_env	*buff;

	buff = match_lstenv(var, lst);
	return (buff->val[0]);
}

//tu mets en la variable et la liste
t_env	*match_lstenv(char *var, t_env *lst)
{
	t_env	*buff;

	buff = lst;
	while (buff)
	{
		if (!ft_strncmp(buff->var, var, ft_strlen(var)))
			return (buff);
	}
	return ((t_env*)NULL);
}

t_env	*ft_lstfind_last(t_env **lst)
{
	if (!lst || !*lst)
		return (NULL);
	if (!((*lst)->next))
		return (*lst);
	return (ft_lstfind_last(&((*lst)->next)));
}

void	*ft_putlst_end_env(char *str, t_env **lst)
{
	t_env	*res;
	t_env	*buff;
	char	**tbs;

	if (!lst)
		return (NULL);
	res = malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	*res = (t_env){0};
	tbs = ft_first_split(str, "=");
	res->var = tbs[0];
	if (tbs[1] && tbs[1][0] == ':')
		res->val = tbs + 1;
	else
	{
		//a revoir pour le cas ou l' argument se finit par un :
		res->val = ft_split(tbs[1], ":");
		if (tbs[1] && !(res->val))
		{
			free(res);
			free(tbs);
			return (NULL);
		}
	}
	if (!*lst)
	{
		*lst = res;
		return (res);
	}
	buff = ft_lstfind_last(lst);
	buff->next = res;
	res->prev = buff;
	return (res);
}

//fonction principale, tu lui fout les env
t_env	**list_env(char **var)
{
	t_env	**res;

	--var;
	res = malloc(sizeof(t_env*));
	if (!res)
		return (NULL);
	*res = NULL;
	while (*(++var))
	{
		if (!ft_putlst_end_env(*var, res))
			return (NULL);
	}
	return (res);
}*/
