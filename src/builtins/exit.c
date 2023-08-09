/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:17:46 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/09 17:38:33 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdbool.h>

static void	print_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

static bool	str_is_num(char *arg)
{
	if (*arg == '-')
		arg++;
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
	bool	is_num;

	status = 0;
	is_num = str_is_num(args[0]);
	if (args[0])
	{
		ft_putendl_fd("exit", 1);
		if (!is_num)
		{
			status = 2;
			print_error(args[0]);
		}
		else if (!args[1])
			status = ft_atoi(args[0]) & 0xff;
		else
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1);
		}
	}
	return (exit_(status, *shell));
}
