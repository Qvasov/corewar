/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:01:36 by ddarell           #+#    #+#             */
/*   Updated: 2019/05/08 20:47:01 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_put(char *dst, const char *src, char c, int nex)
{
	int parts;
	int i;
	int j;

	i = 0;
	parts = 0;
	j = 0;
	while (src[i] && parts <= nex)
	{
		if (parts == nex && src[i] != c)
		{
			dst[j] = src[i];
			j++;
		}
		i++;
		if (src[i - 1] != c && (src[i] == c || src[i] == 0))
			parts++;
	}
	dst[j] = 0;
	return (0);
}

static int	ft_len(char const *s, char c, int nex)
{
	int parts;
	int i;
	int len;

	i = 0;
	parts = 0;
	len = 0;
	while (s[i] && parts <= nex)
	{
		if (parts == nex && s[i] != c)
			len++;
		i++;
		if (s[i - 1] != c && (s[i] == c || s[i] == 0))
			parts++;
	}
	return (len);
}

static int	ft_parts(char const *s, char c)
{
	int parts;
	int i;

	i = 0;
	parts = 0;
	while (s[i])
	{
		i++;
		if (s[i - 1] != c && (s[i] == c || s[i] == 0))
			parts++;
	}
	return (parts);
}

char		**ft_strsplit(char const *s, char c)
{
	int		parts;
	int		i;
	char	**split;

	i = -1;
	if (s == NULL)
		return (NULL);
	parts = ft_parts(s, c);
	if (!(split = (char**)malloc(sizeof(char*) * (parts + 1))))
		return (NULL);
	while (++i < parts)
	{
		if (!(split[i] = (char*)malloc(sizeof(char) * (ft_len(s, c, i) + 1))))
		{
			ft_bclean(split, i);
			free(split);
			return (NULL);
		}
		ft_put(split[i], s, c, i);
	}
	split[i] = 0;
	return (split);
}
