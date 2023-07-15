/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:58:13 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/15 17:44:00 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_builtin	is_builtin(char *bin)
{
	int	bin_len;

	if (bin && *bin)
	{
		bin_len = ft_strlen(bin);
		if (bin_len == 4 && !ft_strncmp(bin, "echo", 5))
			return (ECHO);
		else if (bin_len == 2 && !ft_strncmp(bin, "cd", 3))
			return (CD);
		else if (bin_len == 3 && !ft_strncmp(bin, "pwd", 4))
			return (PWD);
		else if (bin_len == 6 && !ft_strncmp(bin, "export", 7))
			return (EXPORT);
		else if (bin_len == 4 && !ft_strncmp(bin, "unset", 5))
			return (UNSET);
		else if (bin_len == 3 && !ft_strncmp(bin, "env", 4))
			return (ENV);
		else if (bin_len == 4 && !ft_strncmp(bin, "exit", 5))
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
	return (f[cmd.builtin](shell, cmd.args + 1));
}
