/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_label_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:19:30 by laleta            #+#    #+#             */
/*   Updated: 2020/02/04 04:57:34 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"
#include "cw_asm_operation.h"

void		node_queue_free(t_node_queue *node)
{
	uint8_t	cnt;

	if (!node)
		return ;
	cnt = g_oper_tab[node->oper_id].arg_cnt;
	token_arr_free(node->argument, cnt);
	free(node);
}

t_label		*labelist_create_node(t_asm *assm, char **label_str,
															uint32_t byte_start)
{
	t_label		*new_node;

	if (!(new_node = (t_label *)ft_memalloc(sizeof(t_label))))
		error_handle(assm->file_name, ERR_MALLOC, assm, NULL);
	new_node->raw = ft_strdup(*label_str);
	new_node->hash = get_hash(*label_str);
	ft_strdel(label_str);
	new_node->byte_start = byte_start;
	new_node->next = NULL;
	return (new_node);
}

void		labelist_push_back(t_asm *assm, t_label **labelist,
										char **label_str, uint32_t byte_start)
{
	t_label *node;

	if (!labelist)
		return ;
	node = *labelist;
	if (!*labelist)
		*labelist = labelist_create_node(assm, label_str, byte_start);
	else
	{
		while (node->next)
			node = node->next;
		node->next = labelist_create_node(assm, label_str, byte_start);
	}
}

uint16_t	labelist_search(t_asm *assm, t_label *labelist, t_node_queue *node,
																const char *str)
{
	uint64_t	hash;
	char		str_err[32];
	char		*file_name;

	if (!labelist)
		error_handle(assm->file_name, "undefined label list\n", assm, NULL);
	hash = get_hash(str);
	while (labelist)
	{
		if (hash == labelist->hash)
			return (labelist->byte_start);
		labelist = labelist->next;
	}
	close(assm->fd_out);
	if ((file_name = ft_strjoin(assm->path_file_name, "cor")))
	{
		remove(file_name);
		free(file_name);
	}
	ft_sprintf(str_err, "undefined label %s\n", str);
	node_queue_free(node);
	error_handle(assm->file_name, str_err, assm, NULL);
	return (0);
}

void		labelist_free(t_label **labelist)
{
	t_label *node;
	t_label	*node_tmp;

	if (!labelist || !*labelist)
		return ;
	node = *labelist;
	while (node)
	{
		node_tmp = node->next;
		if (node->raw)
			free(node->raw);
		free(node);
		node = node_tmp;
	}
	*labelist = NULL;
}
