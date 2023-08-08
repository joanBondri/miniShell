/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:32:31 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/10 15:29:13 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//int	token_error(t_data, char *token)
//{
//    if (ft_strcmp(token, "|"))
//        ft_putendl_fd(
//        "minishell: syntax error near unexpected token `|'", STDERR_FILENO);
//    if (ft_strcmp(token, "<"))
//        ft_putendl_fd(
//        "minishell: syntax error near unexpected token `<'", STDERR_FILENO);
//    if (ft_strcmp(token, ">"))
//        ft_putendl_fd(
//        "minishell: syntax error near unexpected token `>'", STDERR_FILENO);
//    if (ft_strcmp(token, "newline"))
//        ft_putendl_fd("minishell:syntax error
//        near unexpected token `newline'", STDERR_FILENO);
//    if (ft_strcmp(token, "<>"))
//        ft_putendl_fd(
//        "minishell: syntax error near unexpected token `<>'", STDERR_FILENO);
//    free_data_cmd(data, cmd);
//    return (0);
//}

int	ft_error(int number)
{
	if (number == MALLOC)
		ft_putendl_fd("minishell: malloc failed", STDERR_FILENO);
	if (number == OPEN)
		ft_putendl_fd("minishell: open failed", STDERR_FILENO);
	if (number == CLOSE)
		ft_putendl_fd("minishell: close failed", STDERR_FILENO);
	if (number == DUP2)
		ft_putendl_fd("minishell: dup2 failed", STDERR_FILENO);
	if (number == DUP)
		ft_putendl_fd("minishell: dup failed", STDERR_FILENO);
	if (number == FORK)
		ft_putendl_fd("minishell: fork failed", STDERR_FILENO);
	if (number == PIPE)
		ft_putendl_fd("minishell: pipe failed", STDERR_FILENO);
	if (number == EXECVE)
		ft_putendl_fd("minishell: execve failed", STDERR_FILENO);
	return (130);
}
