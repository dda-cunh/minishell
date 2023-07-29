#include "minishell.h"

//	copy from staging branch
static void	read_input(t_data *shell, char *delim)
{

}

void	here_doc(t_data *shell, char *delim)
{
	shell->infile = open(shell->tmp_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (shell->infile == -1)
		exit_(-3, shell);
	read_input(shell, delim);
	if (close(shell->infile) == -1)
		exit_(-4, shell);
		shell->infile = open(shell->tmp_path, O_RDONLY);
		if (shell->infile == -1)
			exit_(-3, shell);
}