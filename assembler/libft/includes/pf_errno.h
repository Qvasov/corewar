/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_errno.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 03:14:15 by laleta            #+#    #+#             */
/*   Updated: 2019/06/30 22:14:59 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_ERRNO_H
# define PF_ERRNO_H

# include <errno.h>

static char *g_errno_tab[] =
{
	"0 EUND Undefined error",
	"1 EPERM Operation not permitted",
	"2 ENOENT No such file or directory",
	"3 ESRCH No such process",
	"4 EINTR Interrupted system call",
	"5 EIO Input/output error",
	"6 ENXIO No such device or address",
	"7 E2BIG Argument list too long",
	"8 ENOEXEC Exec format error",
	"9 EBADF Bad file descriptor",
	"10 ECHILD  No child processes",
	"11 EAGAIN Resource temporarily unavailable",
	"11 EWOULDBLOCK Resource temporarily unavailable",
	"12 ENOMEM Cannot allocate memory",
	"13 EACCES Permission denied",
	"14 EFAULT Bad address",
	"15 ENOTBLK Block device required",
	"16 EBUSY Device or resource busy",
	"17 EEXIST File exists",
	"18 EXDEV Invalid cross-device link",
	"19 ENODEV No such device",
	"20 ENOTDIR Not a directory",
	"21 EISDIR Is a directory",
	"22 EINVAL Invalid argument",
	"23 ENFILE Too many open files in system",
	"24 EMFILE Too many open files",
	"25 ENOTTY Inappropriate ioctl for device",
	"26 ETXTBSY Text file busy",
	"27 EFBIG File too large",
	"28 ENOSPC No space left on device",
	"29 ESPIPE Illegal seek",
	"30 EROFS Read-only file system",
	"31 EMLINK Too many links",
	"32 EPIPE Broken pipe",
	"33 EDOM Numerical argument out of domain",
	"34 ERANGE Numerical result out of range",
	"35 EDEADLOCK Resource deadlock avoided",
	"36 ENAMETOOLONG File name too long",
	"37 ENOLCK No locks available",
	"38 ENOSYS Function not implemented",
	"39 ENOTEMPTY Directory not empty",
	"40 ELOOP Too many levels of symbolic links",
	"42 ENOMSG No message of desired type",
	"43 EIDRM Identifier removed",
	"44 ECHRNG Channel number out of range",
	"45 EL2NSYNC Level 2 not synchronized",
	"46 EL3HLT Level 3 halted",
	"47 EL3RST Level 3 reset",
	"48 ELNRNG Link number out of range",
	"49 EUNATCH Protocol driver not attached",
	"50 ENOCSI No CSI structure available",
	"51 EL2HLT Level 2 halted",
	"52 EBADE Invalid exchange",
	"53 EBADR Invalid request descriptor",
	"54 EXFULL Exchange full",
	"55 ENOANO No anode",
	"56 EBADRQC Invalid request code",
	"57 EBADSLT Invalid slot",
	"59 EBFONT Bad font file format",
	"60 ENOSTR Device not a stream",
	"61 ENODATA No data available",
	"62 ETIME Timer expired",
	"63 ENOSR Out of streams resources",
	"64 ENONET Machine is not on the network",
	"65 ENOPKG Package not installed",
	"66 EREMOTE Object is remote",
	"67 ENOLINK Link has been severed",
	"68 EADV Advertise error",
	"69 ESRMNT Srmount error",
	"70 ECOMM Communication error on send"
};

#endif
