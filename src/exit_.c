/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:04:01 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/10 15:08:45 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_strerror(void)
{
	ft_putendl_fd(strerror(errno), 2);
	return ;
}

static void	free_redir(t_redir *redir)
{
	if (redir->next)
		free_redir(redir->next);
	if (redir->name)
		free(redir->name);
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
	if (shell->env)
		free_2d(shell->env);
	if (shell->cmd)
		free_cmd(shell->cmd);
	free(shell);
}

int	exit_(int status, t_data *shell)
{
	if (shell)
		free_all(shell);
	if (status)
	{
		ft_putstr_fd("Minishell:", 2);
		if (status == -1)
			ft_putendl_fd("Error on Malloc", 2);
		else if (status == 2)
			put_strerror();
	}
	clear_history();
	exit(status);
}
