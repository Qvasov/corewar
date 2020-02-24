/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:16:44 by laleta            #+#    #+#             */
/*   Updated: 2019/04/08 03:33:59 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str_j;

	if (!s1 || !s2)
		return (NULL);
	if (!(str_j = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
		+ 1))))
		return (NULL);
	ft_strcpy(str_j, s1);
	ft_strcat(str_j, s2);
	return (str_j);
}
