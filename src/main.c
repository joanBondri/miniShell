#include "pip.h"

int		main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	(void)argc;

	signal(SIGINT, handler_int);
	signal(SIGQUIT, SIG_IGN);
	data = parse(envp);
	if (!data)
		return (1);
	return (0);
}
