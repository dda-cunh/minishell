/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:46:27 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/06/30 20:50:40 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../minishell.h"
# include <readline/readline.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

char		**get_cmd(char *s, char **envp);
void		read_write(int from_fd, int to_fd);
int			print_out(int infd, int ac, char **av);
int			init_tmp(int infd, char *delim);
int			cmd_index(int infd);

#endif