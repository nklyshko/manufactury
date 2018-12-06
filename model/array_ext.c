#include "array_ext.h"

bool array_sorted_contains(Array* a, void* e, int (*comparator)(void* e1, void *e2)) {
    if (array_size(a) == 0) {
        return false;
    } else if (array_size(a) == 1) {
        void* c;
        array_get_last(a, &c);
        return comparator(&e, &c) == 0;
    } else {
        void* left;
        array_get_at(a, 0, &left);
        void* right;
        array_get_last(a, &right);
        int cl, cr;
        if ((cl = comparator(&e, &left)) == 0 || (cr = comparator(&e, &right)) == 0) {
            return true;
        } else if (cl < 0 || cr > 0) {
            return false;
        } else {
            int l = 0;
            int r = (int) (array_size(a) - 1);
            int m = 0;
            void* mid;
            while (r - l > 1) {
                m = (r + l) / 2;
                array_get_at(a, (size_t) m, &mid);
                int c = comparator(&e, &mid);
                if (c == 0) {
                    return true;
                } else if (c < 0) {
                    r = m;
                    right = mid;
                } else {
                    l = m;
                    left = mid;
                }
            }
            if (r == m) {
                return comparator(&e, &left) == 0;
            } else {
                return comparator(&e, &right) == 0;
            }
        }
    }
}

int array_sorted_add(Array* a, void* e, int (* comparator)(void* e1, void* e2), void** replaced) {
    if (array_size(a) == 0) {
        array_add(a, e);
        return 0;
    } else {
        void* left;
        array_get_at(a, 0, &left);
        void* right;
        array_get_last(a, &right);
        if (comparator(&e, &left) < 0) {
            array_add_at(a, e, 0);
            return 0;
        } else if (comparator(&e, &right) > 0) {
            array_add(a, e);
            return (int) (array_size(a) - 1);
        } else {
            int l = 0;
            int r = (int) (array_size(a) - 1);
            int m = 0;
            void* mid;
            while (r - l > 1) {
                m = (r + l) / 2;
                array_get_at(a, (size_t) m, &mid);
                int c = comparator(&e, &mid);
                if (c == 0) {
                    array_replace_at(a, e, (size_t) m, replaced);
                    return m;
                } else if (c < 0) {
                    r = m;
                    right = mid;
                } else {
                    l = m;
                    left = mid;
                }
            }
            if (r == m) {
                if (comparator(&e, &left) == 0) {
                    array_replace_at(a, e, (size_t) l, replaced);
                    return l;
                }
            } else {
                if (comparator(&e, &right) == 0) {
                    array_replace_at(a, e, (size_t) r, replaced);
                    return r;
                }
            }
            array_add_at(a, e, (size_t) r);
            return r;
        }
    }
}

void array_remove_single(Array* a, void* e, int (* comparator)(void* e1, void* e2)) {
    ArrayIter iter;
    array_iter_init(&iter, a);
    void* next;
    while(array_iter_next(&iter, &next) != CC_ITER_END) {
        if (comparator(&e, &next) == 0) {
            array_iter_remove(&iter, NULL);
            break;
        }
    }
}
