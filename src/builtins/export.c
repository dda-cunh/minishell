/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:25:14 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/04 16:33:37 by dda-cunh         ###   ########.fr       */
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
			free_2d(envi);
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

int	export_bin(t_data **sh, char *var_value)
{
	char	*value;
	char	*var;
	int		i;

	if (!ft_strchr(var_value, '='))
		return (0);
	i = -1;
	while (var_value[++i])
		if (var_value[i] == '=')
			break ;
	var = ft_substr(var_value, 0, i);
	value = get_env_val((*sh), var);
	if (value)
	{
		free(value);
		update_env_val((*sh), var, &var_value[i + 1], false);
	}
	else
		if ((*sh)->env)
			(*sh)->env = export_var(var_value, (*sh)->env);
	free(var);
	return (0);
}
