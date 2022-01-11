SRC = envp.c \
	  get_prompt.c \
	  main.c \
	  parse.c \
	  cut_off.c \

SRCSDIR = ./src

OBJDIR = $(SRCSDIR)/objects

SRCS = ${SRC:%.c=$(SRCSDIR)/%.c}

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -I./include/ -I./src/libft/

RM = rm -rf

.c.o :
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	make -C src/libft
	mv src/libft/libft.a ./libft.a
	$(CC) -o $(NAME)  $(OBJS) libft.a -lreadline

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
