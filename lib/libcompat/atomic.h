#ifndef ATOMIC_H_
#define ATOMIC_H_

#define atomic_add_32_nv(ptr, val) __sync_add_and_fetch(ptr, val)
#define atomic_add_32(ptr, val) ((void)atomic_add_32_nv(ptr, val))
#define atomic_inc_uint(ptr) __sync_fetch_and_add(ptr, 1)

#endif /* ATOMIC_H_ */
