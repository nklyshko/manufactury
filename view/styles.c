#include <curses.h>
#include "styles.h"

void InitStyle(void) {
    init_pair(COLOR_MENU, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(COLOR_MENU_ACTIVE, COLOR_BLACK, COLOR_CYAN_LIGHT);
    init_pair(COLOR_MENU_ITEM, COLOR_BLACK, COLOR_GRAY_DARK);
    init_pair(COLOR_MENU_ITEM_ACTIVE, COLOR_BLACK, COLOR_GRAY_DARK);
}