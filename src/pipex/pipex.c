/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:25:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/15 18:42:04 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	parent(t_data *shell, int pipefd[2], int tmp, int child_pid)
{
	int	status;

	close_fds((int []){pipefd[1], tmp}, 2);
	waitpid(child_pid, &status, 0);
	if (WEXITSTATUS(status) != 2)
	{
		tmp = open(shell->tmp_path, O_WRONLY | O_TRUNC);
		if (tmp == -1)
			return (2);
		ft_read_write_fd(pipefd[0], tmp);
		close(tmp);
	}
	return (WEXITSTATUS(status));
}

static int	child(t_data *shell, t_cmd *cmd, char **env, int not_first)
{
	int		child_pid;
	int		pipefd[2];
	int		tmp;

	if (pipe(pipefd) == -1)
		return (2);
	tmp = open(shell->tmp_path, O_RDONLY);
	if (tmp == -1)
		return (2);
	child_pid = fork();
	if (child_pid == -1)
		return (2);
	if (child_pid == 0)
	{
		if (not_first && !cmd->redir)
			if (dup2(tmp, STDIN_FILENO) == -1)
				exit(2);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(2);
		close_fds((int []){pipefd[0], pipefd[1], tmp}, 3);
		execve(cmd->bin, cmd->args, env);
		exit(2);
	}
	return (parent(shell, pipefd, tmp, child_pid));
}

static int	builtin_pipes(t_data *shell, int pipefd[2], int stdi, int stdo)
{
	int	tmp;

	if (dup2(stdi, STDIN_FILENO) == -1
		|| dup2(stdo, STDOUT_FILENO) == -1)
		return (2);
	close_fds((int []){pipefd[1], stdo, stdi}, 3);
	tmp = open(shell->tmp_path, O_WRONLY | O_TRUNC);
	if (tmp == -1)
		return (2);
	ft_read_write_fd(pipefd[0], tmp);
	close(tmp);
	return (0);
}

static int	handle_exec(t_data **shell, t_cmd *cmd, char **env, int n_exec)
{
	int	pipefd[2];
	int	std_out_fd;
	int	std_in_fd;
	int	status;
	int	tmp;

	if (!cmd->builtin)
		return (child(*shell, cmd, env, n_exec));
	if (pipe(pipefd) == -1)
		return (2);
	tmp = open((*shell)->tmp_path, O_RDONLY);
	if (tmp == -1)
		return (2);
	std_out_fd = dup(STDOUT_FILENO);
	std_in_fd = dup(STDIN_FILENO);
	if (dup2(tmp, STDIN_FILENO) == -1
		|| dup2(pipefd[1], STDOUT_FILENO) == -1)
		return (2);
	status = exec_builtin(shell, *cmd);
	close(tmp);
	builtin_pipes(*shell, pipefd, std_in_fd, std_out_fd);
	return (status);
}

int	pipex(t_data **shell, t_cmd *cmd)
{
	int		status;
	int		n_exec;

	if (!shell)
		return (1);
	n_exec = 0;
	while (cmd)
	{
		if (init_tmp(*shell, cmd->redir) == 2)
			return (errno);
		status = handle_exec(shell, cmd, (*shell)->env, n_exec);
		if (status == 2)
			return (errno);
		if (print_out(*shell, cmd->redir) == 2)
			return (errno);
		n_exec++;
		cmd = cmd->next;
	}
	return (status);
}
