#include "pip.h"

void	free_tab(char **s)
{
	int		i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

char	*ft_loop_strchr(const char *str, char *c)
{
	char	*res;
	int		i;

	i = -1;
	if (!str || !c)
		return (NULL);
	while (c[++i])
	{
		res = ft_strchr(str, c[i]);
		if (res == NULL)
			break ;
	}
	return (res);
}

void	come_back_prompt(t_data **data)
{
	char	*str;
	char	**env;

	while (true)
	{
		env = (*data)->env;
		(**data) = (t_data){0};
		(*data)->env = env;
		str = readline("minishell> ");
		add_history(str);
		if (!ft_loop_strchr(" \t\v\f", str))
			parser_director(str, data);
		free_all_lst_malloc();
		if (str)
			free(str);
		str = NULL;
	}
}
