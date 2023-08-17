/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:22:57 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/17 16:51:12 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_dir(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
		return (0);
	closedir(dir);
	return (1);
}

bool	redir_has_direction(t_redir *redir, char direction)
{
	if (!redir)
		return (false);
	while (redir)
	{
		if (redir->direction == direction)
			return (true);
		redir = redir->next;
	}
	return (false);
}

static char	*get_tmp_path(t_redir **redir)
{
	char	*redir_addr;
	char	*path;

	redir_addr = ft_itoa(**(int **)redir);
	if (!redir_addr)
		return (ft_strdup("tmp/BADFILE"));
	path = ft_strjoin("/tmp/minihell_tmp", redir_addr);
	free(redir_addr);
	if (!path)
		return (ft_strdup("tmp/BADFILE"));
	return (path);
}

int	get_tmp(t_data *shell, t_redir **redir)
{
	char	*path;
	int		tmp;

	path = get_tmp_path(redir);
	tmp = open(path, O_WRONLY | O_CREAT, 0777);
	here_doc(shell, (*redir)->name, tmp);
	close(tmp);
	tmp = open(path, O_RDONLY, 0777);
	free(path);
	return (tmp);
}
