/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:49:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/02 18:23:55 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	update_env_val(t_data *shell, const char *var, const char *new_val)
{
	size_t	len;
	char	**envi;
	char	*temp;
	int		i;

	len = ft_strlen(var);
	i = -1;
	envi = shell->env;
	if (!envi)
		return (-1);
	while (envi[++i])
	{
		if (ft_strncmp(envi[i], var, len) == 0)
		{
			free(envi[i]);
			temp = ft_strjoin(var, "=");
			if (!temp)
				return (-1);
			envi[i] = ft_strjoin(temp, new_val);
			free (temp);
			return (0);
		}
	}
	return (0);
}

char	*get_env_val(t_data *shell, const char *var)
{
	size_t	len;
	char	**envi;
	int		i;

	len = ft_strlen(var);
	i = -1;
	envi = shell->env;
	if (envi)
		while (envi[++i])
			if (ft_strncmp(envi[i], var, len) == 0)
				return (ft_strdup((envi[i] + len + 1)));
	return (NULL);
}
