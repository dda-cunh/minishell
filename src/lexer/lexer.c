/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:14:15 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/06 15:25:57 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_tkn_err(char tkn)
{
	ft_putstr_fd("minishell: syntax error near unexpected token: \'", 2);
	ft_putchar_fd(tkn, 2);
	ft_putendl_fd("\'", 2);
}

/*
	handle the following errors:
		- invalid chars (ex '\', ';', '#'...)
		- unclosed quotes
		- line starting/ending with pipe - DONE
		- redirects with no file
*/

static bool	valid_lex(char *line)
{
	if (!line[0])
		return (false);
	else if (line[0] == '|' || line[ft_strlen(line) - 1] == '|')
	{
		print_tkn_err('|');
		return (false);
	}
	else if (!valid_quotes(line) || !valid_tkns(line) || !valid_redirect(line))
		return (false);
	return (true);
}

/*
	example command:
	 0  3            16
	"   ls -l | wc -w      "
		^			 ^
		start		 end
	size = end - start + 1
*/

char	**lex_line(t_data *shell, char *in_line)
{
	char	**tokens;
	char	*line;

	line = ft_strtrim(in_line, " ");
	if (!line)
		exit_(-1, shell);
	if (!valid_lex(line))
	{
		free(line);
		return (NULL);
	}
	tokens = ft_split(line, '|');
	free(line);
	if (!tokens)
		return (NULL);
	return (tokens);
}
