/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:25:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/01 19:50:14 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	parent(int pipefd[2], int tmp, int child_pid)
{
	int	status;

	close_fds((int []){pipefd[1], tmp}, 2);
	waitpid(child_pid, &status, 0);
	if (status != 2)
	{
		tmp = open("tmp", O_RDWR | O_TRUNC);
		if (tmp == -1)
			return (2);
		read_write(pipefd[0], tmp);
		close(tmp);
	}
	return (WEXITSTATUS(status));
}

static int	child(char **cmd, char **env)
{
	int		child_pid;
	int		tmp;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (2);
	tmp = open("tmp", O_RDONLY);
	child_pid = fork();
	if (child_pid == -1)
		return (2);
	if (child_pid == 0)
	{
		if (dup2(tmp, STDIN_FILENO) == -1
			|| dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (2);
		close_fds((int []){pipefd[0], pipefd[1], tmp}, 3);
		execve(cmd[0], &cmd[1], env);
		exit(2);
	}
	return (parent(pipefd, tmp, child_pid));
}

int	pipex(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	if (!data)
		return (1);
	i = 0;
	cmd = data->cmd;
	while (cmd)
	{
		if (!cmd)
			return (3);
		if (child(cmd->args, data->env) == 2)
			return (2);
		cmd = cmd->next;
	}
	return (print_out(data));
}
