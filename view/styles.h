#ifndef MANUFACTURY_STYLES_H
#define MANUFACTURY_STYLES_H

#include <view/component/edit.h>
#include <view/component/label.h>
#include <view/component/menu.h>
#include <view/component/button.h>
#include <view/component/scroll_bar.h>

#define TERMINAL_WIDTH 128
#define TERMINAL_HEIGHT 32

#undef COLOR_WHITE
#define COLOR_WHITE 15
#define COLOR_YELLOW_LIGHT 14
#define COLOR_PINK_LIGHT 13
#define COLOR_RED_LIGHT 12
#define COLOR_CYAN_LIGHT 11
#define COLOR_GREEN_LIGHT 10
#define COLOR_BLUE_LIGHT 9
#define COLOR_GRAY_DARK 8
#define COLOR_GRAY_LIGHT 7
#define COLOR_YELLOW_DARK 6
#define COLOR_PINK_DARK 5
#define COLOR_RED_DARK 4
#define COLOR_CYAN_DARK 3
#define COLOR_GREEN_DARK 2
#define COLOR_BLUE_DARK 1

#define COLOR_MENU 4
#define COLOR_MENU_ACTIVE 5
#define COLOR_MENU_ITEM 6
#define COLOR_MENU_ITEM_ACTIVE 7
#define COLOR_TEST_2 254
#define COLOR_TEST_1 255


extern EditStyle* editStyle;
extern LabelStyle* labelStyle;
extern MenuStyle* menuStyle;
extern ButtonStyle* buttonStyle;
extern ScrollBarStyle* scrollBarStyle;

void InitStyle(void);

#endif //MANUFACTURY_STYLES_H
