/*
    main.h, Copyright (C) 2001-2003 Joe Laffey
    Main header for Whatmask

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


#ifndef MAIN_H
#define MAIN_H


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "ctonm.h"

int usage(void);


#ifndef __dest_os
#define __dest_os	6969
#endif


#if __dest_os == __mac_os
int main(void);
#else
int main(int, char**);
#endif

#ifdef NO_LOCALE_SUPPORT
#undef HAVE_LOCALE_H
#endif

#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif

#endif
