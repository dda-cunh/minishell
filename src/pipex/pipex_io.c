/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:52:22 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/12 20:01:19 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	here_doc(t_data *shell, char *delim, int tmp)
{
	size_t	d_len;
	char	*line;

	d_len = ft_strlen(delim);
	line = "";
	while (line)
	{
		rl_event_hook = rl_sig_event;
		if (signal(SIGINT, heredoc_sig_handler) == SIG_ERR)
			exit_(-2, shell);
		line = readline(HD_PROMPT);
		if (!line)
			ft_putendl_fd("warning: here-document delimited by end-of-file", 2);
		if (!line || shell->sigint)
			break ;
		if (ft_strncmp(delim, line, d_len) == 0
			&& (ft_strlen(line) == d_len))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, tmp);
		free(line);
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
			put_strerror(redir->name, true);
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
	while (redir && !get_shell()->sigint)
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
			tmp = get_tmp(shell, &redir);
		if (tmp == -1)
			return (2);
		infd = tmp;
	}
	else
		infd = open(redir->name, O_RDONLY, 0777);
	if (infd == -1)
		put_strerror(redir->name, true);
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
		while (redir && !shell->sigint)
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
