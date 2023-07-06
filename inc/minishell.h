/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:49:51 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/06 15:43:20 by dda-cunh         ###   ########.fr       */
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

typedef struct s_cmd
{
	char			*bin;
	char			**args;
	char			*infile_path;
	char			*outfile_path;
	bool			here_doc;
	bool			append;
	t_builtin		builtin;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_data
{
	char			**env;
	struct s_cmd	*cmd;
	int				infile;
	int				outfile;
	int				status;
}				t_data;

/*	INIT FUNCTIONS	*/
t_data			*init_shell(char **envi);

/*		MINISHELL	*/
int				minishell(t_data *shell);
int				exec_builtin(t_data **shell, t_cmd cmd);

/*		BUILTINS	*/
int				export_bin(t_data **sh, char **args);
int				unset(t_data **sh, char **args);
int				cd(t_data **shell, char **path);
int				env(t_data **shell, char **args);
int				echo(t_data **shell, char **arg);
int				pwd(t_data **shell, char **arg);
int				exit_bin(t_data **shell, char **arg);

/*	UTILS FUNCTIONS	*/
char			*get_env_val(t_data *shell, const char *var);
int				get_env_index(t_data *shell, const char *env_var);
int				update_env_val(t_data *shell, const char *var,
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


/*		PIPEX		*/
void			read_write(int from_fd, int to_fd);
char			**get_cmd(char *s, char **envp);
int				pipex(t_data *data);
int				print_out(t_data *data);
int				init_tmp(int infd, char *delim);
int				cmd_index(int infd);

/*	GRACEFUL EXIT	*/
void			put_strerror(void);
int				exit_(int status, t_data *data);

#endif