/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:36:39 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/03 17:49:12 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo(char **arg)
{
	bool	flag;
	int		i;

	flag = false;
	i = -1;
	if (!arg)
		return (1);
	if (arg[0][0] == '-' && arg[0][1] == 'n')
	{
		i++;
		if (arg[0][2])
			printf("%s", arg[0]);
		else
			flag = true;
	}
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
