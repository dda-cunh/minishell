/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_patch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmouronh <fmouronh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:52:57 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/17 15:53:05 by fmouronh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ignore_expansion(char tkn)
{
	if (!tkn || tkn == ' ' || tkn == '\'' || tkn == '\"')
		return (true);
	else
		return (false);
}