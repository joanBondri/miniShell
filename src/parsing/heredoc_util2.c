/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 04:28:28 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/22 19:02:53 by jbondri          ###   ########.fr       */
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

void	print_varenv(char *s, int fd, t_data *dt)
{
	s = switch_varenv(s, dt);
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

int	print_error_heredoc(int line, char *del)
{
	ft_putstr_fd("minishell: warning: heredocument at line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(del, 2);
	ft_putstr_fd("')", 2);
	ft_putstr_fd("\n", 1);
	return_value(0, 0);
	return (0);
}

void	determine_content_herdoc(char *del, int *fd, t_data *dt)
{
	char	*s;
	int		line;

	signal(SIGINT, SIG_DFL);
	line = 0;
	break_loop(true);
	while (break_loop(true))
	{
		s = NULL;
		line++;
		s = readline("> ");
		rl_on_new_line();
		printf("stoooop %p\n", s);
		add_lst_malloc((void *)s);
		if (!s)
			exit(print_error_heredoc(line, del));
		if ((!ft_strncmp(s, del, ft_strlen(s))
				&& !ft_strncmp(s, del, ft_strlen(del))))
			exit(0);
		print_varenv(s, fd[1], dt);
	}
}
