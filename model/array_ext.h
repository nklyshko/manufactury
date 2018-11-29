#ifndef MANUFACTURY_ARRAY_EXT_H
#define MANUFACTURY_ARRAY_EXT_H

#include <array.h>
#include <list.h>
#include <src/log.h>

int array_add_sorted(Array* a, void* e, int (* comparator)(void* e1, void* e2));

#endif //MANUFACTURY_ARRAY_EXT_H
