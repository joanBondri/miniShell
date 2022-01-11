#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	(void)argc;
	data = parse(envp);
	if (!data)
		return (1);
	return (0);
}
