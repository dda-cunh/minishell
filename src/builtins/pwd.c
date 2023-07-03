/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:25:39 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/03 16:49:50 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pwd(void)
{
	char	*pwd_val;

	pwd_val = getcwd(NULL, 0);
	if (!pwd_val)
		return (-1);
	ft_putendl_fd(pwd_val, 1);
	free(pwd_val);
	return (0);
}
