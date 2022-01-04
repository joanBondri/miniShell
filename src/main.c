#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = parse(argc, argv, envp);
	if (!data)
		return (1);
	return (0);
}
