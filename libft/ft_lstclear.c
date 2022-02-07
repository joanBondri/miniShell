/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:10:36 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 11:09:26 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*t2;

	if (lst == NULL)
		return ;
	tmp = *lst;
	while (tmp)
	{
		t2 = tmp->next;
		(*del)(tmp->content);
		free(tmp);
		tmp = t2;
	}
	*lst = NULL;
}
