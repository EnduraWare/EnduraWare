/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*
 * The door lightweight RPC I/F.
 */


#ifndef DOOR_H_
#define DOOR_H_

#include <sys/types.h>

#include "creds.h"

typedef unsigned int	uint_t;

/* Attributes originally obtained from door_create operation */
#define	DOOR_UNREF	0x01	/* Deliver an unref notification with door */
#define	DOOR_REFUSE_DESC 0x40	/* Do not accept descriptors from callers */

/* Attributes (additional) returned with door_info and door_desc_t data */
#define	DOOR_LOCAL	0x04	/* Descriptor is local to current process */

#define	DOOR_INVAL -1			/* An invalid door descriptor */
#define	DOOR_UNREF_DATA ((void *)1)	/* Unreferenced invocation address */

/* Attributes used to describe door_desc_t data */
#define	DOOR_DESCRIPTOR	0x10000	/* A file descriptor is being passed */
#define	DOOR_RELEASE	0x40000	/* Passed references are also released */

typedef unsigned long long door_id_t;	/* Unique door identifier */
typedef	unsigned int	   door_attr_t;	/* Door attributes */

typedef struct door_desc {
	door_attr_t	d_attributes;	/* Tag for union */
	union {
		/* File descriptor is passed */
		struct {
			int		d_descriptor;
			door_id_t	d_id;		/* unique id */
		} d_desc;
		/* Reserved space */
		int		d_resv[5];
	} d_data;
} door_desc_t;

/*
 * Structure used to pass/return data from door_call
 *
 * All fields are in/out paramters. Upon return these fields
 * are updated to reflect the true location and size of the results.
 */
typedef struct door_arg {
	char		*data_ptr;	/* Argument/result data */
	size_t		data_size;	/* Argument/result data size */
	door_desc_t	*desc_ptr;	/* Argument/result descriptors */
	uint_t		desc_num;	/* Argument/result num discriptors */
	char		*rbuf;		/* Result area */
	size_t		rsize;		/* Result size */
} door_arg_t;


typedef void door_server_procedure_t(void *, char *, size_t, door_desc_t *,
    uint_t);

int	door_call(int, door_arg_t *);
int	door_return(char *, size_t, door_desc_t *, uint_t);
int	door_ucred(ucred_t **);

#endif /* DOOR_H_ */
