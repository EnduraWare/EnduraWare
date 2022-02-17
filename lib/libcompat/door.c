#include <errno.h>

#include "door.h"

int
door_call(int fd, door_arg_t *arg)
{
	printf("door call on %d with args %p\n", fd, arg);
	return -ENOTSUP;
}