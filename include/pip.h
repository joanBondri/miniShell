#ifndef PIP
# define PIP
# include "minishell.h"
# include "parse.h"

void	parser_director(char *s, t_data **data);
void	interprate_sequence(t_cmd *buff);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
void	expand_rest_envvar(t_cmd *buff, t_data *dt);
void	no_such_file(char *name);
void	get_2_redirection(char *s, t_cmd *yop, t_token t);
void	get_redirection(char *str, t_cmd *focus, t_data *dt);
void	near_token(char *s, t_data *dt);
void	ambigus_redirect(char *str);
void	assemblage_file_name_red(char *s, t_token *tt,  t_data *dt);
char	*ft_strndup(char *s, int size);
void	check_pips(char *s);
char	*ft_strlreplace(char *s1, char *s2, int index, int len);
void	develope_dquote(t_token *t, char *s, t_data *dt);
void	develope_word(t_token *t, char *s);
void	develope_quote(t_token *t, char *s);
void	develope_varenv(t_token *t, char *s, t_data *dt);
void	develope_redirection(t_token *t, char *s);
void	find_type_token(char *tb, char *s, t_token *t, t_data *dt);
void	ft_unexpected_token(char c, char *s);
void	ft_bad_substitution(char *s);
void	check_par(char *s);
void	next_token(char *s, t_token *t, t_data *dt);
void	check_redirection_file(char *str, t_data *dt);
void	check_redirection(char *str, t_data *dt);
char	entanglement(char *s);
void	check_quotes(char *s);
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
void	replace(char *s, int len, char *res);
char	*quotes_and_variable(char *s, t_data *data);
t_list	**add_lst_malloc(void *mem);
void	*ft_malloc_conditional(size_t len);
void	free_all_lst_malloc(void);
void	ft_nothing(void *mem);
void	free_lst(void);
char	**ft_split_func(char *s, char *c, bool (check)(char *s, int i, char *c));
char	*get_prompt(void);
void	come_back_prompt(t_data **data);
int		main(int argc, char **argv, char **envp);
void	know_your_token(char *s, t_data *dt);
t_data	*parse(char **env);
bool	check_pip_double(char *s);
bool	divide_with_quotes(char *str, int index, char *c);
void	generate_cmds_strs(t_cmd **pips, char **strs);
void	divide_pip(char *s, t_data **data);
bool	change_mind(char *change, bool bo);
void	ft_exit(char *str);

#endif
