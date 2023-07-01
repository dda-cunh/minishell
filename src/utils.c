/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:49:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/01 22:03:45 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_env_val(t_data *data, const char *var, const char *new_val)
{
	size_t	len;
	char	**envi;
	char	*temp;
	int		i;

	len = ft_strlen(var);
	envi = data->env;
	i = -1;
	while (envi[++i])
	{
		if (ft_strncmp(envi[i], var, len) == 0)
		{
			// free(envi[i]);
			temp = ft_strjoin(var, "=");
			envi[i] = ft_strjoin(temp, new_val);
			free (temp);
			return ;
		}
	}
	return ;
}

char	*get_env_val(t_data *data, const char *var)
{
	char	**envi;
	size_t	len;
	int		i;

	len = ft_strlen(var);
	envi = data->env;
	i = -1;
	while (envi[++i])
	{
		if (ft_strncmp(envi[i], var, len) == 0)
			return (ft_strdup((envi[i] + len + 1)));
	}
	return (NULL);
}

int	exit_(int status, t_data *data)
{
	if (data)
		//clean all
		free(data);
	return (status);
}
