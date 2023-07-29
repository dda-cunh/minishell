/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:24:37 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/11 16:39:14 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**get_path(char **envp)
{
	int		i;

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
	while (path && path[i])
	{
		tmp_path = ft_strjoin(path[i++], "/");
		if (!tmp_path)
			return (NULL);
		tmp_cmd = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (!tmp_cmd)
			return (NULL);
		if (!access(tmp_cmd, F_OK))
		{
			free_2d(path);
			return (tmp_cmd);
		}
		free(tmp_cmd);
	}
	free_2d(path);
	return (ft_strdup(cmd));
}

static char	*builtin_bin(char *s)
{
	char	*function;

	function = NULL;
	if (!ft_strncmp(s, "echo", 5))
		function = ft_strdup("echo");
	else if (!ft_strncmp(s, "cd", 3))
		function = ft_strdup("cd");
	else if (!ft_strncmp(s, "pwd", 4))
		function = ft_strdup("pwd");
	else if (!ft_strncmp(s, "export", 7))
		function = ft_strdup("export");
	else if (!ft_strncmp(s, "unset", 6))
		function = ft_strdup("unset");
	else if (!ft_strncmp(s, "env", 4))
		function = ft_strdup("env");
	else if (!ft_strncmp(s, "exit", 5))
		function = ft_strdup("exit");
	return (function);
}

char	*get_bin(char *s, char **envp)
{
	char	**cmd;
	char	*bin;

	bin = NULL;
	if (s && *s)
	{
		bin = builtin_bin(s);
		if (bin)
			return (bin);
		cmd = ft_split(s, ' ');
		if (!cmd)
			return (NULL);
		if (!access(cmd[0], F_OK))
			bin = ft_strdup(cmd[0]);
		else
			bin = check_cmd_path(cmd[0], envp);
		free_2d(cmd);
	}
	return (bin);
}
