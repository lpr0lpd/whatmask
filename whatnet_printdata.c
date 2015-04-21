/* 
    whatnet_printdata.c, Copyright (C) 2001-2003 Joe Laffey      

    $Revision: 1.8 $
    
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

#include "whatnet_printdata.h"

#ifdef NO_LOCALE_SUPPORT
#undef HAVE_LOCALE_H
#endif

#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif

/* Format the names nicely */

void whatnet_printdata( uint32 mask, char* myIpStr, char* myMaskStr, char* myWildcardStr, char* myCIDRStr, char* myNtStr, char* myBrStr, char* myStartIpStr, char* myEndIpStr, uint32 usableIps )
{

#ifndef NO_PRINT_HEADER        
	printf("\n------------------------------------------------\n");
	printf("           TCP/IP NETWORK INFORMATION\n");
	printf("------------------------------------------------\n");
#endif

	printf("IP Entered = ..................: %s\n", myIpStr);
	
	printf("CIDR = ........................: /%s\n", myCIDRStr);	

	printf("Netmask = .....................: %s\n", myMaskStr);

	printf("Netmask (hex) = ...............: 0x%08x\n", mask);

	printf("Wildcard Bits = ...............: %s\n", myWildcardStr);	
	
#ifndef NO_PRINT_HEADER          
	printf("------------------------------------------------\n");
#endif
	
	printf("Network Address = .............: %s\n", myNtStr);
	
	printf("Broadcast Address = ...........: %s\n", myBrStr);	

	printf("Usable IP Addresses = .........: %" U_INT_32_NUMERIC_PRINTF_STRING U_INT_32_PRINTF_STRING "\n", usableIps);

	printf("First Usable IP Address = .....: %s\n", myStartIpStr);	
		
	printf("Last Usable IP Address = ......: %s\n", myEndIpStr);	
	
	
#ifndef NO_PRINT_HEADER        
	printf("\n");
#endif

}

