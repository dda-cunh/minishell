/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:25:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/11 17:32:17 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	parent(t_cmd *cmd)
{
	char	*error;
	int		status;

	status = 0;
	if (cmd->bin && cmd->builtin == NOTBUILTIN && !ft_strchr(cmd->bin, '/'))
	{
		error = ft_strjoin(cmd->bin, BADCMD_ERR);
		put_strerror(error, 0);
		free(error);
		status = 127;
	}
	return (status);
}

static void	child(t_data *shell, t_cmd **cmd, char **env)
{
	t_cmd	*ref;
	int		status;

	if (!(*cmd)->bin)
		exit_(0, shell);
	if (dupper((*cmd)))
		exit_(2, shell);
	ref = *cmd;
	while ((*cmd)->next)
		*cmd = (*cmd)->next;
	do_close(*cmd);
	*cmd = ref;
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

static int	do_cmd(t_data **shell, t_cmd *cmd)
{
	(*shell)->sigint = false;
	if ((*shell)->sigint)
		return ((*shell)->status);
	if (signal(SIGINT, exec_sig_handler) == SIG_ERR
		|| signal(SIGQUIT, exec_sig_handler) == SIG_ERR)
		exit_(-2, *shell);
	if (!cmd->builtin || (cmd->next || (!cmd->next && cmd->prev
				&& (cmd->builtin == CD || cmd->builtin == EXPORT
					|| cmd->builtin == UNSET || cmd->builtin == EXIT))))
	{
		cmd->id = fork();
		if (cmd->id == -1)
			return (2);
		if (!cmd->id)
			child(*shell, &cmd, (*shell)->env);
		else
			return (parent(cmd));
	}
	else
	{
		cmd->id = -69;
		return (handle_builtin_exec(shell, &cmd));
	}
	return (0);
}

int	pipex(t_data **shell, t_cmd *cmd)
{
	int	status;

	status = 0;
	if (pipeline(*shell, cmd))
		exit_(-5, *shell);
	while (cmd)
	{
		cmd->infd = get_cmd_in(*shell, cmd->redir);
		if (cmd->infd == 2)
			return (2);
		cmd->outfd = get_cmd_out(cmd->redir, cmd);
		if (cmd->outfd == 2)
			return (2);
		status = do_cmd(shell, cmd);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	if (cmd->id > 0)
		status = do_wait(cmd);
	else
		do_wait(cmd);
	return (status);
}
