/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:17:11 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/20 18:15:57 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	update_env(t_data **shell)
{
	int		shlvl;
	char	*s_shlvl;

	//Need to see if we should add protection for int range
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
	//And what else needs to be updated when a shell is started
	return ;
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
	return (minish_envi);
}

static int	set_tmp(t_data **shell)
{
	char	*sh_addr;

	sh_addr = ft_itoa(**(int **)shell); 
	if (!sh_addr)
		exit_(-1, *shell);
	(*shell)->tmp_path = ft_strjoin("/tmp/", sh_addr);
	free(sh_addr);
	if (!(*shell)->tmp_path)
		exit_(-1, *shell);
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
