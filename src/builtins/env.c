/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 21:54:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/04 16:49:56 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env(t_data *shell, char **args)
{
	char	**env_;
	int		i;

	if (args)
	{
		ft_putendl_fd("minishell: env recieves no argument nor flag", 2);
		return (1);
	}
	i = -1;
	env_ = shell->env;
	if (!env_)
		return (222);
	while (env_[++i])
		printf("%s\n", env_[i]);
	return (0);
}
