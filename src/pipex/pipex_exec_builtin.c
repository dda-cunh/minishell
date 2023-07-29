#include "minishell.h"

void	run_builtin(t_cmd *cmd, int i)
{
	if (!cmd->next && i == 0)
		//	run in parent
	else
	{
		//	fork & run
	}
}
