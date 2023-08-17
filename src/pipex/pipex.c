/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:25:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/17 14:34:17 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_builtin_exec(t_data **shell, t_cmd **cmd)
{
	int	std_out_fd;
	int	std_in_fd;
	int	status;

	status = 0;
	std_out_fd = dup(STDOUT_FILENO);
	std_in_fd = dup(STDIN_FILENO);
	dupper(*cmd);
	if ((*cmd)->builtin == EXIT)
	{
		if (dup2(std_in_fd, STDIN_FILENO) == -1
			|| dup2(std_out_fd, STDOUT_FILENO) == -1)
			return (2);
		close_fds((int []){std_in_fd, std_out_fd}, 2);
		std_in_fd = -1;
		std_out_fd = -1;
		do_close(*cmd);
	}
	status = exec_builtin(shell, **cmd);
	if (((*cmd)->builtin != EXIT && dup2(std_in_fd, STDIN_FILENO) == -1)
		|| ((*cmd)->builtin != EXIT && dup2(std_out_fd, STDOUT_FILENO) == -1))
		return (2);
	if ((*cmd)->builtin != EXIT)
		close_fds((int []){std_in_fd, std_out_fd}, 2);
	return (status);
}

static void	check_cmd(t_cmd *cmd)
{
	char	*error;

	error = NULL;
	if ((!cmd->builtin && (!ft_strchr(cmd->bin, '/')
				|| access(cmd->bin, F_OK))))
	{
		error = ft_strjoin(cmd->bin, BADCMD_ERR);
		put_strerror(error, 0);
	}
	else if (cmd->builtin == NOTBUILTIN && !access(cmd->bin, F_OK))
	{
		if (is_dir(cmd->bin))
		{
			error = ft_strjoin(cmd->bin, ": Is a directory");
			put_strerror(error, 0);
		}
		else if (access(cmd->bin, X_OK))
		{
			error = ft_strjoin(cmd->bin, ": Permission denied");
			put_strerror(error, 0);
		}
	}
	free(error);
}

static void	child(t_data *shell, t_cmd **cmd, char **env)
{
	t_cmd	*ref;
	int		status;

	if (!(*cmd)->bin)
		exit_(0, shell);
	if (dupper((*cmd)))
		exit_(2, shell);
	ref = *cmd;
	while ((*cmd)->next)
		*cmd = (*cmd)->next;
	do_close(*cmd);
	*cmd = ref;
	if (ref->builtin == NOTBUILTIN)
		status = execve(ref->bin, ref->args, env);
	else
	{
		if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
			exit_(-2, shell);
		status = exec_builtin(&shell, *ref);
	}
	do_close(*cmd);
	exit_(status, shell);
}

static int	do_cmd(t_data **shell, t_cmd *cmd)
{
	if (signal(SIGINT, exec_sig_handler) == SIG_ERR
		|| signal(SIGQUIT, exec_sig_handler) == SIG_ERR)
		exit_(-2, *shell);
	if (!cmd->bin)
		return (0);
	if (cmd->infd == 2 || cmd->outfd == 2)
		return (1);
	if (cmd->builtin && (!cmd->next && !cmd->prev))
		return (handle_builtin_exec(shell, &cmd));
	cmd->id = fork();
	if (cmd->id == -1)
		return (2);
	if (!cmd->id)
		child(*shell, &cmd, (*shell)->env);
	else
		check_cmd(cmd);
	return (0);
}

int	pipex(t_data **shell, t_cmd *cmd)
{
	int	status;

	status = 0;
	(*shell)->sigint = false;
	if (pipeline(*shell, cmd))
		return (1);
	if ((*shell)->sigint)
		return ((*shell)->status);
	while (cmd)
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR
			|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			exit_(-2, *shell);
		status = do_cmd(shell, cmd);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	if (cmd->id > 0)
		status = do_wait(cmd);
	else
		do_wait(cmd);
	return (status);
}
