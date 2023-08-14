/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:04:01 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/14 15:47:23 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_strerror(char *arg, bool print_strerror)
{
	ft_putstr_fd(ANSI_RED, 2);
	ft_putstr_fd(arg, 2);
	if (print_strerror)
		ft_putstr_fd(strerror(errno), 2);
	ft_putendl_fd(ANSI_RESET, 2);
	return ;
}

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

static void	free_all(t_data **shell)
{
	if (shell && *shell)
	{
		if ((*shell)->env)
			free_2d((*shell)->env);
		if ((*shell)->cmd)
			free_cmd((*shell)->cmd);
	}
}

int	exit_(int status, t_data *shell)
{
	close_fds((int []){0, 1, 2}, 3);
	free_all(&shell);
	clear_history();
	exit(status);
}
