SRC = \
		parsing/check_errors.c \
		parsing/expand.c \
		parsing/ft_malloc_idea.c \
		parsing/ft_split_func.c \
		parsing/get_prompt.c \
		main.c \
		parsing/parse.c \
		parsing/malloc_boost.c \
		parsing/heredoc.c \
		parsing/heredoc_util1.c \
		parsing/heredoc_util2.c \
		parsing/pip.c \
		parsing/manager_parents.c \
		parsing/algo_1.c \
		parsing/algo_2.c \
		parsing/algo_3.c \
		parsing/algo_4.c \
		parsing/algo_5.c \
		parsing/algo_6.c \
		parsing/algo_7.c \
		parsing/algo_8.c \
		parsing/pip_utils.c \
		signal/handler.c \
		signal/handler_parsing.c \
		executable/envp.c \
		executable/error.c \
		executable/executing/exec.c \
		executable/executing/cmd_exec.c \
		executable/executing/io_builtin.c \
		executable/executing/pipe_manage.c \
		executable/executing/child_pipe.c \
		executable/executing/parent_pipe.c \
		executable/utils/utils_cd.c \
		executable/executing/m_cd.c \
		executable/executing/m_echo.c \
		executable/executing/m_env.c \
		executable/utils/utils_exit.c \
		executable/executing/m_exit.c \
		executable/utils/utils_export.c \
		executable/utils/utils_export2.c \
		executable/executing/m_export.c \
		executable/executing/m_pwd.c \
		executable/executing/m_unset.c \
		executable/executing/utils_exec.c \
		executable/free.c \
		executable/print.c \
		executable/return.c \
		executable/utils/env_finder2.c \
		executable/utils/env_finder.c \
		executable/utils/fd_generator.c \
		executable/utils/free.c

SRCSDIR = ./src

OBJDIR = $(SRCSDIR)/objects

SRCS = ${SRC:%.c=$(SRCSDIR)/%.c}

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -I./include/ -I./libft/ -I./src/libft/ -I/usr/local/Cellar/readline/8.2.1/include/

RM = rm -rf

.c.o :
	$(CC)  $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	make -C libft
	mv libft/libft.a ./libft.a
	$(CC) -o $(NAME) $(OBJS) libft.a -L/usr/local/Cellar/readline/8.2.1/lib/ -lreadline

all: $(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
