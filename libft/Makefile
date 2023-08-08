OBJS = $(SRC:.c=.o)


SRC = 	ft_lstadd_back.c\
ft_atoi.c \
ft_atoi_modif.c \
ft_bzero.c \
ft_calloc.c \
ft_convert_base2.c \
ft_convert_base.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_isspace.c \
ft_itoa.c \
ft_lstadd_back.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstdelone.c \
ft_lstiter.c \
ft_lstlast.c \
ft_lstmap.c \
ft_lstnew.c \
ft_lstsize.c \
ft_memccpy.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_printf2.c \
ft_printf3.c \
ft_printf4.c \
ft_printf5.c \
ft_printf6.c \
ft_printf.c \
ft_putchar_fd.c \
ft_putchar_returnvalue.c \
ft_putendl_fd.c \
ft_putendlre_fd.c \
ft_putnbr_fd.c \
ft_putnbr_returnvalue.c \
ft_putstr_fd.c \
ft_putstr_returnvalue.c \
ft_split2.c \
ft_split.c \
ft_strchr.c \
ft_strcmp.c \
ft_strdup.c \
ft_strfind.c \
ft_strjoin3.c \
ft_strjoin.c \
ft_strjoin_modif.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
get_next_line.c \
get_next_line_utils.c

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

.c.o :
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
