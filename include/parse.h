#ifndef PARSE_H
# define PARSE_H
# define MSNOTHING 0
# define MSQUOTE 1
# define MSDQUOTE 2
# define MSWHITESPACE 4
# define MSSPACE 3
# define MSFILE 1
# define MSCMD 2
# define MSPIP 0
# define MSRED_HER 1
# define MSRED_APP 2
# define MSRED_OUT 3
# define MSRED_IN 4
# define MSVOID 80
# define MSNONE 81
# define MSAMBIGOUS 82
# define MSAMBIGOUSL 83
# define MSAMBIGOUSR 84
# define MSAMBIGOUSLR 85
# include <stdbool.h>

typedef struct	s_cell
{
	int				separator;
	int				type;
	char			*content;
	struct s_cell	*next;
}				t_cell;

typedef struct	s_token
{
	char		*start;
	char		copy;
	int			length;
	int			status;
	int			sub_status;
}				t_token;

#endif
