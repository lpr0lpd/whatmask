/*
    octets.h, Copyright (C) 2001-2003 Joe Laffey

    $Revision: 1.5 $

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


#ifndef OCTETS_H
#define OCTETS_H



#include <stdio.h>

#define NM_LEN	16 	/* The max length of an octet string */
			/* e.g. "xxx.xxx.xxx.xxx" + the null  */

extern char* u_int_to_octets(uint32, char*);
extern int octets_to_u_int(uint32*, char*);


#endif
