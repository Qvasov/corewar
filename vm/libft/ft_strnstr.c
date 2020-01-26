/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:20:31 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/25 16:07:21 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	if (needle[0] == 0)
		return ((char*)haystack);
	while (haystack[i] && i < len)
	{
		k = i;
		j = 0;
		while (haystack[k] != needle[j] && haystack[k] && k < len)
			k++;
		while (haystack[k] == needle[j] && haystack[k] && k < len)
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
