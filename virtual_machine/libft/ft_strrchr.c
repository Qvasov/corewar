/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 21:39:15 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/23 23:02:15 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	symb;
	size_t	i;

	symb = (char)c;
	i = ft_strlen(s);
	if (s[i] == symb)
		return ((char*)s + i);
	while (i > 0)
	{
		i--;
		if (s[i] == symb)
			return ((char*)s + i);
	}
	return (0);
}
