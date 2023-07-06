/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:15:44 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/06 15:49:44 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	look for unquoted '$'
	read chars after '$'
		if found in env, replace with string
		else replace with ''

	0   45  8
	cat $VAR | wc -l
*/

/*
	getting a bit spaghetti-ish
	might need to do over

	NOPE!
	expand while parsing
		ie after allocating each thing to cmd->args
		but before parsing anything else
*/
static char	**expand_var(t_data *shell, char **tokens, int index)
{
	char	**env;
	char	*var_name;
	char	*var_val;
	int		i;

	env = shell->env;
	i = index;
	while (tokens[i] && *tokens[i] != ' ')
		i++;
	var_name = ft_calloc(i - index + 1, sizeof(char));
	if (!var_name)
		return (NULL);
	var_val = get_env_val(shell, var_name);

}

static int	search_vars(char *tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

void	expander(t_data *shell, char **tokens)
{
	int	var_index;
	int	i;

	var_index = 0;
	i = 0;
	while (tokens[i])
	{
		var_index = search_vars(tokens[i]);
		if (var_index)
		{
			tokens[i] = expand_var(shell, tokens[i], var_index);
			if (!tokens)
				free_2d(tokens);
				exit_(-1, shell);
		}
		else
			i++;
	}
}