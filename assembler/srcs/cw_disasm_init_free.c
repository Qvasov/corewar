/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_init_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:55:20 by laleta            #+#    #+#             */
/*   Updated: 2020/02/17 20:58:48 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

static void	set_filename(t_disasm *disassm, char *file_name)
{
	char	*name;
	int32_t	len;

	name = NULL;
	len = ft_strlen(file_name);
	if (!(disassm->path_file_name = ft_strnew(len - 3)))
		error_handle(file_name, ERR_MALLOC, NULL, disassm);
	ft_strncpy(disassm->path_file_name, file_name, len - 3);
	name = ft_strrchr(disassm->path_file_name, '/');
	if (name)
		name++;
	else
		name = disassm->path_file_name;
	disassm->file_name = name;
}

void		disasm_init(t_disasm **disassm, char *file_name)
{
	char	*str;

	if (!((*disassm) = (t_disasm *)malloc(sizeof(t_disasm))))
		error_handle(file_name, ERR_MALLOC, NULL, NULL);
	(*disassm)->fd_out = -1;
	(*disassm)->path_file_name = NULL;
	(*disassm)->file_name = NULL;
	ft_memset(&(*disassm)->header, 0, sizeof((*disassm)->header));
	set_filename(*disassm, file_name);
	str = ft_strnew(ft_strlen((*disassm)->path_file_name) + 1);
	ft_strcpy(str, (*disassm)->path_file_name);
	ft_strcat(str, "s");
	if (((*disassm)->fd_out = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666)) ==
																			-1)
		error_handle2(str, strerror(errno), NULL, *disassm);
	free(str);
}

void		disasm_free(t_disasm *disassm)
{
	if (disassm)
	{
		if (disassm->path_file_name)
			free(disassm->path_file_name);
		free(disassm);
	}
}
