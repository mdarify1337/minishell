/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:10:22 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/09 18:09:31 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
#include <fcntl.h>
 #include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define STDIN_FILE 0
# define STDOUT_FILE 1

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
}			t_state;

typedef enum e_token
{
	WORD,
	WHITE_SPACE = ' ',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
}			t_oken;

// struct for env
typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
	struct s_env_node	*previous;
}			t_env_node;

typedef struct s_env
{
	t_env_node	*first;
	t_env_node	*last;
}			t_env;

typedef struct s_element
{
	char					*content;
	int						len;
	enum e_token			type;
	enum e_state			state;
	struct s_element		*next;
	struct s_element		*previous;
}				t_element;

typedef struct s_list
{
	t_element	*first;
	t_element	*last;
}				t_list;

// typedef struct s_direc
// {
// 	int					fd;
// 	char		*file;
// }				t_direc;

// struct for commands
/*

typedef struct s_cmd
{
	int				i_fd;
	int				o_fd;
	char			*cmd_line;
	char			*f_error;
	char			**cmd_option;
	char			**files;
	struct s_cmd	*next;
}					t_cmd;
*/

typedef struct s_norm
{
	int				count;
	int				(*fd)[2];
	int				i;
	int				status;
	int				start;
	int				end;
	int				proc;
	int				*pid;
}					t_mounaji;

typedef struct e_cmd_node
{
	char				*args;
	char				**cmd_;
	int					fcd;
	int					io_in;
	int					io_out;
	char				*ferror;
	struct e_cmd_node	*next;
}				t_cmd_node;

typedef	struct s_darify
{
	int			exit_status;
	t_env		*fenv;
	t_cmd_node	*f_command;
}	t_darify;
t_darify		fcode;
// MINISHELL: ------->execution
char	**env_arr(t_env_node *env);
void	pwd(void);
void	ft_echo(char **s);
void	ft_exit(char **ex);
int		env_cmd(t_env	*env);
int		unset_cmd(t_env *env, char *key);	
int		fcommand_built(t_cmd_node *command);
int		fcalcule_size(t_cmd_node *command);
void	export_cmd(t_env	*env, char **arg);
void    ft_execution_command(t_cmd_node   *command, t_env *env);
void	flinked_execution_pipex(t_cmd_node *shell, t_env *env);
void	flinked_send_error(int l, char	*command);
void	fcd_command_line(char **paths, t_env *env);
void	flinked_execution_command(t_cmd_node *command, t_env *env);
void	fexecute_command(t_cmd_node	*minishell, char	**path, char **env);
void	fchild_command_execution(t_cmd_node *data, t_env *env, t_mounaji *val);
int		fbuilt_check_command(t_cmd_node *info, t_env  *env);
int		fcheck_execv_builtin(t_cmd_node *info, t_env   *env);

// MINISHELL: ------->parsing

void		minishell(char **env);
void		ft_cmdadd_back(t_cmd_node **lst, t_cmd_node *new);
t_list		*init_tokens(t_list *list);
int			get_word(t_list *tokens, char *str, enum e_state state);
t_element	*ft_lstnew(char *content, int len, enum e_token type, \
enum e_state state);
t_list		*lexer(char *line);
char		**ft_split(char const *s, char c);
void		ft_lstadd_back(t_list **list, t_element *new);
int			in_charset(char c);
int			ft_strisspace(char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_is_alpha(char c);
void		minishell(char **env);
int			ft_isspace(char c);
t_element	*skip_space(t_element *elm, int flag);
int			ft_strcmp(char *s1, char *s2);
void		quotes_state(t_list *tokens, char *str, enum e_state *state, \
enum e_token state2);
int			ft_readline(char **line);
int			tokenize_redir(t_list *tokens, char *str, int i,\
enum e_state *state);
int			get_env_var(t_list *tokens, char *str, enum e_state state);
int			is_alphanum(int c);
void		ft_expand(t_list **lst, t_env *env);
int			check_syntax(t_list *lst);
int			is_closed_quote(t_element *elm);
int			check_quotes(t_list	*lst);
int			ft_strchr(char *s, char c);
int			is_redirection(t_element *elm);
size_t		ft_strlen(const char *s);
char		*ft_substr(char *s, int start, int len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(char *str);
t_env		*ft_init_env(char **env);
t_env_node	*env_new(char *env);
void		add_env(t_env **env_list, t_env_node *node);
int			delete_node_by_key(t_env_node *head, char *key);
void		insert_to_tail(t_env_node **tail, t_env_node *node);
t_env_node	*search_by_key(t_env_node *head, char *key);
int			unset_cmd(t_env *env, char *key);
t_cmd_node	*parse_command(t_list **list);
char		*ft_realloc(char *old, char *new);
void		update_redirection(t_cmd_node *cmd, t_element *elm);
int			is_pipe(t_element *elm);
int			ft_lstsize(t_env_node *lst);	
void		ft_split_args(t_cmd_node **args);
int			check_key(char *key);
int			execute_here_doc(t_list **list);
char		*ft_itoa(int n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		init_signals(void);
void		ft_cmd_cleaner(t_cmd_node *node);
void		free_2d_array(char **ar);
void		ft_env_cleaner(t_env_node *lst);
void		env_free(t_env_node *lst);
void		ft_lexer_cleaner(t_list *lst);
void		ft_parsing_cleaner(t_list *lst, t_cmd_node *node, t_env *env);

#endif