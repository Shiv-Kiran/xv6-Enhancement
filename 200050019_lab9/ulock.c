#include "ulock.h"
#include "x86.h"
#include "defs.h"

void init_lock(struct lock_t *s)
{
    s->locked = 0;
}

void acquire_lock(struct lock_t *s)
{
    /* Your Code */
    // pushcli();
    while (xchg(&s->locked, 1) != 0)
    {
    }
    // cprintf("Locked acquired \n");
    // __sync_synchronize();
}

void release_lock(struct lock_t *s)
{
    /* Your Code */

    // __sync_synchronize();

    asm volatile("movl $0, %0"
                 : "+m"(s->locked)
                 :);
    // cprintf("Locked released \n");

    // popcli();
}

void init_sem(struct sem_t *s, int initval)
{
    /* Your Code */
    s->value = initval;
    init_lock(&s->lk);
}

void up_sem(struct sem_t *s) // signal or post
{
    /* Your Code */
    // int decrement = s->value-1;
    // cprintf("Trying to up the lock %d \n", (s->lk).locked);
    acquire_lock(&s->lk);
    s->value++;
    // cprintf("value of s->value = %d \n", s->value);
    signal_sem(&s->lk);
    release_lock(&s->lk);
    // cprintf("Upped the semaphore \n");
}

void down_sem(struct sem_t *s) // wait
{
    /* Your Code */
    acquire_lock(&s->lk);
    // cprintf("Acquired Lock\n");
    // cprintf("%d\n", s->value);
    // cprintf("Checking for lock %d \n", (&s->lk)->locked);

    if (s->value > 0)
    {
        s->value--;
    }
    else
    {
        // cprintf("%d\n", s->value);
        while (s->value <= 0)
        {
            // cprintf("Blocking semaphores with value %d and lock %d \n", s->value, s->lk.locked);
            block_sem(&s->lk);
        }
        // s->value--;
    }
    release_lock(&s->lk);
}
