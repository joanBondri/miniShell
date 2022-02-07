#include "pip.h"

char	*get_prompt(void)
{
	char	*sl;

	sl = ft_strdup("minishell> ");
	add_lst_malloc((void*)sl);
	return (sl);
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
		ft_all_lst_malloc();
		if (str)
			free(str);
		str = NULL;
	}
}
