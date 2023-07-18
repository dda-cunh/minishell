/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:17:11 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/12 18:47:27 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	update_shlvl(t_data **shell)
{
	int		shlvl;
	char	*s_shlvl;

	s_shlvl = get_env_val(*shell, "SHLVL");
	if (!s_shlvl)
		shlvl = 0;
	else
	{
		shlvl = ft_atoi(s_shlvl);
		free(s_shlvl);
	}
	if (shlvl >= 999)
	{
		ft_putendl_fd(SHLVL_ERR, 2);
		shlvl = 0;
	}
	s_shlvl = ft_itoa(shlvl + 1);
	update_env_val(shell, "SHLVL", s_shlvl, true);
	free(s_shlvl);
	return ;
}

static void	reset_pwd(t_data **shell)
{
	char	*dir;

	printf("resetting pwd\n");
	dir = getcwd(NULL, 0);
	printf("dir = %s\n", dir);
	if (!dir)
		exit_(-1, *shell);
	update_env_val(shell, "PWD", dir, true);
	free(dir);
}

static void	update_env(t_data **shell)
{
	update_shlvl(shell);
	if (get_env_index(*shell, "PWD") < 0)
		reset_pwd(shell);
}

static char	**copy_envi(char **envi)
{
	char	**minish_envi;
	int		i;

	minish_envi = ft_calloc(len_2d(envi) + 1, sizeof(char *));
	if (!minish_envi)
		return (NULL);
	i = 0;
	while (envi[i])
	{
		minish_envi[i] = ft_strdup(envi[i]);
		if (!minish_envi[i])
		{
			free_2d(minish_envi);
			return (NULL);
		}
		i++;
	}
	minish_envi[i] = NULL;
	return (minish_envi);
}

static int	set_tmp(t_data **shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit_(errno, *shell);
	(*shell)->tmp_path = ft_strjoin(cwd, "/.tmp");
	if (!(*shell)->tmp_path)
	{
		free(cwd);
		exit_(-1, *shell);
	}
	free(cwd);
	return (0);
}

t_data	*init_shell(char **envi)
{
	t_data	*shell;

	shell = malloc(sizeof(t_data));
	if (!shell)
		return (NULL);
	shell->env = copy_envi(envi);
	if (!shell->env)
		return (NULL);
	update_env(&shell);
	shell->cmd = NULL;
	shell->infile = -1;
	shell->outfile = -1;
	set_tmp(&shell);
	shell->status = 0;
	return (shell);
}
