/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:39:44 by xchalle           #+#    #+#             */
/*   Updated: 2022/02/11 18:20:24 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
//static char	**ft_free20(char **tab, int o)
//{
//	int	i;
//
//	i = 0;
//	while (i < o)
//	{
//		free(tab[i]);
//		i++;
//	}
//	free(tab);
//	return (NULL);
//}
//
//static char	**ft_malloc20(char **tab, const char *str, int compteur, char c)
//{
//	int		k;
//	int		o;
//	int		i;
//
//	i = 0;
//	k = 0;
//	o = 0;
//	while (str[i] && o < compteur)
//	{
//		while (str[i] == c && str[i])
//			i++;
//		k = 0;
//		while (str[i] != c && str[i])
//		{
//			tab[o][k] = str[i];
//			i++;
//			k++;
//		}
//		tab[o][k] = '\0';
//		o++;
//	}
//	tab[o] = 0;
//	return (tab);
//}
//
//static char	**ft_malloc_string20(
//		char **tab, const char *str, int compteur, char c)
//{
//	int		k;
//	int		o;
//	int		i;
//
//	i = 0;
//	k = 0;
//	o = 0;
//	while (str[i] && o < compteur)
//	{
//		k = 0;
//		while (str[i] == c && str[i])
//			i++;
//		while (str[i] != c && str[i])
//		{
//			i++;
//			k++;
//		}
//		tab[o] = malloc(sizeof(char) * (k + 1));
//		if (!(tab[o]))
//			return (ft_free20(tab, o));
//		o++;
//	}
//	return (ft_malloc20(tab, str, compteur, c));
//}
//
//static void	ft_assign20(int *i, int *n, int *compteur)
//{
//	*i = 0;
//	*n = 0;
//	*compteur = 0;
//}
//
//char	**ft_split20(char const *s, char c)
//{
//	int		i;
//	int		n;
//	int		compteur;
//	char	**tab;
//
//	ft_assign20(&i, &n, &compteur);
//	//printf("%s\n",s);
//	if (!s)
//		return (NULL);
//	while (s[i])
//	{
//		n = 0;
//		while (s[i] == c && s[i])
//			i++;
//		while (s[i] != c && s[i])
//		{
//			i++;
//			n++;
//		}
//		if (n > 0)
//			compteur++;
//	}
//	tab = malloc(sizeof(char *) * (compteur + 1));
//	if (!(tab))
//		return (ft_free20(tab, 0));
//	return (ft_malloc_string20(tab, s, compteur, c));
//}

int	pipe_even_c(t_data *data, t_cmd *cmd)
{
	static int	ret[8];

	close(data->pipe_odd[0]);
	if (cmd->infile != -1)
	{
		ret[0] = dup2(cmd->infile, STDIN_FILENO);
		//ret[4] = close(cmd->infile);
	}
	else
	{
		ret[1] = dup2(data->pipe_even[0], STDIN_FILENO);
		//ret[5] = close(data->pipe_even[0]);
	}
	if (cmd->outfile != -1)
	{
		ret[2] = dup2(cmd->outfile, STDOUT_FILENO);
		//ret[6] = close(cmd->outfile);
	}
	else
	{
		ret[3] = dup2(data->pipe_odd[1], STDOUT_FILENO);
		//ret[7] = close(data->pipe_odd[1]);
	}
	if ((ret[0] < 0) || (ret[1] < 0) || (ret[2] < 0) || (ret[3] < 0))
		exit(ft_error(DUP2));
	if ((ret[4] < 0) || (ret[5] < 0) || (ret[6] < 0) || (ret[7] < 0))
		exit(ft_error(CLOSE));
	return (0);
}

int	pipe_odd_c(t_data *data, t_cmd *cmd)
{
	static int	ret[8];

	close(data->pipe_even[0]);
	if (cmd->infile != -1)
	{
		ret[0] = dup2(cmd->infile, STDIN_FILENO);
		//ret[4] = close(cmd->infile);
	}
	else
	{
		ret[1] = dup2(data->pipe_odd[0], STDIN_FILENO);
		//ret[5] = close(data->pipe_odd[0]);
	}
	if (cmd->outfile != -1)
	{
		ret[2] = dup2(cmd->outfile, STDOUT_FILENO);
		//ret[6] = close(cmd->outfile);
	}
	else
	{
		ret[3] = dup2(data->pipe_even[1], STDOUT_FILENO);
		//ret[7] = close(data->pipe_even[1]);
	}
	if ((ret[0] < 0) || (ret[1] < 0) || (ret[2] < 0) || (ret[3] < 0))
		exit(ft_error(DUP2));
	if ((ret[4] < 0) || (ret[5] < 0) || (ret[6] < 0) || (ret[7] < 0))
		exit(ft_error(CLOSE));
	return (0);
}

int	random_pipe_c(t_data *data, t_cmd *cmd, int i)
{
	if ((i % 2) == 0)
		pipe_even_c(data, cmd);
	if ((i % 2) == 1)
		pipe_odd_c(data, cmd);
	return (0);
}

int	last_pipe_c(t_data *data, t_cmd *cmd, int i)
{
	static int	ret[8];

	
	if (i % 2 == 0)
	{
		ret[1] = dup2(data->pipe_even[0], STDIN_FILENO);
		//ret[5] = close(data->pipe_even[0]);
	}
	if (i % 2 == 1)
	{
		ret[2] = dup2(data->pipe_odd[0], STDIN_FILENO);
		//ret[6] = close(data->pipe_odd[0]);
	}
	if (cmd->infile != -1)
	{	
		ret[0] = dup2(cmd->infile, STDIN_FILENO);
		//ret[4] = close(cmd->infile);
	}
	if (cmd->outfile != -1)
	{
		ret[3] = dup2(cmd->outfile, STDOUT_FILENO);
		//ret[7] = close(cmd->outfile);
	}
	if ((ret[0] < 0) || (ret[1] < 0) || (ret[2] < 0) || (ret[3] < 0))
		exit(ft_error(DUP2));
	if ((ret[4] < 0) || (ret[5] < 0) || (ret[6] < 0) || (ret[7] < 0))
		exit(ft_error(CLOSE));
	return (0);
}

int	one_pipe_close(t_data *data, t_cmd *cmd)
{
	static int	ret[2];

	(void)data;
	if (cmd->infile != -1)
	{
		//ret[0] = dup2(cmd->infile, STDIN_FILENO);
		ret[0] = close(cmd->infile);
	}
	if (cmd->outfile != -1)
	{
		//ret[1] = dup2(cmd->outfile, STDOUT_FILENO);
		ret[1] = close(cmd->outfile);
	}
	//if ((ret[0] < 0) || (ret[1] < 0))
	//	exit(ft_error(DUP2));
	if ((ret[0] < 0) || (ret[1] < 0))
		exit(ft_error(CLOSE));
	return (0);
}

int	one_pipe_dup(t_data *data, t_cmd *cmd)
{
	static int	ret[2];

	(void)data;
	if (cmd->infile != -1)
	{
		ret[0] = dup2(cmd->infile, STDIN_FILENO);
		//ret[2] = close(cmd->infile);
	}
	if (cmd->outfile != -1)
	{
		printf("aiiaiaaiai\n");
		ret[1] = dup2(cmd->outfile, STDOUT_FILENO);
		//ret[3] = close(cmd->outfile);
	}
	if ((ret[0] < 0) || (ret[1] < 0))
		exit(ft_error(DUP2));
	//if ((ret[2] < 0) || (ret[3] < 0))
	//	exit(ft_error(CLOSE));
	return (0);
}

int	first_pipe_c(t_data *data, t_cmd *cmd)
{
	static int	ret[7];

	if (data->nbr_pipe != 0)
		ret[6] = close(data->pipe_odd[0]);
	if (cmd->infile != -1)
	{
		ret[0] = dup2(cmd->infile, STDIN_FILENO);
		//ret[5] = close(cmd->infile);
	}
	if (cmd->outfile != -1)
	{
		ret[1] = dup2(cmd->outfile, STDOUT_FILENO);
		//ret[3] = close(cmd->outfile);
	}
	else if (data->nbr_pipe > 0)
	{
		ret[2] = dup2(data->pipe_odd[1], STDOUT_FILENO);
		//ret[4] = close(data->pipe_odd[1]);
	}
	//ret[0] = -1;
	if ((ret[0] < 0) || (ret[1] < 0) || (ret[2] < 0))
		exit(ft_error(DUP2));
	if ((ret[4] < 0) || (ret[5] < 0) || (ret[3] < 0) || (ret[6] < 0))
		exit(ft_error(CLOSE));
	return (0);
}

void	fd_pipe_child(t_data *data, t_cmd *cmd, int i)
{
	if (i == 0)
		first_pipe_c(data, cmd);
	else if (i == data->nbr_cmd - 1)
		last_pipe_c(data, cmd, i);
	else
		random_pipe_c(data, cmd, i);
}

void	first_pipe_p(t_data *data, t_cmd *cmd)
{
	if (data->nbr_pipe != 0)
		close(data->pipe_odd[1]);
	if (cmd->infile != -1)
		close(cmd->infile);
	if (cmd->outfile != -1)
		close(cmd->outfile);
}

void	random_pipe_p(t_data *data, t_cmd *cmd, int i)
{
	if (i % 2 == 0)
	{
		close(data->pipe_even[0]);
		close(data->pipe_odd[1]);
	}
	else
	{
		close(data->pipe_even[1]);
		close(data->pipe_odd[0]);
	}
	if (cmd->infile != -1)
		close(cmd->infile);
	if (cmd->outfile != -1)
		close(cmd->outfile);
}

void	last_pipe_p(t_data *data, t_cmd *cmd, int i)
{
	if (i % 2 == 0)
	{
		close(data->pipe_even[0]);
	}
	else
	{
		close(data->pipe_odd[0]);
	}
	if (cmd->infile != -1)
		close(cmd->infile);
	if (cmd->outfile != -1)
		close(cmd->outfile);
}

void	fd_pipe_parent(t_data *data, t_cmd *cmd, int i)
{
	if (i == 0)
	{
		first_pipe_p(data, cmd);
	}
	else if (i == data->nbr_cmd - 1)
	{
		last_pipe_p(data, cmd, i);
	}
	else
		random_pipe_p(data, cmd, i);
}

void	piper(t_data *data, int i)
{
	if (i == data->nbr_cmd - 1)
	{
		return ;
	}
	else if ((i % 2 == 0))
	{
		if (pipe(data->pipe_odd) < 0)
			exit(ft_error(PIPE));
	}
	else
	{
		if (pipe(data->pipe_even) < 0)
			exit(ft_error(PIPE));
	}
}

int	loop_exec(t_data *data, t_cmd *cmd, int i, char **path)
{
	int	child;
	int	wstatus;
	int	value;

	i++;
	piper(data, i);
	printf("cmd == %d\n", data->nbr_cmd);
	printf("pipe == %d\n", data->nbr_pipe);
	if (data->nbr_cmd == 1 && is_builtin(cmd->arg[0]) == 1)
	{
		one_pipe_dup(data, cmd);
		return_value(call_builtin(data, cmd, 0), 0);
		one_pipe_close(data, cmd);
		return (return_value(0, 1));
	}
	child = fork();
	if (child == -1)
		exit(ft_error(FORK));
	else if (child == 0)
	{
		//if (data->nbr_pipe != 0)
		fd_pipe_child(data, cmd, i);
		if (is_builtin(cmd->arg[0]) == 1)
		{
			value = call_builtin(data, cmd, 0);
			if (value > -1)
			{
				if (i == data->nbr_cmd - 1)
					return_value(value, 0);
				exit(return_value(0, 1));
			}
		}
		else
		{
			if (put_prepath(cmd, path) == 0)
			{
				print_free(ft_strjoin3("minishell: ", cmd->arg[0],
						": command not found\n"), STDERR_FILENO);
				close_fd(cmd);
				exit(return_value(126, 0));
			}
			else
				exec_check(data, cmd);
			if (execve(cmd->arg[0], cmd->arg, data->env) == -1)
				exit(ft_error(EXECVE));
		}
	}
	else
	{
		fd_pipe_parent(data, cmd, i);
		if (i < data->nbr_cmd - 1)
		{
			loop_exec(data, cmd->next, i, path);
		}
		waitpid(child, &wstatus, 0);
		if (WIFEXITED(wstatus))
		{
			//if (WIFSIGNALED)
			value = WEXITSTATUS(wstatus);//error_code
			//if (value == 130)
			//	exit(ft_error(130));
		}
	}
	if (i == data->nbr_cmd - 1)
		return_value(value, 0);
	return (return_value(0, 1));
}

int	exec_data(t_data *data, t_cmd *cmd)
{
	int		i;
	int		value;
	char	**path;

	i = 0;
	while (data->env[i])
	{
		//printf("%s\n", data->env[i]);
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	path = ft_split2(data->env[i] + 5, ':');
	if (!path)
		exit(ft_error(MALLOC));
	i = -1;
	value = loop_exec(data, cmd, i, path);
	free_tab(path);
	return (return_value(0, 1));
}
