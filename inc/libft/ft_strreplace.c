/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:57:09 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/08 20:22:18 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *str, int index, int torem, char *torepl)
{
	char	*result;
	int		len;
	int		tail;

	len = ft_strlen(str) + ft_strlen(torepl) - torem + 1;
	printf("result length = %d\n", len);
	tail = ft_strlen(str) - index - torem;
	result = ft_calloc(len, sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, index + 1);
	ft_strlcat(result, torepl, ft_strlen(torepl) + 1);
	ft_strlcat(result, &str[index + torem], tail + 1);
	printf("result = %s\n", result);
	return (result);
}
