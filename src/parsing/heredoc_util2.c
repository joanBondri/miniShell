/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 04:28:28 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/18 01:53:55 by jbondri          ###   ########.fr       */
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
	// close(fd);
}

int	print_error_heredoc(int line, char *del)
{
	printf("minishell: warning: heredocument at line ");
	printf("%d delimited by end-of-file (wanted `%s')\n", line, del);
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
		add_lst_malloc((void *)s);
		if (!s)
			exit(print_error_heredoc(line, del));
		if ((!ft_strncmp(s, del, ft_strlen(s))
				&& !ft_strncmp(s, del, ft_strlen(del))))
			exit(0);
		print_varenv(s, fd[1], dt);
	}
}
