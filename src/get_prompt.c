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

	str = readline(get_prompt());
	add_history(str);

	know_your_token(str, data);
}
