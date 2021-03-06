/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 20:25:40 by laleta            #+#    #+#             */
/*   Updated: 2020/02/14 23:24:13 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

static void	del_file(t_disasm *disassm)
{
	char	*file_name;

	close(disassm->fd_out);
	if ((file_name = ft_strjoin(disassm->path_file_name, "s")))
	{
		remove(file_name);
		free(file_name);
	}
}

void		error_handle(const char *name, const char *err_str, t_asm *assm,
															t_disasm *disassm)
{
	const char	str_asm[] = "s";
	const char	str_disasm[] = "cor";
	char		*s;

	if (!g_disasm)
		s = (char *)str_asm;
	else
		s = (char *)str_disasm;
	ft_printf(CL_ER " %s%s " NONE F_RED "\tERROR: %s\n" NONE, name, s, err_str);
	if (errno)
		ft_printf(F_RED "%s\n" NONE, strerror(errno));
	if (!g_disasm && assm)
		asm_free(assm);
	if (g_disasm && disassm)
	{
		if (disassm->fd_out != -1)
			del_file(disassm);
		disasm_free(disassm);
	}
	exit(1);
}

void		error_handle2(const char *name, const char *err_str, t_asm *assm,
															t_disasm *disassm)
{
	ft_printf(CL_ER " %s " NONE F_RED "\tERROR: %s\n" NONE, name, err_str);
	if (errno)
		ft_printf(F_RED "%s\n" NONE, strerror(errno));
	if (!g_disasm && assm)
		asm_free(assm);
	if (g_disasm && disassm)
		disasm_free(disassm);
	exit(1);
}

void		error_handle_adv(t_asm *assm, t_inline *iline, const char *err_str,
															t_token **token)
{
	uint64_t	col;

	col = iline->col_alt == 1 ? iline->col_alt : iline->col + 1;
	if (!token || (token && (*token) && !(*token)->raw))
	{
		ft_printf(CL_ER " %ss " NONE, assm->file_name);
		ft_printf(CL_INFO "\t=>[%u:%u]<=" NONE F_RED " ERROR: %s\n", iline->row,
																col, err_str);
	}
	else
	{
		ft_printf(CL_ER " %ss " NONE, assm->file_name);
		ft_printf(CL_INFO "\t=>[%u:%u]<=" NONE F_RED " ERROR: %s ", iline->row,
									col - ft_strlen((*token)->raw), err_str);
		ft_printf(CL_INFO "=>[%s]<=\n" NONE, (*token)->raw);
	}
	if (assm)
		asm_free(assm);
	if (token)
		token_free(token);
	if (iline)
		ft_strdel(&iline->str);
	exit(1);
}

void		error_handle_adv2(t_asm *assm, t_inline *iline, const char *err_str,
															t_token **token)
{
	if (!token || (token && (*token) && !(*token)->raw))
	{
		ft_printf(CL_ER " %ss " NONE, assm->file_name);
		ft_printf(CL_INFO "\t=>[%u:%u]<=" NONE F_RED " ERROR: %s\n", iline->row,
													iline->col + 1, err_str);
	}
	else
	{
		ft_printf(CL_ER " %ss " NONE, assm->file_name);
		ft_printf(CL_INFO "\t=>[%u:%u]<=" NONE F_RED " ERROR: %s ", iline->row,
						iline->col - ft_strlen((*token)->raw) + 1, err_str);
		ft_printf(CL_INFO "=>[%s]<=\n" NONE, (*token)->raw);
	}
	if (assm)
		asm_free(assm);
	if (iline)
		ft_strdel(&iline->str);
}
