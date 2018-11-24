#include <curses.h>
#include <view/component/column_label.h>
#include "styles.h"

EditStyle* evenEditStyle;
EditStyle* oddEditStyle;
ButtonStyle* evenButtonStyle;
ButtonStyle* oddButtonStyle;
SelectStyle* evenSelectStyle;
SelectStyle* oddSelectStyle;

LabelStyle* labelStyle;
MenuStyle* menuStyle;
ScrollBarStyle* scrollBarStyle;
ColumnLabelStyle* columnLabelStyle;

void InitStyle(void) {
    evenEditStyle = CreateEditStyle(11, 12, 13);
    oddEditStyle = CreateEditStyle(14, 15, 16);

    evenButtonStyle = CreateButtonStyle(41, 42, 43);
    oddButtonStyle = CreateButtonStyle(44, 45, 46);

    evenSelectStyle = CreateSelectStyle(61, 62, 63, 64, 65);
    oddSelectStyle = CreateSelectStyle(67, 62, 63, 64, 65);

    labelStyle = CreateLabelStyle(21);
    menuStyle = CreateMenuStyle(31, 32, 33, 34);

    scrollBarStyle = CreateScrollBarStyle(51);

    columnLabelStyle = CreateColumnLabelStyle(71, 72, 73);
    init_pair(11, COLOR_BLACK, COLOR_WHITE);
    init_pair(12, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);
    init_pair(13, COLOR_WHITE, COLOR_GRAY_DARK);
    init_pair(14, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(15, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);
    init_pair(16, COLOR_WHITE, COLOR_GRAY_DARK);

    init_pair(21, COLOR_BLACK, COLOR_WHITE);

    init_pair(31, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(32, COLOR_BLACK, COLOR_CYAN_LIGHT);
    init_pair(33, COLOR_BLACK, COLOR_GRAY_DARK);
    init_pair(34, COLOR_BLACK, COLOR_CYAN_LIGHT);

    init_pair(41, COLOR_BLACK, COLOR_WHITE);
    init_pair(42, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(43, COLOR_BLACK, COLOR_CYAN_LIGHT);
    init_pair(44, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(45, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(46, COLOR_BLACK, COLOR_CYAN_LIGHT);

    init_pair(51, COLOR_BLACK, COLOR_WHITE);

    init_pair(61, COLOR_BLACK, COLOR_WHITE);
    init_pair(62, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);
    init_pair(63, COLOR_WHITE, COLOR_GRAY_DARK);
    init_pair(64, COLOR_BLACK, COLOR_GRAY_DARK);
    init_pair(65, COLOR_BLACK, COLOR_CYAN_LIGHT);
    init_pair(67, COLOR_BLACK, COLOR_GRAY_LIGHT);


    init_pair(71, COLOR_BLACK, COLOR_WHITE);
    init_pair(72, COLOR_BLACK, COLOR_CYAN_LIGHT);
    init_pair(73, COLOR_BLACK, COLOR_GRAY_LIGHT);
}