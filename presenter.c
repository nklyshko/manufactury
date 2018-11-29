#include <model/data_types.h>
#include <src/log.h>
#include "presenter_contract.h"
#include "model_contract.h"
#include "view/view_contract.h"

#define TESTS 23

Array* sorted;
int pos = 0;
int pageSize = 23;
Comparator* sortComparator = NULL;
SortDirection sortDirection = NONE;

void InitApplication(char* param) {
    if (param == NULL) {
        ShowStarter();
    }
}

void FileOpen(void) {
    array_new(&sorted);
    for (int i = 0; i < TESTS; i++) {
        Employee* e = malloc(sizeof(Employee));
        e->id = i;
        e->surname[0] = '\0';
        e->name[0] = '\0';
        e->patronymic[0] = '\0';
        e->profession[0] = '\0';
        e->salary = i * 1000;
        e->departmentId = i * 5;
        e->plotId = i * 5;
        e->experience = (short) (i * 10);
        array_add(sorted, e);
    }
    ShowTable();
    SetData(sorted);
}

void TableOnScrollDown(ScrollType scrollType) {
    int step = 1;
    if (scrollType == PAGE) {
        step = pageSize;
    }
    if (pos == array_size(sorted) - 1) return;
    if (pos + step > array_size(sorted) - 1) {
        pos = (int) (array_size(sorted) - 1);
    } else {
        pos += step;
    }
    SetPos(pos);
}

void TableOnScrollUp(ScrollType scrollType) {
    int step = 1;
    if (scrollType == PAGE) {
        step = pageSize;
    }
    if (pos == 0) return;
    if (pos - step < 0) {
        pos = 0;
    } else {
        pos -= step;
    }
    SetPos(pos);
}

void SortData(Comparator* comparator, SortDirection direction) {
    if (direction == NONE) return;
    log_debug("SIZE %d", array_size(sorted));
    if (sortComparator == comparator) {
        if (sortDirection != direction) {
            log_debug("REVERSE ONLY");
            sortDirection = direction;
            array_reverse(sorted);
            pos = 0;
            SetPos(0);
        }
    } else {
        log_debug("SORTING");
        sortComparator = comparator;
        sortDirection = direction;
        if (sortDirection == ASC) {
            array_sort(sorted, (int (*)(const void*, const void*)) sortComparator->compare);
        } else {
            array_sort(sorted, (int (*)(const void*, const void*)) sortComparator->compareReversed);
        }
        pos = 0;
        SetPos(0);
    }
}
