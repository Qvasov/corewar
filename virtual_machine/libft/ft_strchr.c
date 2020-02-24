/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 21:02:50 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/23 21:16:07 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	symb;
	int		i;

	symb = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == symb)
			return ((char*)s + i);
		i++;
	}
	if (s[i] == symb)
		return ((char*)s + i);
	return (0);
}
