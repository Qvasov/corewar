/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 20:37:00 by ddarell           #+#    #+#             */
/*   Updated: 2019/04/30 18:24:21 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		len;
	int		start;
	int		end;
	char	*trim;

	len = ft_strlen(s);
	i = len;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == 0) && i != 0)
		i--;
	end = i;
	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	start = i;
	len = (end - start + 1 > 0) ? (end - start + 1) : (0);
	if ((trim = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (start++ <= end)
		trim[start - i - 1] = s[start - 1];
	trim[start - i - 1] = '\0';
	return (trim);
}
