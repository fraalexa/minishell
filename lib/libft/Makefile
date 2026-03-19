cc= cc
NAME=libft.a

flags= -Wall -Wextra -Werror

src= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_strcmp.c ft_isalpha.c ft_strncmp.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c 
Obj= $(src:%.c=%.o)

all: $(NAME)

$(NAME): $(Obj) 
	ar rcs $(NAME) $(Obj)

%.o:%.c 
	$(cc) $(flags) -c $< -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(Obj)