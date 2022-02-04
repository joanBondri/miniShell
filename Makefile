SRC = \
		parsing/check_errors.c \
		parsing/env_finder.c \
		parsing/expand.c \
		parsing/ft_malloc_idea.c \
		parsing/ft_split_func.c \
		parsing/get_prompt.c \
		main.c \
		parsing/parse.c \
		parsing/pip.c \

SRCSDIR = ./src

OBJDIR = $(SRCSDIR)/objects

SRCS = ${SRC:%.c=$(SRCSDIR)/%.c}

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -I./include/ -I./src/libft/

RM = rm -rf

.c.o :
	$(CC)  $(CFLAGS) -c $< -o ${<:.c=.o}

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
