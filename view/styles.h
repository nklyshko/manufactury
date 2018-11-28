#ifndef MANUFACTURY_STYLES_H
#define MANUFACTURY_STYLES_H

#include <view/component/edit.h>
#include <view/component/label.h>
#include <view/component/menu.h>
#include <view/component/button.h>
#include <view/component/scroll_bar.h>
#include <view/component/select.h>
#include <view/component/column_label.h>

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

extern MenuStyle* menuStyle;
extern EditStyle* evenEditStyle;
extern EditStyle* oddEditStyle;
extern ButtonStyle* evenButtonStyle;
extern ButtonStyle* oddButtonStyle;
extern SelectStyle* evenSelectStyle;
extern SelectStyle* oddSelectStyle;
extern ColumnLabelStyle* columnLabelStyle;

extern int mainBackground;
extern int tableEvenColor;
extern int tableOddColor;
extern int tableDisabledColor;
extern int transitionMenuTable;
extern int transitionMenuTableDisabled;

extern LabelStyle* labelStyle;
extern ScrollBarStyle* scrollBarStyle;


void InitStyle(void);

#endif //MANUFACTURY_STYLES_H
