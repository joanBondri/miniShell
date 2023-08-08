/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 07:18:16 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/22 18:41:36 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

enum	e_builtin
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET
};

enum	e_error
{
	MALLOC,
	OPEN,
	CLOSE,
	DUP2,
	FORK,
	PIPE,
	EXECVE,
	DUP
};

typedef struct s_cmd
{
	bool			change_in;
	char			*path;
	char			**arg;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}		t_cmd;

typedef struct s_data
{
	int		nbr_pipe;
	int		pipe_even[2];
	int		pipe_odd[2];
	char	**env;
	char	**path;
	int		nbr_cmd;
	int		return_value;
	int		save_in;
	int		save_out;
	t_cmd	*cmd;
}		t_data;

int		parent_process(t_data *data, int i, int child);
void	free_all_cmd(t_cmd *cmd);
void	free_data(t_data *data);
void	free_lst(void);
void	ft_exit_exec(int val, t_cmd *cmd);
void	ft_exit_child(int val, t_data *data);
void	ft_exit_child_one_builtin(int val, t_data *data);
void	print_all(void);
void	exec_builtin(t_data *data, t_cmd *cmd, int i);
void	exec_other_cmd(t_data *data, t_cmd *cmd, char **path);
void	come_back_prompt(t_data **data);
bool	break_loop(bool yop);
void	handler_int_child(int signal);
void	handler_int_heredoc(int signal);
void	handler_int_parser(int signal);
void	handler_quit_parser(int signal);
int		atoi_arg(char *str, int *i, int sign, int val);
void	last_pipe_p(t_data *data, t_cmd *cmd, int i);
void	random_pipe_p(t_data *data, t_cmd *cmd, int i);
void	first_pipe_p(t_data *data, t_cmd *cmd);
int		pipe_even_c(t_data *data, t_cmd *cmd);
int		pipe_odd_c(t_data *data, t_cmd *cmd);
int		random_pipe_c(t_data *data, t_cmd *cmd, int i);
int		last_pipe_c(t_data *data, t_cmd *cmd, int i);
int		first_pipe_c(t_data *data, t_cmd *cmd);
int		one_pipe_dup(t_data *data, t_cmd *cmd);
int		one_pipe_close(t_data *data, t_cmd *cmd);
int		free_cd(char *new, char *old, int ret);
int		go_to_dir(char *new, char *old);
bool	ft_trim(char *s, char c);
t_data	*get_data(t_data *dt);
int		ft_error(int number);
int		return_value(int status, int i);
void	print_env(t_data *data);
void	free_data_cmd(void);
int		close_fd(t_cmd *cmd);
void	exec_cmd(t_data *data, t_cmd *cmd, char **path, int i);
void	parent_fork(t_data *data, t_cmd *cmd, int i, int child);
void	print_free(char *str, int fd);
void	exec_check(t_data *data, t_cmd *cmd);
void	handler_int(int signal);
void	handler_quit_child(int signal);
int		put_val_tab(t_data *data, char *var, char *new);
int		put_val_tab_existing(t_data *data, char *var, char *new);
int		one_builtin(t_data *data, t_cmd *cmd);
int		is_builtin(char *str);
char	*find_env(char *var, t_data *data);
int		add_var_tab(t_data *data, char *str);
int		change_val_var(t_data *data, char *str, int i);
int		print_export_error(char *str);
int		print_export_error_free(char *str, char **tab);
void	print_tab(t_data *data, int *tab, int lenght, int i);
int		loop_exec(t_data *data, t_cmd *cmd, int i, char **path);
void	free_data_cmd2(t_data *data);
void	iteration_export(int *iter, int lenght, int *tab, t_data *data);
int		case_not_existing(t_data *data, char **env_val, char *tab_cell);
void	print_export_env(t_data *data);
bool	check_t_free(t_data *dt, void *mem);
void	free_or_not(void *mem);
void	free_lst_conditionnal(void);
bool	check_tab_string_free(char **yop, void *mem);
char	**free_tab(char **tab);
int		call_builtin(t_data *data, t_cmd *cmd, int i);
int		put_prepath(t_data *data, t_cmd *cmd, char **path);
int		loop_path(char **path, char **cmd);
int		abs_path(t_cmd *cmd);
int		m_unset(t_data *data, t_cmd *cmd);
void	print_error_unset(char *str);
int		remove_var_tab(t_data *data, char *var);
char	**fill_new_tab(t_data *data, int index, char **temp);
int		m_pwd(t_data *data, t_cmd *cmd);
int		m_export(t_data *data, t_cmd *cmd);
int		is_strjoin(char **env_val, char *tab_cell, char *str, t_cmd *cmd);
int		m_exit(t_data *data, t_cmd *cmd);
int		num_val_error(t_data *data, t_cmd *cmd);
int		num_arg_error(t_data *data, t_cmd *cmd);
int		exit_arg_1(char *str, t_data *data, t_cmd *cmd);
int		check_isvalid_num(char *str);
int		m_env(t_data *data, t_cmd *cmd);
int		m_echo(t_data *data, t_cmd *cmd);
int		m_cd(t_data *data, t_cmd *cmd);
void	piper(t_data *data, int i);
void	fd_pipe_parent(t_data *data, t_cmd *cmd, int i);
void	fd_pipe_child(t_data *data, t_cmd *cmd, int i);
int		first_pipe_c(t_data *data, t_cmd *cmd);
int		last_pipe_c(t_data *data, t_cmd *cmd, int i);
int		random_pipe_c(t_data *data, t_cmd *cmd, int i);
int		pipe_odd_c(t_data *data, t_cmd *cmd);
int		pipe_even_c(t_data *data, t_cmd *cmd);
int		find_index_env(t_data *data, char *str);
int		is_correct_export(char **env_val, char *tab_cell, char *str);
int		is_valid_var(char *str);
int		exec_data(t_data *data, t_cmd *cmd);
void	free_all_lst_malloc(void);
bool	change_mind(char *change, bool bo);
bool	in_child(bool change, bool changement);

#endif
