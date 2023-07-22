/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_noargs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmouronh <fmouronh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:45:00 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/18 21:45:09 by fmouronh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env(t_data *shell, char **sorted, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (++i < size)
		sorted[i] = shell->env[i];
	i = 0;
	tmp = NULL;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strncmp(sorted[i], sorted[j], ft_strlen(sorted[i] + 1)) > 0)
			{
				tmp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_sorted_env(t_data *shell)
{
	char	**sorted_env;
	int		size;
	int		i;

	size = len_2d(shell->env);
	sorted_env = ft_calloc(size + 1, sizeof(char *));
	if (!sorted_env)
		exit_(-1, shell);
	i = 0;
	sort_env(shell, sorted_env, size);
	while (sorted_env[i])
	{
		if (ft_strncmp(sorted_env[i], "_=", 2))
			printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	free(sorted_env);
}