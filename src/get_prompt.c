#include "minishell.h"

char	*get_prompt(void)
{
	char	*sl;

	sl = ft_strdup("minishell>");
	add_list_malloc((void*)sl);
	return (sl);
}

void	come_back_prompt(t_data **data)
{
	char	*str;

	while (true)
	{
		str = readline(get_prompt());
		add_history(str);
		if (!ft_loop_strchr(" \t\v\f", str))
			parser_director(str, data);
		if (str)
			free(str);
		str = NULL;
	}
}
