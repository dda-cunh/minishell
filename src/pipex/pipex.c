/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:25:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/10 16:38:52 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	parent(int pipefd[2], int tmp, int child_pid)
{
	int	status;

	close_fds((int []){pipefd[1], tmp}, 2);
	waitpid(child_pid, &status, 0);
	if (WEXITSTATUS(status) != 2)
	{
		tmp = open("tmp", O_WRONLY | O_TRUNC);
		if (tmp == -1)
			return (2);
		ft_read_write_fd(pipefd[0], tmp);
		close(tmp);
	}
	return (WEXITSTATUS(status));
}

static int	child(t_data ***data, t_cmd *cmd, char **env)
{
	int		child_pid;
	int		pipefd[2];
	int		tmp;

	if (pipe(pipefd) == -1)
		return (2);
	tmp = open("tmp", O_RDONLY);
	if (tmp == -1)
		return (2);
	child_pid = fork();
	if (child_pid == -1)
		return (2);
	if (child_pid == 0)
	{
		if (dup2(tmp, STDIN_FILENO) == -1
			|| dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(2);
		close_fds((int []){pipefd[0], pipefd[1], tmp}, 3);
		if (cmd->builtin)
			exec_builtin(*data, *cmd);
		else
			if (execve(cmd->bin, cmd->args, env) == -1)
				exit(2);
	}
	return (parent(pipefd, tmp, child_pid));
}

int	pipex(t_data **data)
{
	t_cmd	*cmd;

	if (!data)
		return (1);
	cmd = (*data)->cmd;
	while (cmd)
	{
		if (init_tmp(cmd->infile_path, cmd->delim) == 2)
			return (errno);
		if (cmd->bin)
			if (child(&data, cmd, (*data)->env) == 2)
				return (errno);
		if (print_out(cmd) == 2)
			return (errno);
		cmd = cmd->next;
	}
	return (0);
}
