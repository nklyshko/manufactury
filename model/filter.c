#include "filter.h"

#define RU_BEGIN 1040
#define RU_END   1103
#define EN_BEGIN 65
#define EN_END   122
#define NUM_BEGIN 48
#define NUM_END   57

bool PositiveNumberFilter(int s) {
    return s >= NUM_BEGIN && s <= NUM_END;
}

bool StringFilter(int s) {
    return (s >= NUM_BEGIN && s <= NUM_END) || (s >= EN_BEGIN && s <= EN_END) || (s >= RU_BEGIN && s <= RU_END) || s == 1025 || s == 1105;
}
