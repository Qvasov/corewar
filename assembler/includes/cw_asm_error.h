/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 22:47:53 by laleta            #+#    #+#             */
/*   Updated: 2020/03/04 00:31:50 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_ASM_ERROR_H
# define CW_ASM_ERROR_H

# define ERR_MALLOC				"memory allocation failure"
# define ERR_FILE_NAME			"file name is too long"
# define ERR_FILE_TYPE			"wrong file type, [*.s] for -a, [*.cor] for -d"
# define ERR_REG_NBR			"register number out of range"
# define ERR_NAME_REDEFINE		"champion name is redefined"
# define ERR_COMMENT_REDEFINE	"champion comment is redefined"
# define ERR_NAME_MISSING		"champion name is missing"
# define ERR_COMMENT_MISSING	"champion comment is missing"
# define ERR_NAME_UNFINISH		"champion name is unfinished"
# define ERR_COMMENT_UNFINISH	"champion comment is unfinished"
# define ERR_HEADER_UNFINISH	"champion header is unfinished"
# define ERR_NAME_LENGTH		"champion name is too long"
# define ERR_COMMENT_LENGTH		"champion comment is too long"
# define ERR_TOKEN_INVALID		"invalid or unexpected token"
# define ERR_OPERATION_MISSING	"operation is missing"
# define ERR_ARGTYPE_INVALID	"invalid argument type"
# define ERR_ARGUMENT_INVALID	"invalid argument"
# define ERR_ARGUMENT_MISSING	"argument is missing"
# define ERR_EXTRA_TOKEN		"too many arguments"
# define ERR_EXTRA_CHAR			"extra char at the end of operation"
# define ERR_NO_OPERATION		"operations not found"
# define ERR_CHAMP_MAXSIZE		"champion code is too large"
# define ERR_CHAMP_MINSIZE		"champion code is too small"
# define ERR_CHAMP_SIZE			"wrong champion code size"
# define ERR_READFILE			"unable to read the file"
# define ERR_MAGIC_NUMBER		"wrong magic number"
# define ERR_OPERATION_INVALID	"invalid operation code"
# define ERR_EXTRA_SEPARATOR	"extra separator"
# define ERR_HEADER_EXTRA_CHAR	"invalid char in header"
# define ERR_END_NEWLINE		"no end with a newline"
# define ERR_EMPTY_FILE			"empty or invalid file"

#endif
