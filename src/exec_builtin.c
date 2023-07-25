/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:58:13 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/25 00:21:59 by dda-cunh         ###   ########.fr       */
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
		else if (bin_len == 5 && !ft_strncmp(bin, "unset", 6))
			return (UNSET);
		else if (bin_len == 3 && !ft_strncmp(bin, "env", 4))
			return (ENV);
		else if (bin_len == 4 && !ft_strncmp(bin, "exit", 5))
			return (EXIT);
	}
	return (NOTBUILTIN);
}

int	exec_builtin(t_data **shell, t_cmd cmd, bool not_first)
{
	static int	(*f[8])(t_data **, char **) = (int (*[8])(t_data **, char **))
	{NULL, &echo, &cd, &pwd, &export_bin, &unset, &env, &exit_bin};
	int			child_pid;
	int			status;

	if (!cmd.builtin)
		return (1);
	if (cmd.next || (!cmd.next && not_first))
	{
		child_pid = fork();
		if (child_pid == -1)
			exit_(-1, *shell);
		if (child_pid == 0)
			exit_(f[cmd.builtin](shell, cmd.args + 1), *shell);
		waitpid(child_pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (f[cmd.builtin](shell, cmd.args + 1));
}
