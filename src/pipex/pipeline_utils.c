/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmouronh <fmouronh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 07:27:57 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/19 07:28:06 by fmouronh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipeline(t_data *shell, int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		if (close(pipes[i][0]) == -1 || close(pipes[i][1]) == -1)
			exit_(-5, shell);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

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
			free_pipeline(shell, pipes[i]);
			exit_(-4, shell);
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
	pipeline = ft_calloc(nr_cmds + 1, sizeof(int*))
	if (!pipeline)
		exit_(-1, shell);
	if (!open_pipes(shell, pipeline, nr_cmds))
	{
		free_pipeline(shell, pipeline);
		exit_(-1, shell);
	}
	return (pipeline);
}
