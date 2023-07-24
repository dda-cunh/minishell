/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 05:05:45 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/24 19:43:37 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_shlvl(t_data **shell)
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

void	reset_pwd(t_data **shell)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		exit_(-1, *shell);
	update_env_val(shell, "PWD", dir, true);
	free(dir);
}
