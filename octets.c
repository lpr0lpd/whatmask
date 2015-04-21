/*
    octets.c, Copyright (C) 2001-2003 Joe Laffey

    $Revision: 1.11 $

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

#include "octets.h"

/* Creates a netmask string (e.g. "255.255.255.192")  */
/* from an unsgined int. The argument buf should have */
/* at least NM_LEN bytes allocated to it.             */
char* u_int_to_octets( uint32 myVal, char* buf)
{
	uint32 	val1,
					val2,
					val3,
					val4;


	val1 = myVal & 0xff000000;
	val1 = val1  >>24;
	val2 = myVal & 0x00ff0000;
	val2 = val2  >>16;
	val3 = myVal & 0x0000ff00;
	val3 = val3 >>8;
	val4 = myVal & 0x000000ff;

	snprintf(buf, NM_LEN, "%" U_INT_32_PRINTF_STRING ".%" U_INT_32_PRINTF_STRING ".%" U_INT_32_PRINTF_STRING ".%" U_INT_32_PRINTF_STRING, val1, val2, val3, val4);

	return(buf);

}


/* Takes an octet string (e.g. "255.255.255.192")            */
/* and creates an unsgined int. The argument buf should be   */
/* the string and myVal is a pointer to an uint32      */
/* returns 0 on success and 1 on failure.                    */
int octets_to_u_int( uint32* myVal, char* buf)
{
	uint32 	val1,
					val2,
					val3,
					val4;
	
	
	*myVal = 0;

	
	if( sscanf(buf, "%" U_INT_32_PRINTF_STRING ".%" U_INT_32_PRINTF_STRING ".%" U_INT_32_PRINTF_STRING ".%" U_INT_32_PRINTF_STRING, &val1, &val2, &val3, &val4) != 4 )
	{
		return(1); /* failure */
	}
	
	if( val1 > 255 || 
		val2 > 255 || 
		val3 > 255 || 
		val4 > 255   )
	{
		/* bad input */
		return(1);
	}
	
	*myVal |= val4;
	val3 <<= 8;
	*myVal |= val3;
	val2 <<= 16;
	*myVal |= val2;
	val1 <<= 24;
	*myVal |= val1;

	/* myVal was passed by reference so it is already setup for the caller */
	return(0); /* success */

}


