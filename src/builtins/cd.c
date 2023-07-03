/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:54:33 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/03 18:14:54 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd(t_data *shell, const char **path)
{
	char	*old_pwd;

	if ((path + 1))
	{
		ft_putendl_fd("minishel: too many arguments", 2);
		return (0);
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (-1);
	if (chdir(*path) == -1)
		put_strerror();
	else
	{
		update_env_val(shell, "OLDPWD", old_pwd);
		update_env_val(shell, "PWD", *path);
	}
	free(old_pwd);
	return (0);
}
