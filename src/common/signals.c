/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 03:57:28 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/06 00:28:51 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	get_shell()->status = 130;
}

void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_done = 1;
		rl_redisplay();
		rl_on_new_line();
	}
	get_shell()->status = 130;
	get_shell()->sigint = true;
}

void	exec_sig_handler(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	get_shell()->sigint = true;
	if (sig == SIGINT)
		get_shell()->status = 130;
	else if (sig == SIGQUIT)
		get_shell()->status = 131;
}

int	rl_sig_event(void)
{
	return (130);
}
