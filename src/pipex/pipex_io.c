/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:52:22 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/22 21:36:39 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	here_doc(t_data *shell, char *delim, int tmp)
{
	size_t	biggest;
	size_t	alen;
	char	*a;

	a = "";
	rl_event_hook = rl_sig_event;
	while (a)
	{
		if (signal(SIGINT, heredoc_sig_handler) == SIG_ERR)
			exit_(-3, shell);
		a = readline(HD_PROMPT);
		if (!a || *a == '\xff')
			break ;
		biggest = ft_strlen(delim);
		alen = ft_strlen(a);
		if (alen > biggest)
			biggest = alen;
		if (!ft_strncmp(a, delim, biggest))
		{
			free(a);
			break ;
		}
		ft_putstr_fd(a, tmp);
		ft_putchar_fd('\n', tmp);
		free(a);
	}
}

static int	get_input(t_data *shell, t_redir **redir, bool fake)
{
	int		infd;
	int		tmp;

	if (fake)
		tmp = open("/dev/null", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		tmp = open(shell->tmp_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (tmp == -1)
		return (2);
	infd = 0;
	if ((*redir)->dbl_tkn)
		here_doc(shell, (*redir)->name, tmp);
	else
	{
		infd = open((*redir)->name, O_RDONLY, 0777);
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

static int	tail_redirect(t_data *shell, t_redir *redir, t_cmd *next, int tmp)
{
	int	outfd;

	outfd = 1;
	if (redir->direction == 'i')
		return (get_input(shell, &redir, true));
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
	if ((!next && !redir->next) || !redir_has_out(redir->next))
		ft_read_write_fd(tmp, outfd);
	else
		close(tmp);
	if (outfd != 1)
		close(outfd);
	return (0);
}

int	print_out(t_data *shell, t_redir *redir, t_cmd *next)
{
	int	status;
	int	tmp;

	while (redir)
	{
		tmp = open(shell->tmp_path, O_RDONLY);
		if (!tmp)
			return (2);
		status = tail_redirect(shell, redir, next, tmp);
		if (status)
			return (status);
		redir = redir->next;
	}
	return (0);
}

int	init_tmp(t_data *shell, t_cmd **cmd, t_redir **redir, bool not_first)
{
	t_redir	*ref;
	bool	read_tmp;
	int		status;

	read_tmp = false;
	if (!not_first || (not_first && (*redir)))
	{
		while (redir && *redir && (*redir)->direction == 'i')
		{
			status = get_input(shell, redir, false);
			ref = *redir;
			*redir = (*redir)->next;
			free(ref);
			if (status)
				return (status);
			read_tmp = true;
		}
	}
	(*cmd)->read_tmp = read_tmp;
	return (0);
}
