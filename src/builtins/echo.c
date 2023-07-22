/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:36:39 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/10 20:41:23 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	n_flag(char **arg)
{
	int	i;


	if (arg && arg[0] && arg[0][0] == '-')
	{
		i = 1;
		while (arg[0][i] == 'n')
			i++;
		if (arg[0][i] == '\0')
			return (true);
	}
	return (false);
}

int	echo(t_data **shell, char **arg)
{
	bool	flag;
	int		i;

	(void)shell;
	flag = n_flag(arg);
	if (flag == true)
		i = 0;
	else
		i = -1;
	while (arg[++i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putendl_fd("", 1);
	return (0);
}