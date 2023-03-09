NAME		= MINISHELL
	
CC		= cc
CFLAGS	= -Wall -Wextra -Werror 
RM		= rm -rf

CLEANER		= $(addprefix cleaner/, clean)
MPIPE		= $(addprefix execution/pipex/, command execution  linked pipe)
UTILS		= $(addprefix utils/, ft_split linked_list utils utils1 ft_itoa)
EXPAND		= $(addprefix expander/, expander)
LEXER		= $(addprefix lexer/, lexer lexer_utils)
PARSER		= $(addprefix parser/, parser parser_utils here_doc)
SYNTAX		= $(addprefix check_syntax/, check_quotes syntax_errors)
ENV			= $(addprefix env/, env_operations env_utils env)
BUILTINS	= $(addprefix execution/builtins/, cd_cmd echo_cmd env_cmd exit_cmd export_cmd pwd_cmd unset_cmd  )
FILES		= $(addprefix src/, signals main minishell $(CLEANER) $(MPIPE) $(UTILS) $(SYNTAX) $(ENV) $(LEXER) $(PARSER) $(BUILTINS) $(EXPAND))
OBJ			= $(FILES:=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -L/usr/local/lib -I/usr/local/include -lreadline $(OBJ) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

push:
	@make fclean
	@git add .
	@git commit -m "shell"
	@git push

.PHONY: re fclean clean all
