#ifndef COMPAT_H_
#define COMPAT_H_

#include <sys/types.h>

#define __NORETURN

/* sys/time.h compat */
#define	SEC		1
#define	MILLISEC	1000
#define	MICROSEC	1000000
#define	NANOSEC		1000000000LL

#ifndef Have_strlcpy
size_t strlcat(char *dst, const char *src, size_t dsize);
size_t strlcpy(char *dst, const char *src, size_t dsize);
#endif

#endif