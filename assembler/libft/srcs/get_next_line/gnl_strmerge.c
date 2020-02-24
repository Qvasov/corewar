/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_strmerge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:14:12 by laleta            #+#    #+#             */
/*   Updated: 2019/09/04 21:14:16 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strmerge(char *s1, const char *s2, size_t len)
{
	char		*fresh;
	const char	*init;
	const char	*init2;

	if (!(fresh = (char*)malloc(sizeof(*fresh) * len + 1)))
		return (NULL);
	init = fresh;
	if (s1)
	{
		init2 = s1;
		while (len && (*fresh = *s1))
		{
			++fresh;
			++s1;
			--len;
		}
		free((char*)init2);
	}
	while (len && (*fresh++ = *s2++))
		--len;
	if (!len)
		*fresh = '\0';
	return ((char*)init);
}
