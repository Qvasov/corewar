/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:04:16 by ddarell           #+#    #+#             */
/*   Updated: 2019/11/29 21:04:18 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str = (char)(*str - 32);
		str++;
	}
	return (str);
}
