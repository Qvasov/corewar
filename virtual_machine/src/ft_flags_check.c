/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:22:06 by ddarell           #+#    #+#             */
/*   Updated: 2020/01/28 22:10:22 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_check_v(char **av, t_data *data)
{
	int check;
	int	num;

	num = ft_satoi(av[1], &check);
	if (!(check && av[1][check] == 0 && (num >= 0 && num <= 31)))
		ft_error("-v - argument error");
	data->v_flag = num;
}

void	ft_check_num_player(char **av, t_data *data)
{
	int num;
	int check;

	data->vm.num_of_players += 1;
	if (data->vm.num_of_players > MAX_PLAYERS)
		ft_error("too much players");
	num = ft_satoi(av[1], &check);
	if (!(check && av[1][check] == 0 && num <= MAX_PLAYERS && num > 0 &&
		data->player[num - 1].path == NULL))
		ft_error("-n - number error");
	check = ft_strlen(av[2]);
	if (check > 4)
		(ft_strcmp(av[2] + check - 4, ".cor") == 0) ?
		data->player[num - 1].path = av[2] :
		ft_error("-n - champion name error");
	else
		ft_error("-n - champion name error");
}

void	ft_check_dump(char **av, t_vm *vm)
{
	int check;

	vm->nbr_cycles = ft_satoi(av[1], &check);
	if (!(check && av[1][check] == 0))
		ft_error("-dump - argument error");
}
