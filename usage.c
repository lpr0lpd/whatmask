/* 
    usage.h, Copyright (C) 2001-2003 Joe Laffey     
    Usage for Whatmask 

    $Revision: 1.6 $
    
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#else
#include "myTypes.h"
#endif


#include <stdlib.h>
#include <stdio.h>

#ifndef __dest_os
#define __dest_os	6969
#endif


#if __dest_os == __win32_os || __dest_os == __mac_os

#define EX_USAGE        64
#define EX_DATAERR		65

#else
/* Windoze does not have this - or I can't find it... */
#include <sysexits.h>
#endif

#include "myname.h"
#include "usage.h"

int usage(void)
{

#if __dest_os != __mac_os
	printf("\n%s v%s, Copyright (C) 2001-2003 Joe Laffey <joe@laffeycomputer.com>\n", PACKAGE, VERSION);
	printf("This binary compiled on %s at %s\n", __DATE__, __TIME__ );
	printf("Visit: http://www.laffeycomputer.com/software.html for updates.\n");

	printf("%s comes with ABSOLUTELY NO WARRANTY; for details see the COPYING file\nthat accompained this distribution. ", PACKAGE);
	printf("This is free software, and you are welcome\nto redistribute it");
	printf(" under the terms of GNU PUBLIC LICENSE.\n");
#endif
	printf("\n%s may be used two ways:\n\n", PACKAGE);
	printf("Given a mask:          %s <CIDR bits>\n", PACKAGE);
	printf("               - or -  %s <subnet mask>\n", PACKAGE);
	printf("               - or -  %s <hex subnet mask>\n", PACKAGE);
	printf("               - or -  %s <wildcard bit mask>\n", PACKAGE);
	printf(" NOTE: %s will autodetect the input and show you all four.\n\n", PACKAGE);
	
	printf("Given an ip/mask:      %s <IP address>/<netmask>\n", PACKAGE);
	printf("       <netmask> may be one of the following:\n");
	printf("                       CIDR notation (e.g. \"24\")\n");
	printf("                       Netmask notation (e.g. \"255.255.255.0\")\n");
	printf("                       Hex Netmask notation (e.g. \"0xffffff00\")\n");
	printf("                       Wildcard bits notation (e.g. \"0.0.0.255\")\n");
	printf(" NOTE: %s will autodetect the netmask format.\n", PACKAGE);
	return(EX_USAGE);

}
