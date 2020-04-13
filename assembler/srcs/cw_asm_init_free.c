/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_init_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:55:20 by laleta            #+#    #+#             */
/*   Updated: 2020/03/03 23:22:27 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

static void	set_filename(t_asm *assm, char *file_name)
{
	char	*name;
	int32_t	len;

	name = NULL;
	len = ft_strlen(file_name);
	if (!(assm->path_file_name = ft_strnew(len - 1)))
		error_handle(file_name, ERR_MALLOC, assm, NULL);
	ft_strncpy(assm->path_file_name, file_name, len - 1);
	name = ft_strrchr(assm->path_file_name, '/');
	if (name)
		name++;
	else
		name = assm->path_file_name;
	assm->file_name = name;
}

void		asm_init(t_asm **assm, char *file_name, int32_t fd)
{
	if (!((*assm) = (t_asm *)malloc(sizeof(t_asm))))
		error_handle(file_name, ERR_MALLOC, NULL, NULL);
	(*assm)->header = NULL;
	(*assm)->oper_queue = NULL;
	(*assm)->path_file_name = NULL;
	(*assm)->file_name = NULL;
	(*assm)->labels = NULL;
	if (!((*assm)->header = (t_header *)ft_memalloc(sizeof(t_header))) ||
		!((*assm)->oper_queue = (t_oper_queue *)malloc(sizeof(t_oper_queue))))
		error_handle(file_name, ERR_MALLOC, *assm, NULL);
	ft_memset((*assm)->header, 0, sizeof((*assm)->header));
	(*assm)->header->magic = COREWAR_EXEC_MAGIC;
	(*assm)->oper_queue->first = NULL;
	(*assm)->oper_queue->last = NULL;
	(*assm)->oper_queue->byte_total = 0;
	(*assm)->oper_queue->oper_cnt = 0;
	(*assm)->fd_in = fd;
	set_filename(*assm, file_name);
}

void		asm_free(t_asm *assm)
{
	if (assm)
	{
		if (assm->path_file_name)
			free(assm->path_file_name);
		if (assm->header)
			free(assm->header);
		if (assm->labels)
			labelist_free(&assm->labels);
		if (assm->oper_queue)
			operqueue_free(assm->oper_queue);
		free(assm);
	}
	get_next_line(-2, NULL);
}

void		token_free(t_token **token)
{
	if (*token)
	{
		if ((*token)->raw)
			ft_strdel(&(*token)->raw);
		free(*token);
		*token = NULL;
	}
}

void		token_arr_free(t_token **token_arr, uint8_t cnt)
{
	uint8_t	i;

	i = 0;
	while (i < cnt)
	{
		if (token_arr[i])
			token_free(&token_arr[i]);
		i++;
	}
	free(token_arr);
}
