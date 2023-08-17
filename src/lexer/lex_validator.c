/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:39:30 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/17 15:17:22 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	output tokens: check to the right until you find a valid char (return true)
					or until '\0', '<', '|' (return false)
						note: ">>>" is not valid

	input tokens: check to the right until you find a valid char
					return false if '\0', '|', '>'
					""
*/

bool	valid_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			i += find_next_quote(&line[i], '\"');
		if (!line[i])
		{
			print_tkn_err('\"');
			return (false);
		}
		if (line[i] == '\'')
			i += find_next_quote(&line[i], '\'');
		if (!line[i])
		{
			print_tkn_err('\'');
			return (false);
		}
		i++;
	}
	return (true);
}

/*
 0  3       11
"ls > myfile"
*/

static int	skip_quotes(char *tkns, char quote)
{
	int	i;

	i = 1;
	while (tkns[i] && tkns[i] != quote)
		i++;
	return (i);
}

bool	valid_redirect(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i += skip_quotes(&line[i], line[i]);
		if (line[i] == '<' || line[i] == '>')
		{
			i++;
			i += redir_found(&line[i], line[i - 1]);
			if (!line[i])
				return (false);
		}
		else
			if (line[i])
				i++;
	}
	return (true);
}

/*
		if (line[i] == '<')
		{
			tkn = '<';
			i++;
			i += redir_found(&line[i], '<');
			if (!line[i])
			{
				print_tkn_err(tkn);
				return (false);
			}
		}
		else if (line[i] == '>')
		{
			tkn = '>';
			i++;
			i += redir_found(&line[i], '>');
			if (!line[i])
			{
				print_tkn_err(tkn);
				return (false);
			}
		}
*/