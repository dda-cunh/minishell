/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:49:51 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/03 20:51:27 by dda-cunh         ###   ########.fr       */
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
int				exec_builtin(t_data *shell, t_cmd cmd);

/*		BUILTINS	*/
int				export_bin(t_data **sh, char *var_value);
int				cd(t_data *shell, const char **path);
int				env(t_data *shell);
int				echo(char **arg);
int				pwd(void);

/*	UTILS FUNCTIONS	*/
void			put_strerror(void);
char			*get_env_val(t_data *shell, const char *var);
int				update_env_val(t_data *shell, const char *var,
					const char *new_val);

/*		PIPEX		*/
void			read_write(int from_fd, int to_fd);
char			**get_cmd(char *s, char **envp);
int				pipex(t_data *data);
int				print_out(t_data *data);
int				init_tmp(int infd, char *delim);
int				cmd_index(int infd);

/*	GRACEFUL EXIT	*/
int				exit_(int status, t_data *data);

#endif