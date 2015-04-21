/* 
    ctonm.c, Copyright (C) 2001-2003 Joe Laffey      
    
    $Revision: 1.17 $

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


#include "ctonm.h"
#include "bitfill.h"
#include "bitcount.h"

int ctonm_main(uint32 myInVal)
{
        
	uint32  myVal;

	char myNetmask[NM_LEN];
	char myNetmask2[NM_LEN];
	char cidr[4];

	uint32	usableIps;


	if(myInVal  >32)	/* it's unsigned so won't be < 0 */
	{
		fprintf(stderr, "%s: CIDR notations must be a number between 0 and 32 inclusive!\n", PACKAGE);
		return(EX_DATAERR);
	}


	myVal = bitfill_from_left(myInVal);


	u_int_to_octets(myVal, (char*)myNetmask);
	u_int_to_octets(~myVal, (char*)myNetmask2);
	
	usableIps = ~myVal; 
	
	/* check for underflow  - since we can't have an unsigned go negative */
	if(usableIps > 0)
		usableIps -= 1;


	snprintf(cidr, 4,"%" U_INT_32_PRINTF_STRING, myInVal);
	printdata(myVal, cidr, (char*) myNetmask, (char*) myNetmask2, usableIps);
	
	return(0);
}

