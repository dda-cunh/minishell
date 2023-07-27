/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_print_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmouronh <fmouronh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:53:47 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/27 19:53:55 by fmouronh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_strerror(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return ;
}

void	print_fatal_error(int status)
{
	ft_putstr_fd("Minishell: fatal error: ", 2);
	if (status == -1)
		ft_putendl_fd("error on malloc", 2);
	else if (status == -2)
		ft_putendl_fd("signal handler error", 2);
	else if (status == -3)
		ft_putendl_fd("file open error", 2);
	else if (status == -4)
		ft_putendl_fd("file close error", 2);
	else if (status == -5)
		ft_putendl_fd("pipe open error", 2);
	else if (status == -6)
		ft_putendl_fd("pipe close error", 2);
	else if (status == -7)
		ft_putendl_fd("exec error", 2);
	else if (status == -8)
		ft_putendl_fd("fork error", 2);
	else if (status == -9)
		ft_putendl_fd("up error", 2);
}