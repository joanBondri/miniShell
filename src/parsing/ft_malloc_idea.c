/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_idea.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:35:14 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/25 20:10:26 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pip.h"

t_list	**add_lst_malloc(void *mem)
{
	static t_list	*one = NULL;
	t_list			*yop;

	if (mem)
	{
		yop = ft_lstnew(mem);
		ft_lstadd_back(&one, yop);
	}
	return (&one);
}

void	*ft_malloc_conditional(size_t len)
{
	void	*mem;

	mem = malloc(len);
	if (mem)
		add_lst_malloc(mem);
	return (mem);
}

void	print_all(void)
{
	t_list	**all;
	t_list	*tmp;

	all = add_lst_malloc(NULL);
	tmp = *all;
	while (tmp)
		tmp = tmp->next;
}

void	free_all_lst_malloc(void)
{
	t_list	**all;

	all = add_lst_malloc(NULL);
	ft_lstclear(all, free);
	*all = NULL;
}

void	free_lst_conditionnal(void)
{
	t_list	**all;

	all = add_lst_malloc(NULL);
	ft_lstclear(all, &free_or_not);
	*all = NULL;
}
