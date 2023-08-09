/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:34:40 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/09 18:06:53 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	do_close(t_cmd *cmd)
{
	t_cmd	*ref;

	ref = cmd;
	if (!cmd->next)
	{
		while (cmd)
		{
			close(cmd->pipe[0]);
			cmd = cmd->prev;
		}
	}
	cmd = ref;
	close(cmd->pipe[1]);
	if (cmd->infd > 2 && redir_has_direction(cmd->redir, 'i'))
		close(cmd->infd);
	if (cmd->outfd > 2 && redir_has_direction(cmd->redir, 'o'))
		close(cmd->outfd);
	return ;
}

int	do_wait(t_cmd *tail)
{
	int	status;
	int	exit;

	status = 0;
	while (tail)
	{
		waitpid(tail->id, &exit, 0);
		if (!tail->next)
			status = WEXITSTATUS(exit);
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
	if (pipe(cmd->pipe) == -1)
		exit_(-5, shell);
	cmd->infd = get_cmd_in(shell, cmd->redir);
	if (cmd->infd == 2)
	{
		close (cmd->pipe[1]);
		return (2);
	}
	cmd->outfd = get_cmd_out(cmd->redir, cmd);
	if (cmd->outfd == 2)
	{
		close (cmd->pipe[1]);
		return (2);
	}
	cmd = cmd->next;
	return (0);
}
