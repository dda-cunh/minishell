#include "minishell.h"

bool	open_infile(t_data *shell, t_redir *redir)
{
	bool	file_ok;

	file_ok = file_check(redir);
	if (!redir->dbl_tkn && file_ok)
	{
		shell->infile = open(redir->name, O_RDONLY)
		if (shell->infile == -1)
			exit_(-3, shell);
	}
	else if (redir->dbl_tkn)
		here_doc(shell, redir);
	if (file_ok || redir->dbl_tkn)
		return (true);
	else
		return (false);
}

bool	open_outfile(t_data *shell, t_data *redir)
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

static void	open_redir_file(t_data *shell, t_redir *redir, bool *fd_open)
{
	if (redir->direction == 'i')
	{
		if (fd_open[0])
		{
			if (close(shell->infile) == -1)
				exit_(-4, shell);
		}
		if (open_infile(shell, redir))
			fd_open[0] = true;
	}
	if (redir->direction == 'o')
	{
		if (fd_open[1])
		{
			if (close(shell->outfile) == -1)
				exit_(-4, shell);
		}
		if (open_outfile(shell, redir))
			fd_open[1] = true;
	}
}

/*
	direction == 'i' && !dbl_tkn
		open file in O_RDONLY
	direction == 'i' && dbl_tkn
		open file O_WRONLY, read from STDIN, close it and open it again in O_RDONLY
	direction == 'o'
		open file, set mode according to dbl_tkn
*/
void	dup_redirects(t_data *shell, t_redir *redir);
{
	bool	fd_open[2];

	fd_open[0] = false;
	fd_open[1] = false;
	while (redir)
	{
		open_redir_file(shell, redir, fd_open);
		redir = redir->next;
	}
	if (fd_open[0])
	{
		if (dup2(shell->infile, STDIN_FILENO) == -1)
			exit_(-9, shell);
	}
	if (fd_open[1])
		if (dup2(shell->outfile, STDOUT_FILENO) == -1)
			exit_(-9, shell);
}

/*
fd_open[0] = infile open
fd_open[1] = outfile open
*/