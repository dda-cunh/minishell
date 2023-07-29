#include "minishell.h"

void	here_doc(t_data *shell, char *delim)
{
	//	open temp in WRONYLY
	shell->infile = open(shell->tmp_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (shell->infile == -1)
		exit_(-3, shell);
	//	read from input until strncmp(input, delim) == 0
	
	//	close temp
	if (close(shell->infile) == -1)
		exit_(-4, shell);
	//	open temp in RDONLY
		shell->infile = open(shell->tmp_path, O_RDONLY);
		if (shell->infile == -1)
			exit_(-3, shell);
}