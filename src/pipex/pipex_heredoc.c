#include "minishell.h"

static size_t	biggest(size_t delim_len, size_t a_len)
{
	if (a_len >= delim_len)
		return (a_len);
	else
		return (delim_len);
}

static void	read_input(t_data *shell, char *delim)
{
	char	*a;

	a = "";
	while (a)
	{
		a = readline(HD_PROMPT);
		if (a && *a == '\xff')
		{
			shell->sigint = true;
			break ;
		}
		if (a)
		{
			if (!ft_strncmp(a, delim, biggest(ft_strlen(delim), ft_strlen(a))))
			{
				free(a);
				break ;
			}
			ft_putendl_fd(a, shell->infile);
			free(a);
		}
		else
			ft_putendl_fd("warning: here-doc delimited by end-of-file", 2);
	}
}

void	here_doc(t_data *shell, char *delim)
{
	rl_event_hook = rl_sig_event;
	if (signal(SIGINT, heredoc_sig_handler) == SIG_ERR)
		exit_(-2, shell);
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