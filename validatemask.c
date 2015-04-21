/* 
    validatemask.c, Copyright (C) 2001-2003 Joe Laffey      
    
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

#include "validatemask.h"

/* validatemask checks to see that an unsigned long    */
/* has all 1s in a row starting on the left like this */
/* Good: 11111111111111111111111110000000              */
/* returns 0 on success, 1 on failure                  */
int validatemask(uint32 myInt)
{
	int foundZero = 0;

	while (myInt != 0)
   	{			/* while more bits to count */

		if( (myInt  & 0x80000000) !=0)	/* test leftmost bit */
		{
			if(foundZero)
				return 1; /* bad */
		}
		else
		{
			foundZero = 1;
		}
			
      	myInt <<= 1; /* shift off the left - zero fill */
	}

	return (0); /* good */

}
