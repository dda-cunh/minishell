/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 21:54:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/10 15:18:47 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env(t_data **shell, char **args)
{
	char	**env_;
	int		i;

	(void) args;
	i = -1;
	env_ = (*shell)->env;
	if (!env_)
		return (222);
	while (env_[++i])
		ft_putendl_fd(env_[i], 1);
	return (0);
}