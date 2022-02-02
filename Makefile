SRC = \
		check_errors.c \
		cut_off.c \
		env_finder.c \
		expand.c \
		ft_malloc_idea.c \
		ft_split_func.c \
		get_prompt.c \
		main.c \
		parse.c \
		pip.c \
		redirection.c \

SRCSDIR = ./src

OBJDIR = $(SRCSDIR)/objects

SRCS = ${SRC:%.c=$(SRCSDIR)/%.c}

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I./include/ -I./src/libft/

RM = rm -rf

.c.o :
	$(CC) -g $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	make -C src/libft
	mv src/libft/libft.a ./libft.a
	$(CC) -g -o $(NAME) $(OBJS) libft.a -lreadline

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
