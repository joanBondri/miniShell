#ifndef PIP
# define PIP
# include "minishell.h"
# include "parse.h"

char	**ft_split_func(char *s, char *c,
		bool (check)(char *s, int i, char *c));
char	*ft_strndup(char *s, int size);
void	check_pips(char *s);
char	*ft_strlreplace(char *s1, char *s2, int index, int len);
void	develope_dquote(t_token *t, char *s, t_data *dt);
void	develope_word(t_token *t, char *s);
void	develope_quote(t_token *t, char *s);
void	develope_varenv(t_token *t, char *s, t_data *dt);
void	develope_redirection(t_token *t, char *s);
void	find_type_token(char *tb, char *s, t_token *t, t_data *dt);
void	next_token(char *s, t_token *t, t_data *dt);
void	check_redirection_file(char *str, t_data *dt);
void	check_redirection(char *s, t_data *dt);
bool	entanglement(char *s);
void	check_quotes(char *s);
void	check_errors_cmd(char *s);
/*t_cell	*attribute_cell(char *s, int i, int info);
t_cell *assign_cell(t_cell **lst, t_cell *last);
char decompose_quotes(char *s, t_cell **lst, char comp);
t_cell	*add_space_cell(t_cell *lst);
t_cell	*create_multiple_cells(char **strs, t_cell **lst);
void	chain_cell(t_cell *to_add, t_cell *next, t_cell *prev);*/
bool	only_char(char *start, char *end, char *find);
int is_valid_var(char *str);
int is_correct_export(char **env_val, char *tab_cell, char *str);
char    *find_env(char *var, t_data *data);
int find_index_env(t_data *data, char *str);
int change_val_var(t_data *data, char *str, int i);
int add_var_tab(t_data *data, char *str);
int put_val_tab(t_data *data, char *var, char *new);
int	find_var_par(char *prin, char **res);
int	find_variable_in_str(char *prin, char **res);
char	*get_variable_first_time(char *val, int msg, t_data *dt);
int		expand_variable(char *prin, int ind, char *res, t_data *dt);
char	*quotes_and_variable(char *s, t_data *data);
//void	find_replace(t_data *dt, t_cell **lst);
char	**ft_split_func(char *s, char *c, bool (check)(char *s, int i, char *c));
char	*get_prompt(void);
int		main(int argc, char **argv, char **envp);
/*void	attach_end_lst_cell(t_cell *buff, t_cell **lst);
t_cell	**decompose_quotes(char *s, t_cell **lst, char *comp);*/
void	ft_exit(char *str);
int		deconstruct(char *s, t_data **dt);
t_data	*parse(char **env);
bool	check_pip_double(char *s);
bool	divide_with_quotes(char *str, int index, char *c);
void	generate_cmds_strs(t_cmd **pips, char **strs);
void	divide_pip(char *s, t_data **data);
t_list	**add_lst_malloc(void *mem);
void	*ft_malloc_conditional(size_t len);
void	free_all_lst_malloc(void);
void	free_lst(void);

#endif
