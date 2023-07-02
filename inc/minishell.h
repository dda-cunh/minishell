/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:49:51 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/02 20:47:11 by dda-cunh         ###   ########.fr       */
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

typedef struct s_data
{
	char			**env;
	struct s_cmd	*cmd;
	int				infile;
	int				outfile;
	int				status;
}				t_data;

typedef struct s_cmd
{
	char			*bin;
	char			**args;
	char			*infile_path;
	char			*outfile_path;
	bool			here_doc;
	bool			append;
	struct s_cmd	*next;
}				t_cmd;

/*	INIT FUNCTIONS	*/
t_data			*init_shell(char **envi);

/*		MINISHELL	*/
int				minishell(t_data *shell);


/*		BUILTINS	*/
int				export_bin(t_data **sh, char *var_value);
int				env(t_data *shell);
int				pwd(t_data *shell);

/*	UTILS FUNCTIONS	*/
int				update_env_val(t_data *shell, const char *var,
					const char *new_val);
char			*get_env_val(t_data *shell, const char *var);

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