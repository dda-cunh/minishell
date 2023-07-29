/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:17:11 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/24 19:09:20 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data	*get_shell(void)
{
	static t_data	shell;

	return (&shell);
}

static void	update_env(t_data **shell)
{
	update_shlvl(shell);
	if (get_env_index(*shell, "PWD") < 0)
		reset_pwd(shell); // this is not working...
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

	shell = get_shell();
	shell->env = copy_envi(envi);
	if (!shell->env)
		return (NULL);
	update_env(&shell);
	shell->sigint = false;
	shell->cmd = NULL;
	shell->stdin_reset = dup(STDIN_FILENO);
	shell->stdout_reset = dup(STDOUT_FILENO);
	if (shell->stdin_reset == -1 || shell->stdout_reset == -1)
		exit_(-9, shell);
	shell->infile = -1;
	shell->outfile = -1;
	shell->file_err = false;
	set_tmp(&shell);
	shell->status = 0;
	return (shell);
}
