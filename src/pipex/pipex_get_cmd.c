/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:27:27 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/01 18:12:35 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

static char	*check_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*tmp_path;
	char	*tmp_cmd;
	char	**path;

	i = 0;
	path = get_path(envp);
	while (path[i])
	{
		tmp_path = ft_strjoin(path[i++], "/");
		tmp_cmd = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (!access(tmp_cmd, F_OK))
		{
			free_2d(path);
			return (tmp_cmd);
		}
		free(tmp_cmd);
	}
	free_2d(path);
	return (NULL);
}

char	**get_cmd(char *s, char **envp)
{
	char	**cmd;
	char	*tmp;
	char	*path;

	if (!*s)
		return (NULL);
	cmd = ft_split(s, ' ');
	if (!cmd)
		return (NULL);
	path = check_cmd_path(cmd[0], envp);
	free_2d(cmd);
	if (!path)
		return (NULL);
	tmp = ft_strjoin(path, " ");
	free(path);
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, s);
	free(tmp);
	if (!path)
		return (NULL);
	cmd = ft_split(path, ' ');
	free(path);
	return (cmd);
}
