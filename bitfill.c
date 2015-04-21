/* 
    bitfill.c, Copyright (C) 2001-2003 Joe Laffey      
    
    $Revision: 1.7 $

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

#include "bitfill.h"


/* This will fill in numBits bits with ones into an uint32.    */
/* The fill starts on the left and moves toward the right like this: */
/* 11111111000000000000000000000000                                  */
/* The caller must be sure numBits is between 0 and 32 inclusive     */
uint32 bitfill_from_left( uint32 numBits )
{
	uint32 myVal = 0;
	register int i;

	/* fill up the bits by adding ones so we have numBits ones */
	for(i = 0; i< numBits; i++)
	{
		myVal = myVal >> 1;
		myVal |= 0x80000000;
	}
	
	return myVal;
}



/* This will fill in numBits bits with ones into an uint32.     */
/* The fill starts on the right and moves toward the right like this: */
/* 00000000000000000000000011111111                                   */
/* The caller must be sure numBits is between 0 and 32 inclusive      */
uint32 bitfill_from_right( uint32 numBits )
{
	uint32 myVal = 0;
	register int i;
	
	/* fill up the bits by adding ones so we have numBits ones */
	for(i = 0; i< numBits; i++)
	{
		myVal = myVal << 1;
		myVal |= 1;
	}
	
	return myVal;
}
