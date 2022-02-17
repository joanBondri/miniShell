/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 04:28:28 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/17 04:29:57 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

void	print_varenv(char *s, int fd, t_data *dt)
{
	s = switch_varenv(s, dt);
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

void	print_error_heredoc(int line, char *del)
{
	printf("minishell: warning: heredocument at line ");
	printf("%d delimited by end-of-file (wanted `%s')\n", line, del);
}

void	determine_content_herdoc(char *del, int fd, t_data *dt)
{
	char	*s;
	int		res;
	int		line;

	line = 0;
	while (true)
	{
		s = NULL;
		line++;
		write(1, "> ", 2);
		res = get_next_line(0, &s);
		rl_on_new_line();
		add_lst_malloc((void *)s);
		if (res == 0)
			return (print_error_heredoc(line, del));
		if (res == -1 || (!ft_strncmp(s, del, ft_strlen(s))
				&& !ft_strncmp(s, del, ft_strlen(del))))
			break ;
		print_varenv(s, fd, dt);
	}
	if (res == -1)
		change_mind("yes", true);
}
