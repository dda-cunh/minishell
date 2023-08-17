/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_patch2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmouronh <fmouronh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:10:47 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/17 12:10:57 by fmouronh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*do_remove(char *removed, char *str, int start, int *i)
{
	char	*result;

	result = ft_calloc(ft_strlen(removed) + ft_strlen(&str[start]) - 1, 1);
	if (!result)
		exit_(-1, get_shell());
	ft_strlcpy(result, removed, ft_strlen(removed) + 1);
	//	cat from str[start] to str[i[1]]
	ft_strlcat(result, &str[start], ft_strlen(result) + i[1] - start + 1);
	//	cat from str[i[1]] to str[i[0]]
	ft_strlcat(result, &str[i[1] + 1], ft_strlen(result) + i[0] - i[1]);
	free(removed);
	return (result);
}