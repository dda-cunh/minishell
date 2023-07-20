/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:49:51 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/20 17:48:03 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>
# include "libft/libft.h"

# define ANSI_CYAN	"\x1b[36m"
# define ANSI_RESET	"\x1b[0m"
# define ANSI_GREEN	"\x1b[32m"
# define ANSI_RED	"\x1b[31m"

# define EXIT_OK	"\u2714"
# define EXIT_KO	"\u2718"
# define PROMPT		" minishell \u2192  "

# define VALID_TKNS "|> <$/\'?\"=_-."

# define BADCMD_ERR	": command not found"
# define SHLVL_ERR	"minishell: shell level (1000) too high, resetting to 1\n"


typedef enum e_builtin
{
	NOTBUILTIN = 0,
	ECHO = 1,
	CD = 2,
	PWD = 3,
	EXPORT = 4,
	UNSET = 5,
	ENV = 6,
	EXIT = 7
}			t_builtin;


typedef struct s_redir
{
	char			*name;
	char			direction;
	bool			dbl_tkn;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd
{
	char			*bin;
	char			**args;
	t_builtin		builtin;
	struct s_redir	*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_data
{
	char			**env;
	struct s_cmd	*cmd;
	int				infile;
	int				outfile;
	char			*tmp_path;
	unsigned char	status;
}				t_data;

/*	INIT FUNCTIONS	*/
t_data			*init_shell(char **envi);

/*		MINISHELL	*/
void			expander(t_data *shell, char **tokens);
char			*get_bin(char *s, char **envp);
int				exec_builtin(t_data **shell, t_cmd cmd);
int				minishell(t_data *shell);

/*		BUILTINS	*/
int				export_bin(t_data **sh, char **args);
int				unset(t_data **sh, char **args);
int				cd(t_data **shell, char **path);
int				env(t_data **shell, char **args);
int				echo(t_data **shell, char **arg);
int				pwd(t_data **shell, char **arg);
int				exit_bin(t_data **shell, char **arg);

/*	EXEC_BUILTINS	*/
t_builtin		is_builtin(char *bin);
int				exec_builtin(t_data **shell, t_cmd cmd);

/*	UTILS FUNCTIONS	*/
char			*get_env_val(t_data *shell, const char *var);
int				get_env_index(t_data *shell, const char *env_var);
int				update_env_val(t_data **shell, const char *var,
					const char *new_val, bool should_create);
/*		LEXER		*/
char			**lex_line(t_data *shell, char *in_line);
void			print_tkn_err(char tkn);
bool			valid_redirect(char *line);
bool			valid_quotes(char *line);
bool			valid_tkn(char tkn);
bool			valid_tkns(char *line);
int				find_next_quote(char *line, char quote);
int				redir_found(char *line, char tkn);

/*		Parser		*/
t_cmd			*parse_tokens(t_data **shell, char **tokens);
char			*manage_redirects(t_cmd *cmd, char *tkns);

/*		PIPEX		*/
char			**get_cmd(char *s, char **envp);
int				init_tmp(t_data *shell, t_redir *redir);
int				print_out(t_data *shell, t_redir *redir, t_cmd *next);
int				pipex(t_data **data, t_cmd *cmd);
int				cmd_index(int infd);

/*	GRACEFUL EXIT	*/
t_cmd			*free_cmd(t_cmd *cmd);
void			put_strerror(void);
int				exit_(int status, t_data *data);

#endif