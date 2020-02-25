/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_web_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:44:14 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/15 20:44:15 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	memory(t_data *data)
{
	t_cur	*cur;
	int		i;

	i = -1;
	cur = data->vm.cursor;
	ft_fprintf(data->web.fd, "const memory_init = [");
	while (cur && cur->next)
		cur = cur->next;
	while (++i < MEM_SIZE)
	{
		if (cur && i == cur->pc)
		{
			data->web.arena[i] += 1000;
			ft_fprintf(data->web.fd, "%d", data->web.arena[i]);
			cur = cur->prev;
		}
		else
			ft_fprintf(data->web.fd, "%d", data->web.arena[i]);
		if (i + 1 == MEM_SIZE)
			ft_fprintf(data->web.fd, "];\n");
		else
			ft_fprintf(data->web.fd, ", ");
	}
}

static void	champions(t_data *data)
{
	int	i;

	ft_fprintf(data->web.fd, "const champion = [");
	i = -1;
	while (++i < data->vm.num_of_players)
	{
		ft_fprintf(data->web.fd, "[\"%s\", \"%s\", %d]",
				data->player[i].name, data->player[i].comment,
				data->player[i].id);
		if (i + 1 == data->vm.num_of_players)
			ft_fprintf(data->web.fd, "];\n");
		else
			ft_fprintf(data->web.fd, ", ");
	}
}

static void	arena_dup(uint64_t **dst, uint8_t *src)
{
	int	i;

	if (!(*dst = (uint64_t *)malloc(sizeof(int64_t) * MEM_SIZE)))
		ft_perror(NULL);
	ft_bzero((*dst), sizeof(int64_t) * MEM_SIZE);
	i = -1;
	while (++i < MEM_SIZE)
		(*dst)[i] += src[i];
}

void		web_init(t_data *data)
{
	int	i;

	i = -1;
	if ((data->web.fd = open("web/CW_visual.js",
			O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO)) < 0)
		ft_perror(NULL);
	if (!(data->web.curs = (int **)malloc(sizeof(int *) *
			data->vm.num_of_players)))
		ft_perror(NULL);
	while (++i < data->vm.num_of_players)
	{
		if (!(data->web.curs[i] = (int *)malloc(sizeof(int) * 17)))
			ft_perror(NULL);
		ft_bzero(&data->web.curs[i][0], sizeof(int) * 17);
		data->web.curs[i][0] = 1;
	}
	arena_dup(&data->web.arena, data->vm.arena);
	if (!(data->web.change = (int64_t *)malloc(sizeof(int64_t) * MEM_SIZE)))
		ft_perror(NULL);
	ft_memset(data->web.change, -1, 8 * (MEM_SIZE));
	champions(data);
	memory(data);
	ft_fprintf(data->web.fd, "const cycle = [");
}
