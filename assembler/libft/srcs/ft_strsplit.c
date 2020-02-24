/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:25:51 by laleta            #+#    #+#             */
/*   Updated: 2019/04/10 22:58:50 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wrd_cnt(char const *s, char c)
{
	size_t		wrd_cnt;
	size_t		i;

	i = 0;
	wrd_cnt = 0;
	while (s[i])
	{
		if (s[i] != c)
			wrd_cnt++;
		while (s[i] != c && s[i + 1])
			i++;
		i++;
	}
	return (wrd_cnt);
}

static size_t	ft_wrd_len(char const *s, char c)
{
	size_t		wrd_len;
	size_t		i;

	i = 0;
	wrd_len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i++])
		wrd_len++;
	return (wrd_len);
}

static size_t	ft_wrd_cpy(char *dest, const char *src, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}

static char		**ft_wrd_fill(char **tab, char const *s, char c, size_t wrd_cnt)
{
	size_t	i;
	size_t	wrd_len;
	size_t	j;

	i = 0;
	j = 0;
	while (i < wrd_cnt)
	{
		wrd_len = ft_wrd_len(&s[j], c);
		if (!(tab[i] = (char *)malloc(sizeof(char) * (wrd_len + 1))))
		{
			while (i--)
				ft_strdel(&tab[i]);
			free(tab);
			return (NULL);
		}
		while (s[j] == c)
			j++;
		j += ft_wrd_cpy(tab[i], &s[j], wrd_len);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**tab;
	size_t		wrd_cnt;

	if (!s)
		return (NULL);
	wrd_cnt = ft_wrd_cnt(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (wrd_cnt + 1))))
	{
		free(tab);
		return (NULL);
	}
	if (!ft_wrd_fill(tab, s, c, wrd_cnt))
		return (NULL);
	return (tab);
}
