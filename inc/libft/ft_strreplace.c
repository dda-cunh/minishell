/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:57:09 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/15 17:47:25 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *str, int index, int torem, char *torepl)
{
	char	*result;
	int		len;
	int		tail;

	len = ft_strlen(str) + ft_strlen(torepl) - torem + 1;
	tail = ft_strlen(&str[index + torem - 1]);
	result = ft_calloc(len, sizeof(char));
	if (!result)
		return (NULL);
	if (index)
		ft_strlcpy(result, str, index + 1);
	if (*torepl)
		ft_strlcat(result, torepl, ft_strlen(result) + ft_strlen(torepl) + 1);
	ft_strlcat(result, &str[index + torem], ft_strlen(result) + tail + 1);
	return (result);
}
