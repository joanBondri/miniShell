/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbondri <jbondri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 06:59:48 by jbondri           #+#    #+#             */
/*   Updated: 2022/02/17 07:00:33 by jbondri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define MSNOTHING 0
# define MSWHITESPACE 8
# define MSSPACE 3
# define MSFILE 1
# define MSCMD 2

# define MSPIP 0
# define MSRED_HER 1
# define MSRED_APP 2
# define MSRED_IN 3
# define MSRED_OUT 4
# define MSQUOTE 5
# define MSDQUOTE 6
# define MSVARENV 7

# define MSVOID 80
# define MSNONE 81
# define MSAMBIGOUS 82
# define MSAMBIGOUSL 83
# define MSAMBIGOUSR 84
# define MSAMBIGOUSLR 85
# define MSWORD 86
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

typedef struct s_cell
{
	int				separator;
	int				type;
	char			*content;
	struct s_cell	*next;
}				t_cell;

typedef struct s_token
{
	char		*start;
	char		*copy;
	int			length;
	int			status;
	int			sub_status;
}				t_token;

#endif
