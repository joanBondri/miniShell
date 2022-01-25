#ifndef PIP
# define PIP
# include "minishell.h"
# include "parse.h"

char	**ft_split_func(char *s, char *c,
		bool (check)(char *s, int i, char *c));
void	ft_exit(char *str);
t_data	*parse(char **env);
char	*get_prompt();
void	divide_pip(char *s, t_data **data);

bool	only_char(char *start, char *end, char *find);
void	chain_cell(t_cell *to_add, t_cell *next, t_cell *prev);
t_cell	*decompose_spaces(t_cell *current, t_cell *prev);
char decompose_quotes(char *s, t_cell **lst, char comp);
bool	check_pip_double(char *s);

#endif
