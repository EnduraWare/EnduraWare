#ifndef THREADS_H_
#define THREADS_H_

#include <sys/time.h>

#define MUTEX_HELD(mtx) (mtx != NULL)

typedef long long hrtime_t;

hrtime_t gethrtime(void);
hrtime_t gethrvtime(void);

#endif /* THREADS_H_ */
