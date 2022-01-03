#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BUFFER_SIZE 100
# define OK 1
# define ERROR -1
# define END 0
# define ALL_LINE -1

int		is_n(char c);
char	*create_newline(char ***line, char *x);
int		assign(char ***line, char *x);
int		recurs(int fd, char **line);
int		get_next_line(int fd, char **line);
void	decaler(int res, char *x);
int		assign_new_line(char ***line, char *x, char *new_line);
#endif
