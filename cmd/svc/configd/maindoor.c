/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
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
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#pragma ident	"%Z%%M%	%I%	%E% SMI"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>

#include "door.h"
#include "creds.h"

#include "repcache_protocol.h"
#include "configd.h"

#define	INVALID_RESULT		((uint32_t)-1U)

static int		main_door_fd = -1;

/*ARGSUSED*/
static void*
main_switcher(void *v)
{
	thread_info_t *ti = (thread_info_t*)v;

	thread_setup(ti);

	while (true) {
		int fd;

		thread_newstate(ti, TI_DOOR_RETURN);
		fd = accept(main_door_fd, NULL, NULL);
		thread_newstate(ti, TI_MAIN_DOOR_CALL);

		if (fd == -1) {
			backend_fini();
			exit(CONFIGD_EXIT_LOST_MAIN_DOOR);
		}

		create_connection(fd);
	}
}

int
setup_main_door(const char *doorpath)
{
	mode_t oldmask;
	struct sockaddr_un sun;
	int ret;

	/*
	 * Create the file if it doesn't exist.  Ignore errors, since
	 * fattach(3C) will catch any real problems.
	 */
	oldmask = umask(000);		/* disable umask temporarily */

	main_door_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (main_door_fd == -1){
		perror("socket");
		return (0);
	}

	memset(&sun, 0, sizeof(struct sockaddr_un));
	sun.sun_family = AF_UNIX;
	strncpy(sun.sun_path, doorpath, sizeof(sun.sun_path) - 1);

	ret = bind(main_door_fd, (const struct sockaddr *)&sun,
	    sizeof(struct sockaddr_un));
	if (ret == -1) {
		perror("bind");
		return (0);
	}

	ret = listen(main_door_fd, 20);
	if (ret == -1) {
		perror("listen");
		return (0);
	}

	(void)umask(oldmask);

	if(new_thread_needed(main_switcher, NULL) == NULL)
		return 0;

	return (1);
}
