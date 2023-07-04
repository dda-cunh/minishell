/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:36:39 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/04 16:45:01 by dda-cunh         ###   ########.fr       */
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

int	echo(char **arg)
{
	bool	flag;
	int		i;

	flag = n_flag(arg);
	if (flag == true)
		i = 0;
	else
		i = -1;
	while (arg[++i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}
