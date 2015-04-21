/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */
/* Should we not print headers? */
/* #undef NO_PRINT_HEADER */

/* Should we not support locales for number formatting? */
/* #undef NO_LOCALE_SUPPORT */


/* Define to `unsigned' if <sys/types.h> doesn't define.  */
/* #undef size_t */

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* The number of bytes in a unsigned int.  */
#define SIZEOF_UNSIGNED_INT 4

/* The number of bytes in a unsigned long.  */
#define SIZEOF_UNSIGNED_LONG 8

/* The number of bytes in a unsigned short.  */
#define SIZEOF_UNSIGNED_SHORT 2

/* Define if you have the <locale.h> header file.  */
#define HAVE_LOCALE_H 1

/* Name of package */
#define PACKAGE "whatmask"

/* Version number of package */
#define VERSION "1.2"


/*  Find the proper type for 32 bits  */
#if SIZEOF_UNSIGNED_SHORT == 4
typedef unsigned short uint32;
#define U_INT_32_PRINTF_STRING	"hu"
#elif SIZEOF_UNSIGNED_INT == 4
typedef unsigned int uint32;
#define U_INT_32_PRINTF_STRING	"u"
#elif SIZEOF_UNSIGNED_LONG == 4
typedef unsigned long uint32;
#define U_INT_32_PRINTF_STRING	"lu"
#else
#error No 32 bit type
#endif

/* locale stuff */
#ifndef NO_LOCALE_SUPPORT

#ifdef HAVE_LOCALE_H
/* This will put a quote character in front of the numeric printf */
/* format string to use the built-in thousands grouping. If your */
/* printf does not support this then undef this or HAVE_LOCALE_H above */
#define U_INT_32_NUMERIC_PRINTF_STRING "'"
#else
#define U_INT_32_NUMERIC_PRINTF_STRING ""
#endif
#else
#define U_INT_32_NUMERIC_PRINTF_STRING ""
#endif

