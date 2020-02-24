/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:44:52 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/06 20:21:49 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
		res[i] = (*f)(s[i]);
		i++;
	}
	return (res);
}
