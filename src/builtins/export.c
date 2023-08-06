/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:25:14 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/06 02:18:57 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**export_var(char *var_value, char **envi)
{
	char	**new_envi;
	int		i;

	new_envi = ft_calloc(len_2d(envi) + 2, sizeof(char *));
	if (!new_envi)
		return (NULL);
	i = -1;
	while (envi[++i])
	{
		new_envi[i] = ft_strdup(envi[i]);
		if (!new_envi[i])
		{
			free_2d(new_envi);
			return (NULL);
		}
	}
	free_2d(envi);
	new_envi[i] = ft_strdup(var_value);
	if (!new_envi[i])
	{
		free_2d(new_envi);
		return (NULL);
	}
	return (new_envi);
}

static void	print_invalid(char *arg)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

static bool	valid_chars(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '=' || ft_isdigit(arg[0]))
		return (false);
	while (arg[i] && arg[i] != '=')
	{
		if ((!ft_isalnum(arg[i]) && arg[i] != '=') && arg[i])
			return (false);
		i++;
	}
	return (true);
}

static int	do_export(t_data **sh, char *export_val)
{
	char	**split;

	split = ft_split(export_val, '=');
	if (!split)
		return (-1);
	if (get_env_index(*sh, split[0]) >= 0)
		update_env_val(sh, split[0], split[1], false);
	else
	{
		(*sh)->env = export_var(export_val, (*sh)->env);
		if (!(*sh)->env)
		{
			free_2d(split);
			exit_(-1, *sh);
		}
	}
	free_2d(split);
	return (0);
}

int	export_bin(t_data **sh, char **args)
{
	int	i;

	i = 0;
	if (!args[i])
	{
		print_sorted_env(*sh);
		return (0);
	}
	while (args[i])
	{
		if (!valid_chars(args[i]))
		{
			print_invalid(args[i]);
			return (1);
		}
		else if (ft_strchr(args[i] + 1, '='))
			do_export(sh, args[i]);
		i++;
	}
	return (0);
}
