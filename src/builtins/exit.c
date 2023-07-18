/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:17:46 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/10 16:49:19 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_error(char *arg)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

static bool	str_is_num(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (false);
		arg++;
	}
	return (true);
}

int	exit_bin(t_data **shell, char **args)
{
	int		status;

	status = 0;
	if (args[1])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (args[0])
	{
		if (str_is_num(args[0]))
			status = ft_atoi(args[0]) & 0xff;
		else
		{
			print_error(args[0]);
			return (2);
		}
	}
	ft_putendl_fd("exit", 1);
	return (exit_(status, *shell));
}
