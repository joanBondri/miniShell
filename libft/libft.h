/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 12:31:04 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/22 18:28:02 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_flag
{
	int		first;
	int		second;
	char	c;
	char	padding;
	char	*str;
}				t_flag;

void			*ft_malloc_conditional(size_t len);
void			*ft_malloc_3434(size_t si);
char			*ft_strjoin3(char *s1, char *s2, char *s3);
char			**ft_split2(char const *s, char c);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *s1, const void *s2, size_t n);
void			*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void			*ft_memmove(void *s1, const void *s2, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isspace(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
int				ft_atoi_modified(const char *str, t_flag *list);
long long		ft_atoi(const char *str, int i, long long d, int c);
char			*ft_strdup(const char *s1);
void			*ft_calloc(size_t count, size_t size);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_modif(char const *s,
					char const *s1, char const *s2, int *o);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_itoa(long long n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
int				ft_putchar_fd_returnvalue(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
int				ft_putstr_fd_returnvalue(char *s, int fd, int length);
void			ft_putendl_fd(char *s, int fd);
int				ft_putendlre_fd(char *s, int fd, int ret);
void			ft_putnbr_fd(int n, int fd);
long long		ft_putnbr_fd_returnvalue(long long n, int fd);
int				ft_strcmp(const char *s1, const char *s2);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
char			*ft_convert_base(unsigned long long nbr,
					char *base_from, char *base_to);
void			ft_convert_nbr_base(unsigned long long nbr, char *basei,
					char *nbr_base_to, int *i);
void			ft_size_nbr_base(long nbr, char *base, int *size);
int				ft_is_base_valid(char *base);
int				ft_char_in_base(char c, char *base);
char			*ft_strcapitalize(char *s);
int				ft_strfind(char *str, char c);

#endif
