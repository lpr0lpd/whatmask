/*
    ctonm.h, Copyright (C) 2001-2003 Joe Laffey

    $Revision: 1.16 $

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef CTONM_H
#define CTONM_H


#include <stdlib.h>
#include <stdio.h>

#ifndef __dest_os
#define __dest_os	6969
#endif

#if __dest_os == __win32_os || __dest_os == __mac_os

#define EX_USAGE        64
#define EX_DATAERR		65
#define EX_SOFTWARE		70

#else
/* Windoze does not have this - or I can't find it... */
#include <sysexits.h>
#endif

#include "octets.h"
#include "printdata.h"
#include "myname.h"

#define BIT_LEN		3	/* Length of the CIDR bits string (including null) */

extern int ctonm_main(uint32);
extern int nmtoc_main(char*, uint32 );

#endif

