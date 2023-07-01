/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:43:46 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/01 20:11:40 by dda-cunh         ###   ########.fr       */
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

# define PROMPT "minishell \U00002192  "

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
t_data			*init_shell(char **env);

/*	UTILS FUNCTIONS	*/
int				exit_(int status, t_data *data);

/*		PIPEX		*/
char			**get_cmd(char *s, char **envp);
void			read_write(int from_fd, int to_fd);
int				pipex(t_data *data);
int				print_out(t_data *data);
int				init_tmp(int infd, char *delim);
int				cmd_index(int infd);

#endif
