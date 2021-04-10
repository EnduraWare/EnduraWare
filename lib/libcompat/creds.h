#ifndef CREDS_H_
#define CREDS_H_

#include <sys/types.h>

typedef struct {
    uid_t uid;
    gid_t gid;
    pid_t pid;
} ucred_t;

#endif