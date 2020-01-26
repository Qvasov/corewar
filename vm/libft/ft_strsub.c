/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:01:36 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/02 19:44:35 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	i;

	i = 0;
	if (s == NULL || len + 1 == 0 || (size_t)start + len > ft_strlen(s) + 1)
		return (NULL);
	if ((s2 = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (i < len)
	{
		s2[i] = s[start + (unsigned int)i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}
