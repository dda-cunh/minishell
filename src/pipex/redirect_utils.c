#include "minishell.h"

static bool	file_check(t_redir *redir)
{
	if ((redir->direction == 'i' && !redir->dbl_tkn)
		&& access(redir->name, F_OK) == -1)
	{
		print_file_error(redir->name, FILE_NOT_FOUND);
		return (false);
	}
	if (redir->direction == 'i' && !redir->dbl_tkn
		&& access(redir->name, R_OK) == -1)
	{
		print_file_error(redir->name, FILE_NO_PERM);
		return (false);
	}
	if (redir->direction == 'o' 
		&& access(redir->name, F_OK) == 0 && access(redir->name, W_OK) == -1)
	{
		print_file_error(redir->name, FILE_NO_PERM);
		return (false);
	}
	return (true);
}

bool	open_infile(t_data *shell, t_redir *redir)
{
	bool	file_ok;

	file_ok = file_check(redir);
	if (!redir->dbl_tkn && file_ok)
	{
		shell->infile = open(redir->name, O_RDONLY);
		if (shell->infile == -1)
			exit_(-3, shell);
	}
	else if (redir->dbl_tkn)
		here_doc(shell, redir->name);
	if (file_ok || redir->dbl_tkn)
		return (true);
	else
		return (false);
}

bool	open_outfile(t_data *shell, t_redir *redir)
{
	int		flags;
	int		mode;
	bool	file_ok;

	if (!redir->dbl_tkn)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	file_ok = file_check(redir);
	if (file_ok)
	{
		shell->outfile = open(redir->name, flags, mode);
		if (shell->outfile == -1)
			exit_(-3, shell);
		return (true);
	}
	else
		return (false);
}
