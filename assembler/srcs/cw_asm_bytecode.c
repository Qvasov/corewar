/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_bytecode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:53:10 by laleta            #+#    #+#             */
/*   Updated: 2020/03/03 20:41:06 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"
#include "cw_asm_operation.h"

void			write_bytes(int fd, uint64_t nbr, uint8_t bytes)
{
	while (bytes)
	{
		ft_putchar_fd(((nbr >> ((bytes - 1) * 8)) & 0xFF), fd);
		bytes--;
	}
}

static uint32_t	set_arg_nbr(t_asm *assm, t_token *argument, t_node_queue *node,
														uint32_t bytes_added)
{
	uint8_t		offset;
	uint32_t	nbr;

	offset = 0;
	if (argument->subtype == T_REG)
		return (ft_atoi(&(argument->raw[1])));
	offset = argument->subtype == T_DIR ? 1 : 0;
	if (argument->raw[offset] == LABEL_CHAR)
	{
		nbr = labelist_search(assm, assm->labels, node,
												&(argument->raw[offset + 1]));
		if (nbr > bytes_added)
			nbr -= bytes_added;
		else
			nbr = (0xFFFFFFFF - (bytes_added - nbr - 1));
	}
	else
		nbr = ft_atoi(&(argument->raw[offset]));
	return (nbr);
}

static void		write_argument(t_asm *assm, t_node_queue *node,
														uint32_t bytes_added)
{
	int8_t		i;
	uint32_t	nbr;
	uint8_t		byte;

	i = 0;
	while (i < g_oper_tab[node->oper_id].arg_cnt)
	{
		nbr = set_arg_nbr(assm, node->argument[i], node, bytes_added);
		if (node->argument[i]->subtype == T_REG)
			byte = REGNBR_SIZE;
		else if (node->argument[i]->subtype == T_IND)
			byte = IND_SIZE;
		else
			byte = g_oper_tab[node->oper_id].dir_size;
		token_free(&node->argument[i]);
		write_bytes(assm->fd_out, nbr, byte);
		i++;
	}
	free(node->argument);
}

void			write_bytecode(t_asm *assm, t_header *header,
															t_oper_queue *queue)
{
	t_node_queue	*node;
	uint32_t		bytes_added;

	bytes_added = 0;
	write_bytes(assm->fd_out, header->magic, 4);
	write(assm->fd_out, header->prog_name, PROG_NAME_LENGTH + 4);
	write_bytes(assm->fd_out, header->prog_size, 4);
	write(assm->fd_out, header->comment, COMMENT_LENGTH + 4);
	while (!operqueue_is_empty(assm->oper_queue))
	{
		node = operqueue_pop(queue);
		write_bytes(assm->fd_out, node->oper_id, 1);
		if (node->arg_code)
			write_bytes(assm->fd_out, node->arg_code, 1);
		write_argument(assm, node, bytes_added);
		bytes_added += node->bytes;
		free(node);
	}
}

void			translate_to_bytecode(t_asm *assm)
{
	char	*str;

	str = ft_strnew(ft_strlen(assm->path_file_name) + 3);
	ft_strcpy(str, assm->path_file_name);
	ft_strcat(str, "cor");
	if ((assm->fd_out = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		error_handle2(str, strerror(errno), assm, NULL);
	free(str);
	write_bytecode(assm, assm->header, assm->oper_queue);
}
