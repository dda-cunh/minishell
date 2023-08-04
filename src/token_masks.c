/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_masks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 06:05:12 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/03 17:44:07 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_mask(char *str, char quote, char tkn)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
	{
		if (str[i] == tkn)
			str[i] = '\xff';
		i++;
	}
	return (i + 1);
}

void	unset_mask(char *str, char tkn)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\xff')
			str[i] = tkn;
		i++;
	}
}

void	trim_quotes(t_data *shell, char **args)
{
	char	*tmp;
	char	quote;
	int		i;

	quote = '\0';
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '\'' || args[i][0] == '\"')
		{
			quote = args[i][0];
			tmp = ft_strtrim(args[i], &quote);
			if (!tmp)
				exit_(-1, shell);
			free(args[i]);
			args[i] = tmp;
		}
		i++;
	}
}
