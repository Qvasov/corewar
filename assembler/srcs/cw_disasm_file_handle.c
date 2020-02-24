/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_disasm_file_handle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 20:27:30 by laleta            #+#    #+#             */
/*   Updated: 2020/02/24 12:56:23 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

void	copy_champion(char *champ_raw, t_disasm *disassm, uint64_t total_size)
{
	ft_memcpy(&disassm->header, champ_raw, sizeof(t_header));
	disassm->header.magic = swap_byte4(disassm->header.magic);
	if (disassm->header.magic != COREWAR_EXEC_MAGIC)
		error_handle(disassm->file_name, ERR_MAGIC_NUMBER, NULL, disassm);
	disassm->header.prog_size = swap_byte4(disassm->header.prog_size);
	if (disassm->header.prog_size != total_size - HEADER_SIZE)
		error_handle(disassm->file_name, ERR_CHAMP_SIZE, NULL, disassm);
	ft_memcpy(disassm->program, champ_raw + sizeof(t_header),
													disassm->header.prog_size);
	disassm->header.prog_name[PROG_NAME_LENGTH] = '\0';
	disassm->header.comment[COMMENT_LENGTH] = '\0';
}

void	disasm_file_handle(t_disasm *disassm, int32_t fd)
{
	int64_t	ret;
	char	buf[CHAMP_MAX_SIZE + HEADER_SIZE + 2];

	if ((ret = read(fd, buf, CHAMP_MAX_SIZE + HEADER_SIZE + 1)) <= 0)
		error_handle(disassm->file_name, ERR_READFILE, NULL, disassm);
	if (ret <= HEADER_SIZE)
		error_handle(disassm->file_name, ERR_CHAMP_MINSIZE, NULL, disassm);
	copy_champion(buf, disassm, ret);
}
