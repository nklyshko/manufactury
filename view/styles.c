#include <curses.h>
#include "styles.h"

EditStyle* editStyle;
LabelStyle* labelStyle;
MenuStyle* menuStyle;
ButtonStyle* buttonStyle;

void InitStyle(void) {
    editStyle = CreateEditStyle(11, 12);
    labelStyle = CreateLabelStyle(21);
    menuStyle = CreateMenuStyle(31, 32, 33, 34);
    buttonStyle = CreateButtonStyle(41, 42, 43);
    init_pair(11, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(12, COLOR_WHITE, COLOR_GRAY_DARK);

    init_pair(21, COLOR_BLACK, COLOR_WHITE);

    init_pair(31, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(32, COLOR_BLACK, COLOR_CYAN_LIGHT);
    init_pair(33, COLOR_BLACK, COLOR_GRAY_DARK);
    init_pair(34, COLOR_BLACK, COLOR_CYAN_LIGHT);

    init_pair(41, COLOR_BLACK, COLOR_GRAY_DARK);
    init_pair(42, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(43, COLOR_BLACK, COLOR_CYAN_LIGHT);
}