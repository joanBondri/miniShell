/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 04:28:28 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/25 20:31:36 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

bool	break_loop(bool yop)
{
	bool		swap;
	static bool	not_end = true;

	swap = not_end;
	not_end = yop;
	return (swap);
}

void	print_varenv(char **s, int fd, t_data *dt)
{
	switch_varenv(s, dt);
	write(fd, *s, ft_strlen(*s));
	write(fd, "\n", 1);
}

void	ft_2_exit(int num, char *s, t_data *dt)
{
	free_all_lst_malloc();
	if (dt->env)
		free_tab(dt->env);
	free(dt);
	if (s)
		free(s);
	exit(num);
}

int	print_error_heredoc(t_data *data, int line, char *del)
{
	ft_putstr_fd("minishell: warning: heredocument at line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(del, 2);
	ft_putstr_fd("')", 2);
	ft_putstr_fd("\n", 1);
	return_value(0, 0);
	ft_2_exit(0, NULL, data);
	return (0);
}

void	determine_content_herdoc(char *del, int *fd, t_data *dt)
{
	char	*s;
	int		line;

	close(fd[0]);
	signal(SIGINT, SIG_DFL);
	line = 0;
	while (true)
	{
		s = NULL;
		line++;
		s = readline("> ");
		rl_on_new_line();
		if (!s)
			exit(print_error_heredoc(dt, line, del));
		if ((!ft_strncmp(s, del, ft_strlen(s))
				&& !ft_strncmp(s, del, ft_strlen(del))))
			ft_2_exit(0, s, dt);
		print_varenv(&s, fd[1], dt);
		free(s);
	}
}
