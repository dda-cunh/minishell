/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:25:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/06 02:39:53 by dda-cunh         ###   ########.fr       */
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
	if (cmd->bin && cmd->builtin == NOTBUILTIN && !ft_strchr(cmd->bin, '/'))
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
	if ((*cmd)->builtin == NOTBUILTIN)
		status = execve((*cmd)->bin, (*cmd)->args, env);
	else
		status = exec_builtin(&shell, **cmd);
	do_close(*cmd);
	exit_(status, shell);
}

static int	handle_builtin_exec(t_data **shell, t_cmd **cmd)
{
	int	std_out_fd;
	int	std_in_fd;
	int	status;

	status = 0;
	std_out_fd = dup(STDOUT_FILENO);
	std_in_fd = dup(STDIN_FILENO);
	status = dupper(*cmd);
	if (status)
		return (2);
	status = exec_builtin(shell, **cmd);
	if (dup2(std_in_fd, STDIN_FILENO) == -1
		|| dup2(std_out_fd, STDOUT_FILENO) == -1)
		return (2);
	return (status);
}

static int	do_cmd(t_data **shell, t_cmd *cmd, int i_cmd)
{
	pid_t	curr;

	(*shell)->sigint = false;
	if ((*shell)->sigint)
		return ((*shell)->status);
	if (signal(SIGINT, exec_sig_handler) == SIG_ERR
		|| signal(SIGQUIT, exec_sig_handler) == SIG_ERR)
		exit_(-2, *shell);
	if (!cmd->builtin || (cmd->next || (!cmd->next && i_cmd
				&& (cmd->builtin == CD || cmd->builtin == EXPORT
					|| cmd->builtin == UNSET || cmd->builtin == EXIT))))
	{
		curr = fork();
		if (curr == -1)
			return (2);
		if (!curr)
			child(*shell, &cmd, (*shell)->env);
		else
			return (parent(cmd, curr));
	}
	else
		return (handle_builtin_exec(shell, &cmd));
	return (0);
}

int	pipex(t_data **shell, t_cmd *cmd)
{
	int	status;
	int	i_cmd;

	i_cmd = 0;
	while (cmd)
	{
		if (!pipeline(*shell, cmd))
		{
			status = do_cmd(shell, cmd, i_cmd);
			do_close(cmd);
		}
		else
			put_strerror(NULL, true);
		cmd = cmd->next;
		++i_cmd;
	}
	return (status);
}
