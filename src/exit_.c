/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:04:01 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/04 17:15:25 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_strerror(void)
{
	ft_putendl_fd(strerror(errno), 2);
	return ;
}

static void	free_all(t_data *shell)
{
	if (shell->env)
	{
		free_2d(shell->env);
	}
	free(shell);
}

int	exit_(int status, t_data *shell)
{
	if (shell)
		free_all(shell);
	if (status)
	{
		ft_putstr_fd("Minishell:", 2);
		if (status == -1)
			ft_putendl_fd("Error on Malloc", 2);
		else if (status == 2)
			put_strerror();
	}
	exit(status);
}
