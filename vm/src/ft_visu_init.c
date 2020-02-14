/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visu_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:15:20 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/12 17:15:24 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	memory(t_data *data)
{
	t_cur	*cur;
	int		i;

	i = -1;
	cur = data->vm.cursor;
	ft_fprintf(data->visu.fd, "const memory_init = [");
	while (cur && cur->next)
		cur = cur->next;
	while (++i < MEM_SIZE)
	{
		if (cur && i == cur->pc)
		{
			data->visu.arena[i] += 1000;
			ft_fprintf(data->visu.fd, "%d", data->visu.arena[i]);
			cur = cur->prev;
		}
		else
			ft_fprintf(data->visu.fd, "%d", data->visu.arena[i]);
		if (i + 1 == MEM_SIZE)
			ft_fprintf(data->visu.fd, "];\n");
		else
			ft_fprintf(data->visu.fd, ", ");
	}
}

static void	champions(t_data *data)
{
	int	i;

	ft_fprintf(data->visu.fd, "const champion = [");
	i = -1;
	while (++i < data->vm.num_of_players)
	{
		ft_fprintf(data->visu.fd, "[\"%s\", \"%s\", %d]",
		data->player[i].name, data->player[i].comment, data->player[i].id);
		if (i + 1 == data->vm.num_of_players)
			ft_fprintf(data->visu.fd, "];\n");
		else
			ft_fprintf(data->visu.fd, ", ");
	}
}

static void	arena_dup(uint64_t **dst, uint8_t *src)
{
	int	i;

	if (!(*dst = (uint64_t *)malloc(sizeof(int64_t) * MEM_SIZE)))
		ft_perror();
	ft_bzero((*dst), sizeof(int64_t) * MEM_SIZE);
	i = -1;
	while (++i < MEM_SIZE)
		(*dst)[i] += src[i];
}

void		ft_init_visu(t_data *data)
{
	int	i;

	i = -1;
	if ((data->visu.fd = open("visual.js", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO)) < 0)
		ft_perror();

	if (!(data->visu.curs = (int **)malloc(sizeof(int *) * data->vm.num_of_players)))
		ft_perror();
	while (++i < data->vm.num_of_players)
	{
		if (!(data->visu.curs[i] = (int *)malloc(sizeof(int) * 17)))
			ft_perror();
		ft_bzero(&data->visu.curs[i][1], sizeof(int) * 16);
		data->visu.curs[i][0] = 1;
	}
	arena_dup(&data->visu.arena, data->vm.arena);

	if (!(data->visu.change = (int64_t *)malloc(sizeof(int64_t) * MEM_SIZE)))
		ft_perror();
	ft_memset(data->visu.change, -1, 8 * (MEM_SIZE));
	champions(data);
	memory(data);
	ft_fprintf(data->visu.fd, "const cycle = [");
}
