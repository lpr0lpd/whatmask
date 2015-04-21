/* 
    printdata.c, Copyright (C) 2001-2003 Joe Laffey      
    
    $Revision: 1.10 $

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

#include "printdata.h"

#ifdef NO_LOCALE_SUPPORT
#undef HAVE_LOCALE_H
#endif

#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif

/* Format the names nicely */
void printdata(uint32 mask, char* cidr, char* nm, char* cisco, uint32 usableIps)
{

#ifndef NO_PRINT_HEADER        
	printf("\n---------------------------------------------\n");
	printf("       TCP/IP SUBNET MASK EQUIVALENTS\n");
	printf("---------------------------------------------\n");
#endif

	printf("CIDR = .....................: /%s\n", cidr);

	printf("Netmask = ..................: %s\n", nm);

	printf("Netmask (hex) = ............: 0x%08x\n", mask);

	printf("Wildcard Bits = ............: %s\n", cisco);
	
	printf("Usable IP Addresses = ......: %" U_INT_32_NUMERIC_PRINTF_STRING U_INT_32_PRINTF_STRING "\n", usableIps);

#ifndef NO_PRINT_HEADER        
	printf("\n");
#endif

}

