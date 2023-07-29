/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 07:27:57 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/20 16:09:49 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	open_pipes(t_data *shell, int **pipes, int nr_cmds)
{
	int	i;

	i = 0;
	while (i < nr_cmds)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i])
			return (false);
		if (pipe(pipes[i]) == -1)
		{
			free_pipeline(shell, pipes);
			exit_(-5, shell);
		}
		i++;
	}
	return (true);
}

static int	count_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	**set_pipeline(t_data *shell, t_cmd *cmd)
{
	int	**pipeline;
	int	nr_cmds;

	nr_cmds = count_cmds(cmd);
	pipeline = ft_calloc(nr_cmds + 1, sizeof(int *));
	if (!pipeline)
		return (NULL);
	if (!open_pipes(shell, pipeline, nr_cmds))
	{
		free_pipeline(shell, pipeline);
		return (NULL);
	}
	return (pipeline);
}
