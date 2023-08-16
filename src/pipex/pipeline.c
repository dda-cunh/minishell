/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:34:40 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/16 22:06:15 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_status(t_cmd *tail, int exit)
{
	if (get_shell()->sigint && (exit == 2 || exit == 131))
		return (get_shell()->status);
	else if (!tail->builtin && !ft_strchr(tail->bin, '/'))
		return (127);
	else if (tail->builtin == NOTBUILTIN && !access(tail->bin, F_OK)
		&& access(tail->bin, X_OK))
		return (126);
	else
		return (WEXITSTATUS(exit));
}

void	do_close(t_cmd *tail)
{
	if (!tail)
		return ;
	if (tail->pipe[0] > 2)
		close(tail->pipe[0]);
	if (tail->pipe[1] > 2)
		close(tail->pipe[1]);
	if (tail->infd > 2 && redir_has_direction(tail->redir, 'i'))
		close(tail->infd);
	if (tail->outfd > 2 && redir_has_direction(tail->redir, 'o'))
		close(tail->outfd);
	if (tail->prev)
		do_close(tail->prev);
	return ;
}

int	do_wait(t_cmd *tail)
{
	int	status;
	int	exit;

	do_close(tail);
	status = 0;
	while (tail)
	{
		if (tail->id > 0)
		{
			waitpid(tail->id, &exit, 0);
			if (!tail->next)
				status = get_status(tail, exit);
		}
		tail = tail->prev;
	}
	return (status);
}

int	dupper(t_cmd *cmd)
{
	if (cmd->infd > 2 && redir_has_direction(cmd->redir, 'i'))
	{
		if (dup2(cmd->infd, STDIN_FILENO) == -1)
			return (2);
	}
	else
		if (cmd->prev && dup2(cmd->prev->pipe[0], STDIN_FILENO) == -1)
			return (2);
	if (cmd->outfd > 2 && redir_has_direction(cmd->redir, 'o'))
	{
		if (dup2(cmd->outfd, STDOUT_FILENO) == -1)
			return (2);
	}
	else
		if (cmd->next && dup2(cmd->pipe[1], STDOUT_FILENO) == -1)
			return (2);
	return (0);
}

int	pipeline(t_data *shell, t_cmd *cmd)
{
	t_cmd	*ref;

	ref = cmd;
	while (cmd && !shell->sigint)
	{
		cmd->infd = get_cmd_in(shell, cmd->redir);
		if (cmd->infd == 2)
			return (1);
		if (shell->sigint)
			close(cmd->infd);
		cmd = cmd->next;
	}
	cmd = ref;
	while (cmd && !shell->sigint)
	{
		if (pipe(cmd->pipe) == -1)
			exit_(-5, shell);
		cmd->outfd = get_cmd_out(cmd->redir, cmd);
		if (cmd->outfd == 2)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
