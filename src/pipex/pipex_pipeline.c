#include "minishell.h"

void	free_pipeline(t_data *shell, int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		if (close(pipes[i][0]) == -1 || close(pipes[i][1]) == -1)
			exit_(-6, shell);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

//	maybe this needs to be done in the chd process?
void	dup_pipes(t_cmd *cmd, int **pipe_fd, int i)
{
	if (i != 0)
	{
		if (dup2(pipe_fd[i - 1][0], STDIN_FILENO) == -1)
			exit_(-9, get_shell());
	}
	if (cmd->next)
	{
		if (dup2(pipe_fd[i][1], STDOUT_FILENO) == -1)
			exit_(-9, get_shell());
	}
	else if (!cmd->next && i != 0)
	{
		if (dup2(get_shell()->stdout_reset, STDOUT_FILENO) == -1)
			exit_(-9, get_shell());
	}
}

int	**set_pipes(t_data *shell, t_cmd *cmd)
{
	int	**pipe_fd;

	if (cmd->next)
	{
		pipe_fd = set_pipeline(shell, cmd);
		if (!pipe_fd)
			exit_(-1, shell);
	}
	else
		pipe_fd = NULL;
	return (pipe_fd);
}
