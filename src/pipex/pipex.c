/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:25:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/22 23:05:46 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	parent(t_data *shell, int pipes[2][2], int child_pid)
{
	int	status;
	int	tmp;

	close_fds((int []){pipes[0][0], pipes[0][1], pipes[1][1]}, 3);
	waitpid(child_pid, &status, 0);
	if (!WEXITSTATUS(status))
	{
		tmp = open(shell->tmp_path, O_WRONLY | O_TRUNC);
		if (tmp == -1)
		{
			close_fds((int []){pipes[1][0]}, 1);
			return (2);
		}
		ft_read_write_fd(pipes[1][0], tmp, 1, 1);
	}
	return (WEXITSTATUS(status));
}

static int	child(t_data *shell, t_cmd *cmd, char **env, bool not_first)
{
	int	child_pid;
	int	pip[2][2];
	int	tmp;

	if (pipe(pip[0]) == -1 || pipe(pip[1]) == -1)
		return (2);
	tmp = open(shell->tmp_path, O_RDONLY);
	if (tmp == -1)
		return (2);
	ft_read_write_fd(tmp, pip[0][1], 1, 0);
	child_pid = fork();
	if (child_pid == -1)
		return (2);
	if (child_pid == 0)
	{
		if (not_first || cmd->read_tmp)
			if (dup2(pip[0][0], STDIN_FILENO) == -1)
				exit(2);
		if ((cmd->next || cmd->redir) && dup2(pip[1][1], STDOUT_FILENO) == -1)
			exit(2);
		close_fds((int []){pip[0][0], pip[0][1], pip[1][0], pip[1][1]}, 4);
		exit(execve(cmd->bin, cmd->args, env));
	}
	return (parent(shell, pip, child_pid));
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
	ft_read_write_fd(pipefd[0], tmp, 1, 1);
	return (0);
}

static int	handle_exec(t_data **shell, t_cmd *cmd, char **env, bool not_first)
{
	int	std_out_fd;
	int	std_in_fd;
	int	pipefd[2];
	int	status;
	int	tmp;

	if (!cmd->builtin)
		return (child(*shell, cmd, env, not_first));
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
	status = exec_builtin(shell, *cmd, not_first);
	close(tmp);
	builtin_pipes(*shell, pipefd, std_in_fd, std_out_fd);
	return (status);
}

int	pipex(t_data **shell, t_cmd *cmd)
{
	bool	not_first;
	int		status;
	int		tmp;

	if (!shell)
		return (1);
	tmp = open((*shell)->tmp_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (tmp == -1)
		return (2);
	close(tmp);
	not_first = false;
	//	set sig handlers for SIGINT & SIGQUIT in cmd here
	while (cmd)
	{
		if (init_tmp(*shell, &cmd, &(cmd->redir), not_first) == 2)
			return (errno);
		status = handle_exec(shell, cmd, (*shell)->env, not_first);
		if (status)
			return (errno);
		if (print_out(*shell, cmd->redir, cmd->next) == 2)
			return (errno);
		not_first = true;
		cmd = cmd->next;
	}
	return (status);
}
