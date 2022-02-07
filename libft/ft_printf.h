/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:04:35 by xchalle           #+#    #+#             */
/*   Updated: 2021/05/25 11:22:18 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

int		ft_printf(const char *str, ...);
int		ft_strfind_point(long long first);
int		ft_printer_str(t_flag list, char *s);
int		ft_printer_nbr(t_flag list, long long u);
int		ft_nbrlen(long long nbr);
int		ft_nbrlen_unsigned(long long nbr);
int		complete_before(const char *str, t_flag *list);
void	ft_separate(char *keeper, char *c);
char	*ft_determinate(const char *str);
int		ft_afteresp_str(t_flag list, char *s);
int		ft_afteresp_nbr(t_flag list, long long d);
int		ft_afteresp_adr(t_flag list, char *s, unsigned long long u);
int		ft_afteresp_char(t_flag list);
int		ft_printer_adr(t_flag list, char *u, unsigned long long nbr);
int		ft_find_point(char *str);
int		ft_second(int second, long long u);
void	ft_atooi(char *s, t_flag list);
int		ft_printer_char(t_flag list, long long u);
void	ft_atoooi(char *s, t_flag *list, char *str, long long nbr);
int		in_charset(char c);
char	*ft_replace(char *str, va_list param);
int		ft_pourcent(va_list param, t_flag list, char *str);
int		ft_pourcent4(va_list param, t_flag list, char *str);
int		ft_pourcent2(va_list param, t_flag list, char *str);
int		ft_pourcent3(va_list param, t_flag list, char *str);
int		ft_pourcent5(va_list param, t_flag list, char *str);
void	mal_s(char *s, char *str);

#endif
