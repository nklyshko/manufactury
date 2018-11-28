#include "data_types.h"

bool valueOfGender(wchar_t* str) {
    return str[0] != L'Ж';
}

ProfClass valueOfProfClass(wchar_t* str) {
    switch (str[0]) {
        case L'1':
            return FIRST;
        case L'2':
            return SECOND;
        case L'3':
            return THIRD;
        default:
            return FIRST;
    }
}
