/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:04:01 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/03 18:04:26 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
