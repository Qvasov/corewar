/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixclr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 20:55:30 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/08 21:02:48 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_matrixclr(char **matrix, size_t matrix_size)
{
	size_t i;

	if (matrix == NULL || *matrix == NULL)
		return ;
	i = 0;
	while (i < matrix_size)
	{
		free(matrix[i]);
		i++;
	}
	return ;
}
