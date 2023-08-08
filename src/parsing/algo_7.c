/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 07:04:27 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/22 18:59:46 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*buff1;
	char	*buff2;

	if (!s1 && !s2 && !s3)
		return (NULL);
	buff1 = ft_strjoin_mod23(s1, s2);
	buff2 = ft_strjoin_mod23(buff1, s3);
	free(buff1);
	return (buff2);
}

char	**stop_stack_arg(t_list **one)
{
	char	**strs;
	t_list	*buff;
	int		i;

	strs = malloc(sizeof(char *) * (ft_lstsize(*one) + 1));
	add_lst_malloc(strs);
	if (!strs)
		return (NULL);
	buff = *one;
	strs[ft_lstsize(*one)] = NULL;
	i = ft_lstsize(*one) - 1;
	while (buff && i > -1)
	{
		strs[i] = (char *)buff->content;
		buff = buff->next;
		i--;
	}
	*one = NULL;
	return (strs);
}

char	**add_lst_arg(char *mem, bool stop_stack)
{
	static t_list	*one = NULL;
	t_list			*buff;

	if (!mem && !stop_stack)
		one = NULL;
	else if (mem)
	{
		buff = ft_lstnew(mem);
		add_lst_malloc(buff);
		ft_lstadd_front(&one, buff);
	}
	if (!stop_stack)
		return (NULL);
	return (stop_stack_arg(&one));
}

void	expand_rest_envvar(t_cmd *buff, t_data *dt)
{
	int		i;
	char	*buff_s;
	t_token	t;

	i = 0;
	while (buff->path[i])
	{
		t = (t_token){0};
		next_token(buff->path + i, &t, dt);
		if (t.status == MSVARENV)
		{
			buff_s = ft_strlreplace(buff->path, t.copy, i, t.length);
			add_lst_malloc(buff_s);
			i += ft_strlen(t.copy);
			buff->path = buff_s;
		}
		else
			i += t.length;
	}
}

void	no_such_file(char *name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_all_lst_malloc();
	return_value(1, 0);
	change_mind("yes", true);
}
