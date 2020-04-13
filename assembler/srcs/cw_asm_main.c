/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 04:43:03 by laleta            #+#    #+#             */
/*   Updated: 2020/03/04 03:45:50 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

uint8_t	g_disasm = 0;

static int32_t	valid_file(const char *file_name)
{
	int32_t	fd;
	char	*file_type;
	int32_t	len;

	if ((len = ft_strlen(file_name)) > MAX_FILE_PATH - 3)
		error_handle2(file_name, ERR_FILE_NAME, NULL, NULL);
	if ((file_type = ft_strrchr(file_name, '.')) &&
			((!g_disasm && ft_strequ(file_type, ".s")) ||
			(g_disasm && ft_strequ(file_type, ".cor"))))
		return (fd = open(file_name, O_RDONLY));
	else
		error_handle2(file_name, ERR_FILE_TYPE, NULL, NULL);
	return (-1);
}

void			disassembler(int32_t fd, char *file_name)
{
	t_disasm	*disassm;

	disassm = NULL;
	disasm_init(&disassm, file_name);
	disasm_file_handle(disassm, fd);
	close(fd);
	translate_to_source(disassm);
	ft_printf(CL_OK " %scor " NONE, disassm->file_name);
	ft_printf(F_GREEN "\tWriting output code to %ss\n\n" NONE,
													disassm->path_file_name);
	disasm_free(disassm);
}

void			assembler(int32_t fd, char *file_name)
{
	t_asm	*assm;

	assm = NULL;
	asm_init(&assm, file_name, fd);
	file_handle(assm);
	close(fd);
	translate_to_bytecode(assm);
	ft_printf(CL_OK " %ss " NONE, assm->file_name);
	ft_printf(F_GREEN "\tWriting output program to %scor\n\n" NONE,
														assm->path_file_name);
	close(assm->fd_out);
	asm_free(assm);
}

static int32_t	usage(void)
{
	ft_printf("usage:\n\tassembler:	./asm -a file.s\n"
									"\tdisassembler:	./asm -d file.cor\n");
	return (1);
}

int32_t			main(int32_t argc, char **argv)
{
	int32_t	i;
	int32_t	fd;

	i = 1;
	if (argc < 3 || (!(g_disasm = ft_strequ("-d", argv[1])) &&
													!ft_strequ("-a", argv[1])))
		return (usage());
	while (++i < argc)
	{
		if ((fd = valid_file(argv[i])) != -1)
			!g_disasm ? assembler(fd, argv[i]) : disassembler(fd, argv[i]);
		else
		{
			if (errno)
			{
				ft_printf(CL_ER " %s " NONE, argv[i]);
				ft_printf(F_RED "\tERROR: %s\n\n" NONE, strerror(errno));
			}
			continue ;
		}
	}
	return (0);
}
