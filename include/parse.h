#ifndef PARSE_H
# define PARSE_H
# define NOTHING 0
# define QUOTE 1
# define DQUOTE 2
# define SPACE 3
# define FILE 1
# define CMD 2

typedef struct	s_cell
{
	int				separator;
	int				type;
	char			*content;
	struct s_cell	*next;
}				t_cell;

#endif
