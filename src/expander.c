/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:15:44 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/10 15:15:58 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_status(t_data *shell, char *tokens, int index)
{
	char	*status_str;
	char	*expanded;

	status_str = ft_itoa((int)shell->status);
	if (!status_str)
		exit_(-1, shell);
	expanded = ft_strreplace(tokens, index - 1, 2, status_str);
	free(status_str);
	if (!expanded)
		exit_(-1, shell);
	return (expanded);
}

static char	*expand_var(t_data *shell, char *tokens, int index)
{
	char	*var_name;
	char	*var_val;
	char	*expanded;
	int		i;

	i = index;
	if (tokens[i] == '?')
		return (get_status(shell, tokens, index));
	while (tokens[i] && ft_isalnum(tokens[i]))
		i++;
	var_name = ft_calloc(i - index + 1, sizeof(char));
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, &tokens[index], i - index + 1);
	var_val = get_env_val(shell, var_name);
	expanded = ft_strreplace(tokens, index - 1, i - index + 1, var_val);
	free(var_name);
	free(var_val);
	free(tokens);
	if (!expanded)
		exit_(-1, shell);
	return (expanded);
}

static int	search_var_tkn(char *tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == '\'')
		{
			i++;
			while (tokens[i] != '\'')
				i++;
		}
		if (tokens[i] == '$')
			return (i + 1);
		i++;
	}
	return (-1);
}

void	expander(t_data *shell, char **tokens)
{
	int	var_i;
	int	i;

	var_i = 0;
	i = 0;
	while (tokens[i])
	{
		var_i = search_var_tkn(tokens[i]);
		if (var_i >= 0)
			tokens[i] = expand_var(shell, tokens[i], var_i);
		else
			i++;
	}
}
