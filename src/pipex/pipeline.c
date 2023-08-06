/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:34:40 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/06 04:48:19 by dda-cunh         ###   ########.fr       */
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
	if (cmd->infd > 2)
	{
		if (dup2(cmd->infd, STDIN_FILENO) == -1)
			return (2);
	}
	else
		if (cmd->prev && dup2(cmd->prev->pipe[0], STDIN_FILENO) == -1)
			return (2);
	if (cmd->outfd > 2)
	{
		if (dup2(cmd->outfd, STDOUT_FILENO) == -1)
			return (2);
	}
	else
		if (cmd->next && dup2(cmd->pipe[1], STDOUT_FILENO) == -1)
			return (2);
	return (0);
}

int	pipeline(t_data *shell, t_cmd **cmd)
{
	t_cmd	*curr;

	curr = *cmd;
	while (curr)
	{
		if (pipe(curr->pipe) == -1)
			exit_(-5, shell);
		curr->infd = get_cmd_in(shell, curr->redir);
		if (curr->infd == 2)
			return (2);
		curr->outfd = get_cmd_out(curr->redir, curr);
		if (curr->outfd == 2)
			return (2);
		curr = curr->next;
	}
	return (0);
}
