/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:41:48 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/09 15:33:37 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main()
{
	int a;
	a = -2147483647;
	printf("%d\n", a);
	a = a * (-1);
	printf("%d\n", a);
	return (1);
}
