/* 
    whatnet.c, Copyright (C) 2001-2003 Joe Laffey      
    Network Info Processing for Whatmask

    $Revision: 1.21 $    

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

#include <stdio.h>
#include <string.h>
#include "octets.h"
#include "bitfill.h"
#include "bitcount.h"
#include "validatemask.h"
#include "whatnet_printdata.h"
#include "myname.h"
#include "usage.h"


#include "whatnet.h"

int whatnet_main(char* myIpPtr, char* myMaskPtr)
{
	
	uint32 		myIp,		/* ip address */
				myMask,		/* subnet mask */
				myCIDR,		/* CIDR style mask */
				myBr,		/* Broadcast address */
				myNt;		/* Network address */
	
	char		myIpStr[NM_LEN],		/* ip address as string */
				myMaskStr[NM_LEN],		/* subnet mask as string */
				myNtStr[NM_LEN],		/* Network address as string */
				myBrStr[NM_LEN],		/* broadcast address as string */
				myStartIpStr[NM_LEN],	/* starting usable address as string */
				myEndIpStr[NM_LEN],		/* ending usable address as string */
				myWildcardStr[NM_LEN],	/* wildcard mask as string */
				myCIDRStr[BIT_LEN];		/* CIDR bits as string */				
	
	uint32		usableIps; 	/* number of usable ips addresses */
	


	/* try to convert the octets to the ip - this also returns 1 if the conversion fails */
	if(octets_to_u_int(&myIp, myIpPtr))
	{
		fprintf(stderr, "%s: \"%s\" is not a valid IP address! IP addresses take the form\n\"xxx.xxx.xxx.xxx\" where each octet (group of numbers separated by dots) must be\nbetween 0 and 255 inclusive!\n", PACKAGE, myIpPtr);
		return(EX_SOFTWARE);	
	}
	
	if(    (myMaskPtr[0] == '0') 
	  	&& (myMaskPtr[1] =='x' || myMaskPtr[1] == 'X') 
	  )
	{
	
	  	if(
		 !(  (myMaskPtr[2] >= 'a' && myMaskPtr[2] <= 'f')
			 ||(myMaskPtr[2] >= 'A' && myMaskPtr[2] <= 'F')
			 ||(myMaskPtr[2] >= '0' && myMaskPtr[2] <= '9')
			 ) ||
		 !(  (myMaskPtr[3] >= 'a' && myMaskPtr[3] <= 'f')
			 ||(myMaskPtr[3] >= 'A' && myMaskPtr[3] <= 'F')
			 ||(myMaskPtr[3] >= '0' && myMaskPtr[3] <= '9')
			 ) ||
		 !(  (myMaskPtr[4] >= 'a' && myMaskPtr[4] <= 'f')
			 ||(myMaskPtr[4] >= 'A' && myMaskPtr[4] <= 'F')
			 ||(myMaskPtr[4] >= '0' && myMaskPtr[4] <= '9')
			 ) ||
		 !(  (myMaskPtr[5] >= 'a' && myMaskPtr[5] <= 'f')
			 ||(myMaskPtr[5] >= 'A' && myMaskPtr[5] <= 'F')
			 ||(myMaskPtr[5] >= '0' && myMaskPtr[5] <= '9')
			 ) ||
		 !(  (myMaskPtr[6] >= 'a' && myMaskPtr[6] <= 'f')
			 ||(myMaskPtr[6] >= 'A' && myMaskPtr[6] <= 'F')
			 ||(myMaskPtr[6] >= '0' && myMaskPtr[6] <= '9')
			 ) ||
		 !(  (myMaskPtr[7] >= 'A' && myMaskPtr[7] <= 'f')
			 ||(myMaskPtr[7] >= 'A' && myMaskPtr[7] <= 'F')
			 ||(myMaskPtr[7] >= '0' && myMaskPtr[7] <= '9')
			 ) ||
		 !(  (myMaskPtr[8] >= 'a' && myMaskPtr[8] <= 'f')
			 ||(myMaskPtr[8] >= 'A' && myMaskPtr[8] <= 'F')
			 ||(myMaskPtr[8] >= '0' && myMaskPtr[8] <= '9')
			 ) ||
		 !(  (myMaskPtr[9] >= 'a' && myMaskPtr[9] <= 'f')
			 ||(myMaskPtr[9] >= 'A' && myMaskPtr[9] <= 'F')
			 ||(myMaskPtr[9] >= '0' && myMaskPtr[9] <= '9')
			 ) ||
		 ( strlen(myMaskPtr) != 10)
		 )
		{
		  /*doesn't have all 8 hex chars*/
		  fprintf(stderr, "%s: \"%s\" is not a valid subnet mask!\n(Hex values need 8 chars [0-9][a-f][A-F])\n", PACKAGE, myMaskPtr);
		  return(EX_DATAERR);
		}		
		else if( sscanf((char*)(myMaskPtr+2), "%08x", &myMask) != 1)
		{
		  /* hex conversion failed... weird. should not happen*/
		  fprintf(stderr, "%s: Stage two hex parsing failed! Please report this as a bug with the input that caused it.\n", PACKAGE);
		  return(EX_DATAERR);
		}
    }
	else
	{
	

	  /* try to convert the octets for the mask - this also returns 1 if the conversion fails */
	  if(octets_to_u_int(&myMask, myMaskPtr))
		{
		  /*assume CIDR */
		
		  if((strchr(myMaskPtr, '.') != NULL) || sscanf(myMaskPtr, "%" U_INT_32_PRINTF_STRING, &myCIDR) != 1)
			{
			  /* not CIDR */
			  fprintf(stderr, "%s: \"%s\" is not a valid subnet mask or wildcard bit mask!\n", PACKAGE, myMaskPtr);
			  return(EX_DATAERR);
			}
		
		
		  if(myCIDR > 32 )
			{
			  fprintf(stderr, "CIDR netmask notations must be between 0 and 32 bits inclusive!\n");
			  return(EX_DATAERR);	
			}
		  /* Make a mask from the CIDR value */
		  myMask = bitfill_from_left(myCIDR);
		
		}			
	}

	/* check the ip and subnet mask for class A, B, C requirments and warn if inconsistent */
	/*
	validate_class(myIp, myMask);
	*/
	
	/* ip */
	u_int_to_octets(myIp, myIpStr);
	
	/* netmask */
	if( validatemask(myMask) )
	{
		/* This failed but may be Cisco-style */
		/* not it so we can see if it is cisco-style */
		myMask = ~myMask;	
		
		if( validatemask(myMask) )
		{
			/* Now we know it's bad */
			fprintf(stderr, "%s: \"%s\" is not a valid subnet mask or wildcard bit mask!\n", PACKAGE, myMaskPtr);
			return(EX_DATAERR);
		}
	}

	u_int_to_octets(myMask, myMaskStr);
	
	/* Wildcard bits as string */
	u_int_to_octets(~myMask, myWildcardStr);
	
	/* CIDR as a string */
	myCIDR = (unsigned int)bitcount(myMask);
	snprintf(myCIDRStr, BIT_LEN, "%" U_INT_32_PRINTF_STRING, myCIDR );
	
	/* network address */
	myNt = (myIp & myMask);
	u_int_to_octets( myNt, myNtStr);
	
	/* Broadcast address */
	myBr = ( myNt + ~myMask );
	u_int_to_octets(  myBr, myBrStr) ;
	
	/* usable ips */
	usableIps = (myCIDR >30)?0:(myBr - myNt - 1);
	
	if(usableIps <= 0)
	{
		strcpy(myStartIpStr , "<none>");
		strcpy(myEndIpStr , "<none>");
	}
	else
	{
		/* startIp */
		u_int_to_octets( myNt + 1, myStartIpStr);
		
		/* endIp */
		u_int_to_octets( myBr - 1, myEndIpStr);
	}
	
	whatnet_printdata( myMask, myIpStr, myMaskStr, myWildcardStr, myCIDRStr, myNtStr, myBrStr, myStartIpStr, myEndIpStr, usableIps );

	return(0);
}

