/* 
    main.c, Copyright (C) 2001-2003 Joe Laffey     
    Main for Whatmask 

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


#include "whatnet.h"
#include "usage.h"

#include "main.h"

#if __dest_os == __mac_os
int main(void)
#else
int main(int argc, char** argv)
#endif
{
	
	uint32 val1;
	char	*inStrPtr;
	int		retVal;
	char*	slashPos;

#if __dest_os == __mac_os
	char	inStr[256];
	char	line[256];
#endif
	
#ifdef HAVE_LOCALE_H
	if ( !setlocale(LC_NUMERIC, "") )
	{
    	fprintf(stderr, "* %s: WARNING: Unable to set locale to default locale!\n* Please check your LANG and/or LC_NUMERIC environment variables.\n* US users set LC_NUMERIC to 'en_US'\n* Or, you may want to recompile without local support.\n", PACKAGE);
		/* return(EX_SOFTWARE); */
		if ( !setlocale(LC_NUMERIC, "C") )
		{	
			fprintf(stderr, "%s: Unable to set locale to default  'C' locale! \nYou may want to recompile without local support.\n", PACKAGE);
			return(EX_SOFTWARE);
		}
	}
#endif
	
	
#if __dest_os == __mac_os
	char	inStr[256];
	char	line[256];
	
	inStrPtr = inStr; 
	
	printf("%s v%s, Copyright (C) 2001-2003 Joe Laffey <joe@laffeycomputer.com>\n", PACKAGE, VERSION);
	printf("Visit: http://www.laffeycomputer.com/software.html for updates.\n\n");

	printf("%s comes with ABSOLUTELY NO WARRANTY; for details see the COPYING file\nthat accompained this distribution. ", PACKAGE);
	printf("This is free software, and you are welcome\nto redistribute it");
	printf(" under the terms of GNU PUBLIC LICENSE.\n");
	
	usage();
	printf("\n");
	
	/* Loop for ever for Mac OS Classic because there is no command line */
	while(1)
	{
	
	printf("\nEnter the netmask or ip/netmask: ");
	fgets(line, 255, stdin);
	if(sscanf(line,"%255s", inStrPtr) != 1)
	{
		usage();
		continue;
	}

#else

	
	if(argc < 2 || argc > 3)
		return(usage());
		
	inStrPtr = argv[1];


#endif
	
	
		
	
	
	
#if __dest_os != __mac_os
	if(argc == 3)
	{
		/* if argv[2] starts with a slash '/' we skip it */
		retVal = whatnet_main(argv[1], ((argv[2][0] == '/')?argv[2]+1:argv[2]) );
	}
	else 
	{
#endif

		if(inStrPtr[0] == '/') /* drop a leading slash */
		inStrPtr += 1;
		
		slashPos = strchr(inStrPtr, '/');
		if(slashPos != NULL )
		{
			/* This is an ip/netmask combo to be processed as net info */
			
			/* assume the input is ip/mask */
			
			slashPos[0] = '\0'; /* terminate the ip string by putting a null in place of the slash */
			
			retVal = whatnet_main(inStrPtr, slashPos + 1);
		}
		else
		{
		
			if( 	   (inStrPtr[0] == '0') 
				&& (inStrPtr[1]=='x' || inStrPtr[1]=='X') 
			  )
			{
				
				if(
					!(  (inStrPtr[2] >= 'a' && inStrPtr[2] <= 'f')
						 ||(inStrPtr[2] >= 'A' && inStrPtr[2] <= 'F')
						 ||(inStrPtr[2] >= '0' && inStrPtr[2] <= '9')
						 ) ||
					 !(  (inStrPtr[3] >= 'a' && inStrPtr[3] <= 'f')
						 ||(inStrPtr[3] >= 'A' && inStrPtr[3] <= 'F')
						 ||(inStrPtr[3] >= '0' && inStrPtr[3] <= '9')
						 ) ||
					 !(  (inStrPtr[4] >= 'a' && inStrPtr[4] <= 'f')
						 ||(inStrPtr[4] >= 'A' && inStrPtr[4] <= 'F')
						 ||(inStrPtr[4] >= '0' && inStrPtr[4] <= '9')
						 ) ||
					 !(  (inStrPtr[5] >= 'a' && inStrPtr[5] <= 'f')
						 ||(inStrPtr[5] >= 'A' && inStrPtr[5] <= 'F')
						 ||(inStrPtr[5] >= '0' && inStrPtr[5] <= '9')
						 ) ||
					 !(  (inStrPtr[6] >= 'a' && inStrPtr[6] <= 'f')
						 ||(inStrPtr[6] >= 'A' && inStrPtr[6] <= 'F')
						 ||(inStrPtr[6] >= '0' && inStrPtr[6] <= '9')
						 ) ||
					 !(  (inStrPtr[7] >= 'A' && inStrPtr[7] <= 'f')
						 ||(inStrPtr[7] >= 'A' && inStrPtr[7] <= 'F')
						 ||(inStrPtr[7] >= '0' && inStrPtr[7] <= '9')
						 ) ||
					 !(  (inStrPtr[8] >= 'a' && inStrPtr[8] <= 'f')
						 ||(inStrPtr[8] >= 'A' && inStrPtr[8] <= 'F')
						 ||(inStrPtr[8] >= '0' && inStrPtr[8] <= '9')
						 ) ||
					 !(  (inStrPtr[9] >= 'a' && inStrPtr[9] <= 'f')
						 ||(inStrPtr[9] >= 'A' && inStrPtr[9] <= 'F')
						 ||(inStrPtr[9] >= '0' && inStrPtr[9] <= '9')
						 ) ||
				   ( strlen(inStrPtr) != 10)
				)
				{
					/*doesn't have all 8 hex chars*/
					fprintf(stderr, "%s: \"%s\" is not a valid subnet mask!\n(Hex values need 8 chars [0-9][a-f][A-F])\n", PACKAGE, inStrPtr);
					retVal = EX_DATAERR;
	
				}		
				else if( sscanf((char*)(inStrPtr+2), "%08x", &val1) == 1)
				{
					/* hex conversion succeeded so we have a netmask */
					retVal =  nmtoc_main(inStrPtr,val1);
				}
			}
			else
			{
			/* try to convert the octets - this also returns 1 if the conversion fails */
			if(octets_to_u_int(&val1, inStrPtr))
			{
				/*assume CIDR */
				if((strchr(inStrPtr, '.') != NULL) || sscanf(inStrPtr, "%" U_INT_32_PRINTF_STRING, &val1) != 1)
				{
					/* not CIDR */
					fprintf(stderr, "%s: \"%s\" is not a valid subnet mask or wildcard bit mask!\n", PACKAGE, inStrPtr);
					retVal = EX_DATAERR;
				}
				else
				{	
					/*try CIDR */
					retVal =  ctonm_main(val1);
				}
			}
			else 
			{
				/* octet conversion succeeded so we have a netmask */
				retVal =  nmtoc_main(inStrPtr,val1);
			}
			}
		}
	
	
	} /**** */ 	/* This closing brace is double purpose! */
				/* It serves as the close for the else of if(argc == 3) and also as the */
				/* end of while(1) loop forever for Mac OS classic */


	return(retVal);
}

