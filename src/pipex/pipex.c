/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:25:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/03 19:30:18 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	parent(t_cmd *cmd, int child_pid)
{
	char	*error;
	int		status;

	if (cmd->next)
		waitpid(child_pid, &status, WNOHANG);
	else
		waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	if (status == 255)
	{
		error = ft_strjoin(cmd->bin, BADCMD_ERR);
		put_strerror(error, 0);
		free(error);
		return (127);
	}
	return (status);
}

static void	child(t_data *shell, t_cmd **cmd, char **env)
{
	int	status;

	status = 2;
	if (!(*cmd)->bin)
		exit_(0, shell);
	status = dupper((*cmd));
	if (status)
		exit_(2, shell);
	status = execve((*cmd)->bin, (*cmd)->args, env);
	do_close(*cmd);
	exit_(status, shell);
}

static int	handle_builtin_exec(t_data **shell, t_cmd **cmd, int i_cmd)
{
	int	std_out_fd;
	int	std_in_fd;
	int	status;

	status = 2;
	std_out_fd = dup(STDOUT_FILENO);
	std_in_fd = dup(STDIN_FILENO);
	status = dupper(*cmd);
	if (status)
		return (2);
	status = exec_builtin(shell, **cmd, i_cmd);
	if (dup2(std_in_fd, STDIN_FILENO) == -1
		|| dup2(std_out_fd, STDOUT_FILENO) == -1)
		return (2);
	return (status);
}

int	pipex(t_data **shell, t_cmd *cmd)
{
	pid_t	curr;
	int		status;
	int		i_cmd;

	i_cmd = 0;
	while (cmd)
	{
		if (!pipeline(*shell, cmd))
		{
			if (!cmd->builtin)
			{
				curr = fork();
				if (curr == -1)
					return (2);
				if (!curr)
					child(*shell, &cmd, (*shell)->env);
				else
					status = parent(cmd, curr);
			}
			else
				status = handle_builtin_exec(shell, &cmd, i_cmd);
		}
		else
			put_strerror(NULL, true);
		do_close(cmd);
		cmd = cmd->next;
		++i_cmd;
	}
	return (status);
}
