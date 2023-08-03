/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:52:22 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/03 19:26:34 by dda-cunh         ###   ########.fr       */
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

static int	get_output(t_redir *redir, t_cmd *cmd)
{
	int	outfd;

	if (redir)
	{
		if (redir->dbl_tkn)
			outfd = open(redir->name, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			outfd = open(redir->name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (outfd == -1)
			return (2);
		if (cmd->bin && ((!redir->next && !cmd->next)
				|| !redir_has_direction(redir->next, 'o')))
			return (outfd);
		close(outfd);
	}
	return (1);
}

int	get_cmd_out(t_redir *redir, t_cmd *cmd)
{
	bool	is_last;
	int		outfd;

	if (!redir && cmd->next)
		return (-69);
	outfd = 1;
	if (redir && !redir->next && redir->direction == 'o')
		return (get_output(redir, cmd));
	while (redir)
	{
		if (redir->direction == 'o')
		{
			is_last = !redir_has_direction(redir->next, 'o');
			outfd = get_output(redir, cmd);
			if (outfd == 2)
				return (2);
			if (is_last)
				break ;
		}
		redir = redir->next;
	}
	return (outfd);
}

static int	get_input(t_data *shell, t_redir *redir, bool fake)
{
	int		infd;
	int		tmp;

	infd = 0;
	if (redir->dbl_tkn)
	{
		if (fake)
			tmp = open("/dev/null", O_WRONLY, 0777);
		else
			tmp = open(shell->tmp_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (tmp == -1)
			return (2);
		here_doc(shell, redir->name, tmp);
		close(tmp);
		if (!fake)
			infd = open(shell->tmp_path, O_RDONLY, 0777);
	}
	else
		infd = open(redir->name, O_RDONLY, 0777);
	if (infd == -1)
		return (2);
	if (fake && infd)
		close(infd);
	return (infd);
}

int	get_cmd_in(t_data *shell, t_redir *redir)
{
	bool	is_last;
	int		infd;

	infd = 0;
	if (redir && redir_has_direction(redir, 'i'))
	{
		if (redir && !redir->next && redir->direction == 'i')
			return (get_input(shell, redir, false));
		while (redir)
		{
			if (redir->direction == 'i')
			{
				is_last = !redir_has_direction(redir->next, 'i');
				infd = get_input(shell, redir, !is_last);
				if (infd == 2)
					return (2);
				if (is_last)
					break ;
			}
			redir = redir->next;
		}
	}
	return (infd);
}
