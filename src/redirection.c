#include "pip.h"

void	divide_pip(char *s, t_data **data)
{
	char	**strs;
	t_cmd	**pips;

	strs = ft_split_func(s, "|", &divide_with_quotes);
	pips = malloc(sizeof(t_cmd*));
	if (!strs || !pips)
		ft_exit("the end\n");
	*pips = NULL;
	generate_cmds_strs(pips, strs);
	(*data)->cmd = pips;
}
