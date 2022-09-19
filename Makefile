SRC = lexer.c main.c token.c ft_strlen.c ft_strcat.c find_env.c find_in_env.c ft_lstadd_back.c ft_split.c

CFLAGS = -Wall -Wextra -Werror 

NAME = minishell

OBJ = ${SRC:.c=.o}

all : $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include  -fsanitize=address
clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY:	all clean fclean re