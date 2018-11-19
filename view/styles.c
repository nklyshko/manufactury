#include <curses.h>
#include "styles.h"

EditStyle* editStyle;
LabelStyle* labelStyle;
MenuStyle* menuStyle;

void InitStyle(void) {
    editStyle = CreateEditStyle(11, 12);
    labelStyle = CreateLabelStyle(23);
    menuStyle = CreateMenuStyle(34, 35, 36, 37);
    init_pair(11, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(12, COLOR_WHITE, COLOR_GRAY_DARK);

    init_pair(23, COLOR_BLACK, COLOR_WHITE);

    init_pair(34, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(35, COLOR_BLACK, COLOR_CYAN_LIGHT);
    init_pair(36, COLOR_BLACK, COLOR_GRAY_DARK);
    init_pair(37, COLOR_BLACK, COLOR_CYAN_LIGHT);
}