/* Should we not print headers? */
#undef NO_PRINT_HEADER

/* Should we not support locales for number formatting? */
#undef NO_LOCALE_SUPPORT

@TOP@

@BOTTOM@

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

