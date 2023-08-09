/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:34:40 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/06 06:11:24 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	do_close(t_cmd *cmd)
{
	if (!cmd->next)
		close(cmd->pipe[0]);
	close(cmd->pipe[1]);
	if (cmd->infd > 2 && redir_has_direction(cmd->redir, 'i'))
		close(cmd->infd);
	if (cmd->outfd > 2 && redir_has_direction(cmd->redir, 'o'))
		close(cmd->outfd);
	return ;
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