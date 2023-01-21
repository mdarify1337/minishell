NAME = minishell
CFLAGS = -Wall -Wextra -Werror
SRC = minishell.c

OSRC = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OSRC)
	$(CC) $(CFLAGS) $(OSRC) -o $(NAME)

clean:
	rm -f $(OSRC) $(OBONUS)
fclean: clean
	rm -f $(NAME)
re: fclean all