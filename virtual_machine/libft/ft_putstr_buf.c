/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:44:48 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/15 19:44:49 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_buf(char *buf, size_t *i, size_t buff_size, char *str)
{
	size_t	j;

	j = 0;
	while (str[j])
	{
		ft_putchar_buf(buf, i, buff_size, str[j]);
		++j;
	}
}
