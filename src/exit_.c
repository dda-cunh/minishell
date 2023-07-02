/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:04:01 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/02 15:58:17 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_all(t_data *shell)
{
	int	i;

	i = -1;
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
			ft_putendl_fd(strerror(errno), 2);
	}
	return (status);
}
