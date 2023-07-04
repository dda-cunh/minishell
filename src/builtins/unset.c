/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 00:43:34 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/04 17:24:23 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**unset_var(t_data *shell, int index)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = ft_calloc(len_2d(shell->env), sizeof(char *));
	if (!new_env)
		exit_(-1, shell);
	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (i == index)
			i++;
		new_env[j] = ft_strdup(shell->env[i]);
		if (!new_env[j])
		{
			free_2d(new_env);
			exit_(-1, shell);
		}
		j++;
		i++;
	}
	return (new_env);
}

static void	print_invalid(char *arg)
{
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	unset(t_data *shell, char **args)
{
	int		index;
	int		status;
	int		i;

	status = 0;
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			print_invalid(args[i]);
			status = 1;
		}
		else
		{
			index = get_env_index(shell, args[i]);
			if (index >= 0)
				shell->env = unset_var(shell, index);
		}
		i++;
	}
	return (status);
}
