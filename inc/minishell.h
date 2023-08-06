/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:49:51 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/06 05:56:03 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>
# include <time.h>
# include "libft/libft.h"

# define ANSI_CYAN	"\x1b[36m"
# define ANSI_RESET	"\x1b[0m"
# define ANSI_GREEN	"\x1b[32m"
# define ANSI_RED	"\x1b[31m"

# define EXIT_OK	"\u2714"
# define EXIT_KO	"\u2718"
# define PROMPT		" minishell \u2192  "

# define HD_PROMPT	"\x1b[36mmini\x1b[31mhell\x1b[0m<>> "

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
	int				infd;
	int				outfd;
	int				pipe[2];
	struct s_redir	*redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_data
{
	char			**env;
	struct s_cmd	*cmd;
	char			*tmp_path;
	bool			sigint;
	unsigned char	status;
}				t_data;

/*	INIT FUNCTIONS	*/
t_data			*get_shell(void);
t_data			*init_shell(char **envi);
void			update_shlvl(t_data **shell);
void			reset_pwd(t_data **shell);

/*		SIGNALS		*/
void			main_sig_handler(int sig);
void			heredoc_sig_handler(int sig);
void			exec_sig_handler(int sig);
int				rl_sig_event(void);

/*		MINISHELL	*/
void			expander(t_data *shell, char **tokens);
char			*get_bin(char *s, char **envp);
int				minishell(t_data *shell);

/*		BUILTINS	*/
int				export_bin(t_data **sh, char **args);
void			print_sorted_env(t_data *shell);
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
bool			redir_has_direction(t_redir *redir, char direction);

/*	TOKEN MASKS		*/
int				set_mask(char *str, char quote, char tkn);
void			unset_mask(char *str, char tkn);
void			trim_quotes(t_data *shell, char **args);

/*		LEXER		*/
char			**lex_line(t_data *shell, char *in_line);
void			print_tkn_err(char tkn);
bool			valid_redirect(char *line);
bool			valid_quotes(char *line);
bool			valid_tkn(char tkn);
bool			valid_tkns(char *line);
int				find_next_quote(char *line, char quote);
int				redir_found(char *line, char tkn);

/*		PARSER		*/
t_cmd			*parse_tokens(t_data **shell, char **tokens);
char			*manage_redirects(t_cmd *cmd, char *tkns);

/*		PIPEX		*/
char			**get_cmd(char *s, char **envp);
void			do_close(t_cmd *cmd);
int				get_cmd_in(t_data *shell, t_redir *redir);
int				get_cmd_out(t_redir *redir, t_cmd *cmd);
int				pipeline(t_data *shell, t_cmd *cmd);
int				pipex(t_data **shell, t_cmd *cmd);
int				cmd_index(int infd);
int				dupper(t_cmd *cmd);

/*	GRACEFUL EXIT	*/
t_cmd			*free_cmd(t_cmd *cmd);
void			put_strerror(char *arg, bool print_strerror);
int				exit_(int status, t_data *shell);

#endif