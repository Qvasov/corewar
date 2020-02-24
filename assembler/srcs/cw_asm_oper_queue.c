/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_oper_queue.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:58:21 by laleta            #+#    #+#             */
/*   Updated: 2020/02/03 20:17:09 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

t_node_queue	*operqueue_create_node(uint8_t oper_type, uint8_t arg_code,
										uint8_t byte_size, t_token **argument)
{
	t_node_queue	*node;

	if (!(node = (t_node_queue *)ft_memalloc(sizeof(t_node_queue))))
		return (NULL);
	node->arg_code = arg_code;
	node->oper_id = oper_type;
	node->argument = argument;
	node->bytes = byte_size;
	node->next = NULL;
	return (node);
}

void			operqueue_push(t_asm *assm, t_oper_queue *queue,
															t_node_queue *node)
{
	if (!node)
		error_handle(assm->file_name, ERR_MALLOC, assm, NULL);
	if (!queue->first)
		queue->first = node;
	else
		queue->last->next = node;
	queue->last = node;
	queue->byte_total += node->bytes;
	queue->oper_cnt++;
}

t_node_queue	*operqueue_pop(t_oper_queue *queue)
{
	t_node_queue	*node;

	if (!queue || !queue->first)
		return (NULL);
	node = queue->first;
	queue->first = queue->first->next;
	if (!queue->first)
		queue->last = NULL;
	queue->byte_total -= node->bytes;
	queue->oper_cnt--;
	return (node);
}

int8_t			operqueue_is_empty(t_oper_queue *queue)
{
	if (!queue || !queue->first)
		return (1);
	return (0);
}

void			operqueue_free(t_oper_queue *queue)
{
	t_node_queue	*node;
	t_node_queue	*tmp;
	int8_t			i;

	if (!queue)
		return ;
	node = queue->first;
	while (node)
	{
		tmp = node->next;
		if (node->argument)
		{
			i = -1;
			while (node->argument[++i])
				token_free(&(node->argument[i]));
			free(node->argument);
		}
		free(node);
		node = tmp;
	}
	free(queue);
}
