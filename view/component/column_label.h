#ifndef MANUFACTURY_COLUMN_LABEL_H
#define MANUFACTURY_COLUMN_LABEL_H

#include <view/interactive_panel.h>

typedef struct ColumnLabel ColumnLabel;
typedef struct ColumnLabelStyle ColumnLabelStyle;
typedef enum SortDirection SortDirection;

enum SortDirection { NONE, ASC, DSC};

struct ColumnLabel {
    ColumnLabelStyle* style;
    int size;
    SortDirection activeDirection;
    wchar_t* text;
    InteractivePanel* panel;
    void (* OnDirectionChange)(void);
};

struct ColumnLabelStyle {
    int defaultColor;
    int focusedColor;
    int activeColor;
};

Component* CreateColumnLabel(ColumnLabelStyle* style, int x, int y, int size, wchar_t* text);

ColumnLabelStyle* CreateColumnLabelStyle(int defaultColor, int focusedColor, int activeColor);

#endif //MANUFACTURY_COLUMN_LABEL_H
