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

static void	unmask_quoted_pipes(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		unset_mask(tokens[i], '|');
		i++;
	}
}

static void	mask_quoted_pipes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '\'' && line[i] != '\"')
			i++;
		else
			i += set_mask(&line[i], line[i], '|');
	}
}

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
	mask_quoted_pipes(line);
	tokens = ft_split(line, '|');
	free(line);
	if (!tokens)
		return (NULL);
	unmask_quoted_pipes(tokens);
	return (tokens);
}
