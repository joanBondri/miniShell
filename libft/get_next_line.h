/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:46:29 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/14 16:58:03 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include "libft.h"
# include <unistd.h>
# define BUFFER_SIZE 1000

int		get_next_line(int fd, char **line);
char	*ft_swap_gnl(char *dest, char *src);
int		ft_strlen_gnl(char *s, char c);
int		ft_termine_garcon(char **line, char *keeper, char *wait, int fd);
int		ft_read(int fd, char **wait);
int		ft_check(char *keeper, char c, int size);
char	*ft_strjoin_gnl(char *s1, char *s2, char c);
char	*ft_empty_string(char *s1, char *s2, char c, int m);
#endif
