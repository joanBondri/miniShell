/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 06:53:08 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/25 20:31:58 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIP_H
# define PIP_H
# include "minishell.h"
# include "parse.h"
# include "libft.h"
# include "get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

char	*switch_varenv(char **str, t_data *dt);
void	print_varenv(char **s, int fd, t_data *dt);
char	*ft_exit_malloc(void);
int		print_error_heredoc(t_data *data, int line, char *del);
char	**stop_stack_arg(t_list **one);
void	determine_content_herdoc(char *del, int *fd, t_data *dt);
char	*next_del(char *s, t_token *tt, t_data *dt);
void	handler_int(int signal);
void	do_all_heredoc(t_data *dt);
char	*ft_loop_strchr(const char *str, char *c);
int		is_valid_var(char *str);
int		is_correct_export(char **env_val, char *tab_cell, char *str);
char	*find_env(char *var, t_data *data);
int		find_index_env(t_data *data, char *str);
int		change_val_var(t_data *data, char *str, int i);
int		add_var_tab(t_data *data, char *str);
int		put_val_tab(t_data *data, char *var, char *new);
int		find_var_par(char *prin, char **res);
int		find_variable_in_str(char *prin, char **res);
char	*get_variable_first_time(char *val, int msg, t_data *dt);
int		expand_variable(char *prin, int ind, char *res, t_data *dt);
void	replace(char *s, int len, char *res);
char	*quotes_and_variable(char *s, t_data *data);
t_list	**add_lst_malloc(void *mem);
void	*ft_malloc_conditional(size_t len);
void	free_all_lst_malloc(void);
void	ft_nothing(void *mem);
void	free_lst(void);
char	**ft_split_func(char *s, char *c,
			bool (check)(char *s, int i, char *c));
char	*get_prompt(void);
void	come_back_prompt(t_data **data);
void	know_your_token(char *s, t_data *dt);
t_data	*parse(char **env);
bool	check_pip_double(char *s);
bool	divide_with_quotes(char *str, int index, char *c);
void	generate_cmds_strs(t_cmd **pips, char **strs, t_data *dt);
void	divide_pip(char *s, t_data **data);
void	ft_exit(char *str);
char	*ft_strjoin_mod23(char const *str1, char const *str2);
void	parser_director_2(char *s, t_data **dt);
int		parser_director(char *s, t_data **dt);
bool	ft_trim(char *s, char c);
int		manage_parent(int pip[2]);
int		error_pip(void);
int		manage_pid(int pip[2], t_cmd *buff);
void	interprate_sequence(t_cmd *buff, t_data *dt);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
char	**add_lst_arg(char *mem, bool stop_stack);
void	expand_rest_envvar(t_cmd *buff, t_data *dt);
void	no_such_file(char *name);
void	get_3_redirection(char *s, t_cmd *yop, t_token t);
void	get_2_redirection(char *s, t_cmd *yop, t_token t);
void	temp_function_get_redir(char *str, int i, t_data *dt, t_cmd *focus);
void	get_redirection(t_cmd *focus, t_data *dt);
void	near_token(char *s, t_data *dt);
void	ambigus_redirect(char *s);
char	*assemblage_concateneur(char *s1);
bool	assem_2(char *s, t_data *dt, int *i);
void	assemblage_file_name_red(char *s, t_token *tt, t_data *dt);
void	next_token_2(char *s, t_token *t, t_data *dt);
char	*ft_strndup(char *s, int size);
void	check_pips(char *s);
char	*ft_strlreplace(char *s1, char *s2, int index, int len);
void	yop(char *s, int i, t_data *dt, t_token *t);
void	develope_dquote(t_token *t, char *s, t_data *dt);
void	develope_word(t_token *t, char *s);
void	develope_quote(t_token *t, char *s);
char	*interrog(void);
void	set_null_token_varenv(t_token *t);
void	insultant(char *res, t_token *t);
void	develope_varenv(t_token *t, char *s, t_data *dt);
void	develope_redirection(t_token *t, char *s);
void	find_type_token(char *tb, char *s, t_token *t, t_data *dt);
void	change_interrog(int res);
void	ft_unexpected_token(char c, char *s);
void	print_bad_sub(char *res);
void	ft_bad_substitution(char *s);
void	check_par(char *s);
void	next_token(char *s, t_token *t, t_data *dt);
int		check_redirection_file(char *str, t_data *dt);
void	check_redirection(char *str, t_data *dt);
char	etranglement(char *s, bool *q, bool *dq);
char	entanglement(char *s);
void	check_quotes(char *s);

#endif
