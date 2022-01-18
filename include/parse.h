#ifndef PARSE_H
# define PARSE_H
# define MSNOTHING 0
# define MSQUOTE 1
# define MSDQUOTE 2
# define MSWHITESPACE 4
# define MSSPACE 3
# define MSFILE 1
# define MSCMD 2
# include <stdbool.h>

typedef struct	s_cell
{
	int				separator;
	int				type;
	char			*content;
	struct s_cell	*next;
}				t_cell;

#endif
