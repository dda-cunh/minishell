/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_validator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:35:47 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/06 15:41:41 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_next_quote(char *line, char quote)
{
	int	i;

	i = 1;
	while (line [i] && line[i] != quote)
		i++;
	return (i);
}

bool	valid_tkn(char tkn)
{
	int	i;

	i = 0;
	while (VALID_TKNS[i])
	{
		if (tkn == VALID_TKNS[i])
			return (true);
		i++;
	}
	return (false);
}

int	redir_found(char *line, char tkn)
{
	int	i;

	i = 0;
	if (line[i] == tkn)
		i++;
	while (line[i])
	{
		if (ft_isalnum(line[i]) || line[i] == '$'
			|| line[i] == '/' || line[i] == '.')
			return (i);
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			print_tkn_err(tkn);
			return (ft_strlen(line));
		}
		i++;
	}
	if (!line[i])
		print_tkn_err(tkn);
	return (i);
}
