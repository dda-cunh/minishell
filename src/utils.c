/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:49:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/04 16:18:40 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_strerror(void)
{
	ft_putendl_fd(strerror(errno), 2);
	return ;
}

static int	create_on_update(t_data *shell, const char *var,
	const char *new_val)
{
	char	*tempa;
	char	*tempb;

	tempa = ft_strjoin(var, "=");
	if (!tempa)
		return (-1);
	tempb = ft_strjoin(tempa, new_val);
	if (!tempb)
	{
		free(tempa);
		return (-1);
	}
	export_bin(&shell, tempb);
	return (0);
}

int	update_env_val(t_data *shell, const char *var, const char *new_val,
	bool should_create)
{
	size_t	len;
	char	*temp;
	int		i;

	len = ft_strlen(var);
	i = -1;
	if (!shell->env)
		return (-1);
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], var, len) == 0)
		{
			free(shell->env[i]);
			temp = ft_strjoin(var, "=");
			if (!temp)
				return (-1);
			shell->env[i] = ft_strjoin(temp, new_val);
			free (temp);
			return (0);
		}
	}
	if (should_create)
		create_on_update(shell, var, new_val);
	return (0);
}

char	*get_env_val(t_data *shell, const char *var)
{
	size_t	len;
	int		i;

	len = ft_strlen(var);
	i = -1;
	shell->env = shell->env;
	if (shell->env)
		while (shell->env[++i])
			if (ft_strncmp(shell->env[i], var, len) == 0)
				return (ft_strdup((shell->env[i] + len + 1)));
	return (NULL);
}
