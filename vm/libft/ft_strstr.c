/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 23:04:49 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/25 15:15:43 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	if (needle[0] == 0)
		return ((char*)haystack);
	while (haystack[i])
	{
		k = i;
		j = 0;
		while (haystack[k] != needle[j] && haystack[k])
			k++;
		while (haystack[k] == needle[j] && haystack[k])
		{
			k++;
			j++;
			if (needle[j] == 0)
				return ((char*)haystack + k - j);
		}
		i++;
	}
	return (0);
}
