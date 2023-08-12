/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:22:57 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/12 19:34:11 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	get_tmp(t_redir **redir)
{
	char	*path;
	int		fd;

	path = get_tmp_path(redir);
	fd = open(path, O_RDWR | O_CREAT, 0777);
	free(path);
	return (fd);
}
