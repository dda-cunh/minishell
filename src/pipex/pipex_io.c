/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:52:22 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/17 17:00:24 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_out(t_data *shell, t_redir *redir)
{
	int		tmp;
	int		outfd;

	tmp = open(shell->tmp_path, O_RDONLY);
	outfd = 1;
	if (redir && redir->direction == 'o')
	{
		if (redir->dbl_tkn)
			outfd = open(redir->name,
					O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			outfd = open(redir->name,
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (outfd == -1)
		{
			close(tmp);
			return (2);
		}
	}
	ft_read_write_fd(tmp, outfd);
	if (outfd != 1)
		close(outfd);
	return (0);
}

static size_t	get_biggest(char *delim, size_t alen)
{
	if (alen >= ft_strlen(delim))
		return (alen);
	else
		return (ft_strlen(delim));
}

static void	here_doc(t_data *shell, char *delim, int tmp)
{
	char	*a;
	size_t	biggest;
	size_t	alen;

	a = "";
	while (a)
	{
		rl_event_hook = rl_sig_event;
		if (signal(SIGINT, heredoc_sig_handler) == SIG_ERR)
			exit_(-3, shell);
		a = readline("minishell>>> ");
		if (!a || *a == '\xff')
			break ;
		alen = ft_strlen(a) - 1;
		biggest = get_biggest(delim, alen);
		if (!ft_strncmp(a, delim, biggest))
		{
			free(a);
			break ;
		}
		ft_putendl_fd(a, tmp);
		free(a);
	}
}

int	init_tmp(t_data *shell, t_redir *redir)
{
	int		infd;
	int		tmp;

	tmp = open(shell->tmp_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (tmp == -1)
		return (2);
	infd = 0;
	if (redir && redir->direction == 'i' && redir->dbl_tkn)
		here_doc(shell, redir->name, tmp);
	else if (redir && redir->direction == 'i' && !redir->dbl_tkn)
	{
		infd = open(redir->name, O_RDONLY, 0777);
		if (infd == -1)
		{
			close(tmp);
			return (2);
		}
		ft_read_write_fd(infd, tmp);
	}
	close(tmp);
	return (0);
}
