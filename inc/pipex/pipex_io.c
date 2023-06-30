/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:52:22 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/06/30 19:25:16 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_write(int from_fd, int to_fd)
{
	char	*a;

	a = "";
	while (a)
	{
		a = readline(from_fd);
		if (!a)
			break ;
		ft_putstr_fd(a, to_fd);
		free(a);
	}
	close(from_fd);
}

int	print_out(int infd, int ac, char **av)
{
	int		tmp;
	int		outfd;

	tmp = open("tmp", O_RDONLY);
	if (!infd)
		outfd = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		outfd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0777);
	if (outfd == -1)
	{
		close(tmp);
		return (2);
	}
	read_write(tmp, outfd);
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
		a = readline(STDIN_FILENO);
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

int	init_tmp(int infd, char *delim)
{
	int		tmp;

	tmp = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (tmp == -1)
		return (2);
	if (infd)
		read_write(infd, tmp);
	else
		here_doc(delim, tmp);
	close(tmp);
	return (0);
}
