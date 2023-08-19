#include "types.h"

struct lock_t
{
    uint locked;
};

struct sem_t
{
    int value;
    struct lock_t lk;
};
