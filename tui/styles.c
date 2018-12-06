#include <curses.h>
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
TextAreaStyle* textAreaStyle;
ButtonStyle* yesButtonStyle;
ButtonStyle* noButtonStyle;
ButtonStyle* cancelButtonStyle;

LabelStyle* dataDialogLabelStyle;
EditStyle* dataDialogEditStyle;
SelectStyle* dataDialogSelectStyle;
ButtonStyle* dataDialogButtonStyle;
TextAreaStyle* dataDialogErrorTextStyle;

int mainBackground;
int tableEvenColor;
int tableOddColor;
int tableDisabledColor;
int transitionMenuTable;
int transitionMenuTableDisabled;
int dialogBackground;

void InitStyle(void) {
    evenEditStyle = CreateEditStyle(11, 12, 13);
    oddEditStyle = CreateEditStyle(14, 15, 16);

    menuStyle = CreateMenuStyle(31, 32, 33, 34);

    evenButtonStyle = CreateButtonStyle(41, 42, 43);
    oddButtonStyle = CreateButtonStyle(44, 45, 46);

    evenSelectStyle = CreateSelectStyle(61, 62, 63, 64, 65);
    oddSelectStyle = CreateSelectStyle(67, 62, 63, 64, 65);

    columnLabelStyle = CreateColumnLabelStyle(71, 72, 73, 74);

    tableEvenColor = 81;
    tableOddColor = 82;
    tableDisabledColor = 83;
    mainBackground = 84;
    transitionMenuTable = 85;
    transitionMenuTableDisabled = 86;

    yesButtonStyle = CreateButtonStyle(91, 42, 43);
    noButtonStyle = CreateButtonStyle(92, 42, 43);
    cancelButtonStyle = CreateButtonStyle(93, 42, 43);
    init_pair(91, COLOR_BLACK, COLOR_GREEN_LIGHT);
    init_pair(92, COLOR_BLACK, COLOR_RED_LIGHT);
    init_pair(93, COLOR_BLACK, COLOR_GRAY_LIGHT);

    textAreaStyle = CreateTextAreaStyle(99);
    init_pair(99, COLOR_BLACK, COLOR_GRAY_LIGHT);

    labelStyle = CreateLabelStyle(21);
    init_pair(21, COLOR_BLACK, COLOR_GRAY_LIGHT);

    scrollBarStyle = CreateScrollBarStyle(51);

    dialogBackground = 87;
    init_pair(87, COLOR_BLACK, COLOR_GRAY_DARK);

    dataDialogLabelStyle = CreateLabelStyle(101);
    init_pair(101, COLOR_BLACK, COLOR_GRAY_DARK);

    dataDialogEditStyle = CreateEditStyle(111, 112, 113);
    init_pair(111, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(112, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);
    init_pair(113, COLOR_GRAY_LIGHT, COLOR_BLACK);

    dataDialogSelectStyle = CreateSelectStyle(121, 122, 123, 124, 125);
    init_pair(121, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(122, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);
    init_pair(123, COLOR_GRAY_LIGHT, COLOR_BLACK);
    init_pair(124, COLOR_GRAY_LIGHT, COLOR_BLACK);
    init_pair(125, COLOR_BLACK, COLOR_CYAN_LIGHT);

    dataDialogButtonStyle = CreateButtonStyle(131, 132, 133);
    init_pair(131, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(132, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);
    init_pair(133, COLOR_BLACK, COLOR_CYAN_LIGHT);

    dataDialogErrorTextStyle = CreateTextAreaStyle(141);
    init_pair(141, COLOR_RED_DARK, COLOR_GRAY_LIGHT);

    init_pair(11, COLOR_BLACK, COLOR_WHITE);
    init_pair(12, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);
    init_pair(13, COLOR_WHITE, COLOR_GRAY_DARK);
    init_pair(14, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(15, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);
    init_pair(16, COLOR_WHITE, COLOR_GRAY_DARK);

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

    init_pair(61, COLOR_BLACK, COLOR_WHITE);
    init_pair(62, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);
    init_pair(63, COLOR_WHITE, COLOR_GRAY_DARK);
    init_pair(64, COLOR_BLACK, COLOR_GRAY_DARK);
    init_pair(65, COLOR_BLACK, COLOR_CYAN_LIGHT);
    init_pair(67, COLOR_BLACK, COLOR_GRAY_LIGHT);

    init_pair(71, COLOR_BLACK, COLOR_WHITE);
    init_pair(72, COLOR_BLACK, COLOR_CYAN_LIGHT);
    init_pair(73, COLOR_BLACK, COLOR_GRAY_LIGHT);
    init_pair(74, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);

    init_pair(81, COLOR_GRAY_DARK, COLOR_WHITE);
    init_pair(82, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);
    init_pair(83, COLOR_GRAY_LIGHT, COLOR_WHITE);
    init_pair(84, COLOR_GRAY_DARK, COLOR_WHITE);
    init_pair(85, COLOR_GRAY_DARK, COLOR_GRAY_LIGHT);
    init_pair(86, COLOR_GRAY_LIGHT, COLOR_WHITE);

    init_pair(51, COLOR_BLACK, COLOR_GRAY_LIGHT);
}