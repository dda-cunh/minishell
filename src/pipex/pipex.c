/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:25:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/17 19:52:43 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/*
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

static int	child(t_data *shell, t_cmd *cmd, char **env, bool not_first)
{
	int	child_pid;
	int	pipefd[2];
	int	tmp;

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
		if (not_first || (cmd->redir && cmd->redir->direction == 'i'))
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

static int	handle_exec(t_data **shell, t_cmd *cmd, char **env, bool n_exec)
{
	int	std_out_fd;
	int	std_in_fd;
	int	pipefd[2];
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
*/

static void	reset_io(t_data *shell)
{
	if (dup2(shell->stdin_reset, STDIN_FILENO) == -1
		|| dup2(shell->stdout_reset, STDOUT_FILENO) == -1)
		exit_(-9, shell);
	shell->file_err = false;
	shell->sigint = false;
}

static void	close_files(t_data *shell)
{
	if (shell->infile != -1)
	{
		if (close(shell->infile) == -1)
			exit_(-4, shell);
		shell->infile = -1;
	}
	if (shell->outfile != -1)
	{
		if (close(shell->outfile) == -1)
			exit_(-4, shell);
		shell->outfile = -1;
	}
}

static void	handle_exec(t_cmd *cmd, int i)
{
	if (signal(SIGINT, exec_sig_handler) == SIG_ERR
		|| signal(SIGQUIT, exec_sig_handler) == SIG_ERR)
		exit_(-2, get_shell());
	if (cmd->builtin)
		run_builtin(cmd, i);
	else
		run_cmd(cmd);
}

static void	dup_io(t_cmd *cmd, int **pipe_fd, int i)
{
	get_shell()->file_err = false;
	if (pipe_fd)
		dup_pipes(cmd, pipe_fd, i);
	if (cmd->redir)
		dup_redirects(get_shell(), cmd->redir);
}

int	pipex(t_data *shell, t_cmd *cmd)
{
	int		**pipe_fd;
	int		i;

	pipe_fd = set_pipes(shell, cmd);
	i = 0;
	while (cmd)
	{
		dup_io(cmd, pipe_fd, i);
		if (shell->sigint)
		{
			close_files(shell);
			break ;
		}
		if (!shell->file_err && cmd->args && cmd->args[0])
			handle_exec(cmd, i);
		close_files(shell);
		cmd = cmd->next;
		i++;
	}
	reset_io(shell);
	if (pipe_fd)
		free_pipeline(shell, pipe_fd);
	return (shell->status);
}
