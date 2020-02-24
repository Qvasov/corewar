/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:01:47 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/29 19:06:34 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	wide;
	char	*conc;
	size_t	i;
	size_t	j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	wide = i + j + 1;
	if (wide < i || wide < j
		|| (conc = (char*)malloc(sizeof(char) * wide)) == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		conc[i] = s1[i];
	while (s2[j])
		conc[i++] = s2[j++];
	conc[i] = '\0';
	return (conc);
}
