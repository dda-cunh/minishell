/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:52:22 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/08 19:23:36 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_out(t_cmd *cmd)
{
	int		tmp;
	int		outfd;

	tmp = open("tmp", O_RDONLY);
	outfd = 1;
	if (cmd->append)
		outfd = open(cmd->outfile_path,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		if (cmd->outfile_path)
			outfd = open(cmd->outfile_path,
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfd == -1)
	{
		close(tmp);
		return (2);
	}
	ft_read_write_fd(tmp, outfd);
	close(outfd);
	return (0);
}

static void	here_doc(char *delim, int tmp)
{
	char	*a;
	size_t	biggest;
	size_t	alen;

	a = "";
	while (a)
	{
		ft_putstr_fd(">>> ", 1);
		a = get_next_line(STDIN_FILENO);
		if (!a)
			break ;
		alen = ft_strlen(a) - 1;
		if (alen >= ft_strlen(delim))
			biggest = alen;
		else
			biggest = ft_strlen(delim);
		if (!ft_strncmp(a, delim, biggest))
		{
			free(a);
			break ;
		}
		ft_putstr_fd(a, tmp);
		free(a);
	}
}

int	init_tmp(char	*inpath, char *delim)
{
	int		infd;
	int		tmp;

	tmp = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (tmp == -1)
		return (2);
	infd = 0;
	if (!delim)
	{
		infd = open(inpath, O_RDONLY, 0777);
		if (infd == -1)
			return (2);
	}
	if (infd)
		ft_read_write_fd(infd, tmp);
	else
		here_doc(delim, tmp);
	close(tmp);
	return (0);
}
