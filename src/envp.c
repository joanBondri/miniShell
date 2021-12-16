#include "minishell.h"

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
	if (!tbs || !res)
		return (NULL);
	*res = {};
	tbs = ft_split_mnshell(str, "=");
	res->var = tbs[0];
	if (tbs[1] && tbs[1][0] == ':')
		res->val = tbs + 1;
	else
	{
		res->val = ft_split_mnshell(tbs[1], ":");
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

t_env	*list_env(char **var)
{
	t_env	*res;

	--var;
	res = NULL;
	while (*(++var))
	{
		if (!ft_putlst_end_env(*var, &res))
			return (NULL);
	}
	return (res);
}
