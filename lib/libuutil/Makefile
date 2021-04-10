#
# Use base mk files to generate libraries (DragonFly and FreeBSD)
#

LIB=		uutil
SHLIB_MAJOR=	1
SRCS=		avl.c \
		uu_alloc.c \
		uu_avl.c \
		uu_dprintf.c \
		uu_ident.c \
		uu_list.c \
		uu_misc.c \
		uu_open.c \
		uu_pname.c \
		uu_string.c \
		uu_strtoint.c

CFLAGS+=	-I${.CURDIR}

VERSION_DEF=	${.CURDIR}/Versions.def
SYMBOL_MAPS=	${.CURDIR}/mapfile-vers

NOPROFILE=	yes
NO_PROFILE=	yes

.PATH:		${.CURDIR}/avl

.include <bsd.lib.mk>
