/* 
    nmtoc.c, Copyright (C) 2001-2003 Joe Laffey      
    
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
#include "validatemask.h"


int nmtoc_main(char* argv_one, uint32 myVal)
{
	char 	numBits[BIT_LEN];
	
	char	myNetmask[NM_LEN];
	char	myNetmask2[NM_LEN];
	
	uint32	usableIps;
	

	if( validatemask(myVal) )
	{
		/* This failed but may be Cisco-style */
		/* not it so we can see if it is cisco-style */
		myVal = ~myVal;	
		
		if( validatemask(myVal) )
		{
			/* Now we know it's bad */
			fprintf(stderr, "%s: \"%s\" is not a valid subnet mask or wildcard bit mask!\n", PACKAGE, argv_one);
			return(EX_DATAERR);
		}
	}

	
		
	

	snprintf((char*)numBits, BIT_LEN , "%" U_INT_32_PRINTF_STRING, bitcount(myVal));
	
	/*
	usableIps = bitfill_from_right(bitcount(~myVal));
	*/
	usableIps = ~myVal;
	
	/* check for underflow since we can't let the unsigned go negative */
	if(usableIps > 0)
		usableIps -= 1;
	

	u_int_to_octets(myVal, (char*)myNetmask);
	u_int_to_octets(~myVal, (char*)myNetmask2);
	
	printdata( myVal, (char*)numBits, (char*)myNetmask, (char*)myNetmask2, usableIps);

	return(0);
}
