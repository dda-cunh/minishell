/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:17:46 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/17 12:10:04 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	exit_bin(t_data **shell, char **args)
{
	bool	is_num;
	int		status;

	status = 0;
	if (args[0])
	{
		ft_putendl_fd("exit", 2);
		if (args[1])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1);
		}
		is_num = ft_sislong(args[0]);
		if (!is_num)
		{
			status = 2;
			print_error(args[0]);
		}
		else if (!args[1])
			status = ft_atoi(args[0]) & 0xff;
	}
	return (exit_(status, *shell));
}
