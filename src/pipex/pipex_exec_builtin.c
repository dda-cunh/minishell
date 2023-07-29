#include "minishell.h"

void	run_builtin(t_cmd *cmd, int i)
{
	static int	(*f[8])(t_data **, char **) = (int (*[8])(t_data **, char **))
		{NULL, &echo, &cd, &pwd, &export_bin, &unset, &env, &exit_bin};
	int	pid;

	pid = 0;
	if (!cmd->next && i == 0)
		get_shell()->status = f[cmd->builtin](shell, &cmd->args[1]);
	else
	{
		pid = fork();
		if (pid == -1)
			exit_(-8, get_shell());
		else if (pid == 0)
			//	run in chd
		else
			//	wait for chd to terminate & exit function
	}
}
