/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:58:13 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/10 16:36:56 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_builtin	is_builtin(char *bin)
{
	if (bin && *bin)
	{
		if (!ft_strncmp(bin, "echo", 5))
			return (ECHO);
		else if (!ft_strncmp(bin, "cd", 3))
			return (CD);
		else if (!ft_strncmp(bin, "pwd", 4))
			return (PWD);
		else if (!ft_strncmp(bin, "export", 7))
			return (EXPORT);
		else if (!ft_strncmp(bin, "unset", 5))
			return (UNSET);
		else if (!ft_strncmp(bin, "env", 4))
			return (ENV);
		else if (!ft_strncmp(bin, "exit", 5))
			return (EXIT);
	}
	return (NOTBUILTIN);
}

int	exec_builtin(t_data **shell, t_cmd cmd)
{
	static int	(*f[8])(t_data **, char **) = (int (*[8])(t_data **, char **))
	{NULL, &echo, &cd, &pwd, &export_bin, &unset, &env, &exit_bin};

	if (!cmd.builtin)
		return (1);
	return (f[cmd.builtin](shell, cmd.args));
}
