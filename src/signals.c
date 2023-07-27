/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmouronh <fmouronh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 03:57:28 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/19 03:57:36 by fmouronh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 2);
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
		ft_putendl_fd("", 2);
		rl_replace_line("\xff", 0);
		rl_done = 1;
		rl_redisplay();
		rl_on_new_line();
	}
	get_shell()->status = 130;
	get_shell()->sigint = true;
}

int	rl_sig_event(void)
{
	return (130);
}
