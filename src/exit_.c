/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:04:01 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/25 00:33:05 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_redir(t_redir *redir)
{
	if (redir->name)
		free(redir->name);
	if (redir->next)
		free_redir(redir->next);
	free(redir);
}

t_cmd	*free_cmd(t_cmd *cmd)
{
	if (cmd->next)
		free_cmd(cmd->next);
	if (cmd->bin)
		free(cmd->bin);
	if (cmd->args)
		free_2d(cmd->args);
	if (cmd->redir)
		free_redir(cmd->redir);
	free(cmd);
	return (NULL);
}

static void	free_all(t_data *shell)
{
	if (shell)
	{
		if (shell->env)
			free_2d(shell->env);
		if (shell->cmd)
			free_cmd(shell->cmd);
		if (shell->tmp_path)
			free(shell->tmp_path);
	}
}

int	exit_(int status, t_data *shell)
{
	free_all(shell);
	if (status < 0)
	{
		print_fatal_error(status);
		status *= -1;
	}
	else if (errno && !shell->sigint)
		put_strerror();
	clear_history();
	exit(status);
}
