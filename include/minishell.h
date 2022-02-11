#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <readline/readline.h>
//#include <readline/history.h>

enum	builtin
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET
};

enum	error
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

typedef struct	s_cmd
{
	char		*path;
	char		**arg;
	int		infile;
	int		outfile;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}		t_cmd;

typedef struct	s_data
{
	int	nbr_pipe;
	int	pipe_even[2];
	int	pipe_odd[2];
	char	**env;
	int	nbr_cmd;
	int	return_value;
	int	save_in;
	int	save_out;
	t_cmd	*cmd;
}		t_data;

t_data	*get_data(t_data *dt);
int	ft_error(int number);
int	return_value(int status, int i);
void	print_env(t_data *data);
void	free_data_cmd(void);
int	close_fd(t_cmd *cmd);
void    print_free(char *str, int fd);
void	exec_check(t_data *data, t_cmd *cmd);
void	handler_int(int signal);
void	handler_quit(int signal);
int	put_val_tab(t_data *data, char *var, char *new);
int	is_builtin(char *str);
char	*find_env(char *var, t_data *data);
int	add_var_tab(t_data *data, char *str);
int	change_val_var(t_data *data, char *str, int i);
void	print_export_error(char *str);
char	**free_tab(char **tab);
int	call_builtin(t_data *data, t_cmd *cmd, int i);
int	put_prepath(t_cmd *cmd, char **path);
int	loop_path(char **path, char **cmd);
int	abs_path(t_cmd *cmd);
int	m_unset(t_data *data, t_cmd *cmd);
void	print_error_unset(char *str);
int	remove_var_tab(t_data *data, char *var);
char	**fill_new_tab(t_data *data, int index, char **temp);
int	m_pwd(t_data *data, t_cmd *cmd);
int	m_export(t_data *data, t_cmd *cmd);
void	print_export_error(char *str);
int	m_exit(t_data *data, t_cmd *cmd);
int	num_val_error(t_data *data, t_cmd *cmd);
int	num_arg_error(t_data *data, t_cmd *cmd);
int	exit_arg_1(char *str, t_data *data, t_cmd *cmd);
int	check_isvalid_num(char *str);
int	m_env(t_data *data, t_cmd *cmd);
int	m_echo(t_data *data, t_cmd *cmd);
int	m_cd(t_data *data, t_cmd *cmd);
void	piper(t_data *data, int i);
void	fd_pipe_parent(t_data *data, t_cmd *cmd, int i);
void	fd_pipe_child(t_data *data, t_cmd *cmd, int i);
int	first_pipe_c(t_data *data, t_cmd *cmd);
int	last_pipe_c(t_data *data, t_cmd *cmd, int i);
int	random_pipe_c(t_data *data, t_cmd *cmd, int i);
int	pipe_odd_c(t_data *data, t_cmd *cmd);
int	pipe_even_c(t_data *data, t_cmd *cmd);
int	find_index_env(t_data *data, char *str);
int	is_correct_export(char **env_val, char *tab_cell, char *str);
int	is_valid_var(char *str);
int	exec_data(t_data *data, t_cmd *cmd);

#endif
