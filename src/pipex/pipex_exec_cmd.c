#include "minishell.h"

static void	exec_cmd(t_cmd *cmd)
{

}

void	run_cmd(t_cmd *cmd)
{
	if (strchr(cmd->args[0], '/'))
	{
		cmd->bin = ft_strdup(cmd->args[0]);
		if (!cmd->bin)
			exit_(-1, get_shell());
	}
	else
		cmd->bin = get_cmd_bin(get_shell()->env, cmd->args[0]);
	if (cmd->bin)
		exec_cmd(cmd);
}
/*
	if strchr(cmd->args[0], '/')
		alloc cmd->args[0] to cmd->bin
	else
		check for cmd->args[0] in $PATH, alloc to cmd->bin
		(return NULL if not found)
	if cmd->bin
		fork/exec
*/