#include "array_ext.h"

int array_add_sorted(Array* a, void* e, int (* comparator)(void*, void*)) {
    if (array_size(a) == 0) {
        array_add(a, e);
    } else {
        void* left;
        array_get_at(a, 0, &left);
        void* right;
        array_get_last(a, &right);
        if (comparator(e, left) < 0) {
            array_add_at(a, e, 0);
        } else if (comparator(e, right) > 0) {
            array_add(a, e);
        } else {
            int l = 0;
            int r = (int) (array_size(a) - 1);
            int m;
            void* mid;
            while (r - l > 1) {
                m = (r + l) / 2;
                array_get_at(a, (size_t) m, &mid);
                int c = comparator(e, mid);
                if (c == 0) {
                    array_add_at(a, e, (size_t) m);
                    return m;
                } else if (c < 0) {
                    r = m;
                    right = mid;
                } else {
                    l = m;
                    left = mid;
                }
            }
            array_add_at(a, e, (size_t) r);
            return r;
        }
    }
}
