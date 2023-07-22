/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:49:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/22 23:07:40 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	redir_has_direction(t_redir *redir, char direction)
{
	if (!redir)
		return (false);
	while (redir)
	{
		if (redir->direction == direction)
			return (true);
		redir = redir->next;
	}
	return (false);
}

int	get_env_index(t_data *shell, const char *env_var)
{
	char	**envi;
	char	*var;
	size_t	len;
	int		i;

	envi = shell->env;
	var = ft_strjoin(env_var, "=");
	if (!var)
		return (-1);
	len = ft_strlen(var);
	i = 0;
	while (envi[i])
	{
		if (!strncmp(var, envi[i], len))
		{
			free(var);
			return (i);
		}
		i++;
	}
	free(var);
	return (-1);
}

static int	create_on_update(t_data *shell, const char *var,
	const char *new_val)
{
	char	*tempa;
	char	*tempb;
	char	**args;

	tempa = ft_strjoin(var, "=");
	if (!tempa)
		return (-1);
	tempb = ft_strjoin(tempa, new_val);
	free(tempa);
	if (!tempb)
		return (-1);
	args = ft_calloc(2, sizeof(char *));
	if (!args)
	{
		free(tempb);
		return (-1);
	}
	args[0] = tempb;
	free(tempb);
	export_bin(&shell, args);
	free(args);
	return (0);
}

int	update_env_val(t_data **shell, const char *var, const char *new_val,
	bool should_create)
{
	size_t	len;
	char	*temp;
	int		i;

	len = ft_strlen(var);
	i = -1;
	if (!(*shell)->env)
		return (-1);
	while ((*shell)->env[++i])
	{
		if (ft_strncmp((*shell)->env[i], var, len) == 0)
		{
			free((*shell)->env[i]);
			temp = ft_strjoin(var, "=");
			if (!temp)
				return (-1);
			(*shell)->env[i] = ft_strjoin(temp, new_val);
			free (temp);
			return (0);
		}
	}
	if (should_create)
		create_on_update((*shell), var, new_val);
	return (0);
}

char	*get_env_val(t_data *shell, const char *var)
{
	size_t	len;
	char	*val;
	int		i;

	len = ft_strlen(var);
	i = -1;
	if (shell->env)
	{
		while (shell->env[++i])
		{
			if (ft_strncmp(shell->env[i], var, len) == 0
				&& shell->env[i][len] && shell->env[i][len] == '=')
			{
				val = ft_strdup((shell->env[i] + len + 1));
				if (!val)
					exit_(-1, shell);
				return (val);
			}
		}
	}
	val = ft_strdup("");
	if (!val)
		exit_(-1, shell);
	return (val);
}
