SRC = \
		parsing/check_errors.c \
		parsing/expand.c \
		parsing/ft_malloc_idea.c \
		parsing/ft_split_func.c \
		parsing/get_prompt.c \
		main.c \
		parsing/parse.c \
		parsing/heredoc.c \
		parsing/pip.c \
		signal/handler.c \
		executable/envp.c \
		executable/error.c \
		executable/executing/exec.c \
		executable/executing/io_builtin.c \
		executable/executing/child_pipe.c \
		executable/executing/parent_pipe.c \
		executable/utils/utils_cd.c \
		executable/executing/m_cd.c \
		executable/executing/m_echo.c \
		executable/executing/m_env.c \
		executable/utils/utils_exit.c \
		executable/executing/m_exit.c \
		executable/utils/utils_export.c \
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

CFLAGS = -Wall -Wextra -Werror -I./include/ -I./libft/ -I./src/libft/ -fsanitize=address -g3

RM = rm -rf

.c.o :
	$(CC)  $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	make -C libft
	mv libft/libft.a ./libft.a
	$(CC) -o $(NAME) $(OBJS) libft.a -lreadline -fsanitize=address -g3

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
