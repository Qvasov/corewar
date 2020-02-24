/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:57:04 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/06 20:21:45 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*res;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	if ((res = ft_strnew(ft_strlen(s))) == NULL)
		return (NULL);
	while (s[i])
	{
		res[i] = (*f)((unsigned int)i, s[i]);
		i++;
	}
	return (res);
}
