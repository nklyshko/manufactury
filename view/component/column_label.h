#ifndef MANUFACTURY_COLUMN_LABEL_H
#define MANUFACTURY_COLUMN_LABEL_H

#include <view/interactive_panel.h>

typedef struct ColumnLabel ColumnLabel;
typedef struct ColumnLabelStyle ColumnLabelStyle;
typedef enum SortDirection SortDirection;

enum SortDirection { NONE, ASC, DSC};

struct ColumnLabel {
    ColumnLabelStyle* style;
    bool enabled;
    int size;
    SortDirection activeDirection;
    wchar_t* text;
    InteractivePanel* panel;
    void (* OnDirectionChange)(Component* handle);
};

struct ColumnLabelStyle {
    int defaultColor;
    int focusedColor;
    int activeColor;
    int disabledColor;
};

Component* CreateColumnLabel(ColumnLabelStyle* style, int x, int y, int size, wchar_t* text);

void ColumnLabelSetEnabled(Component* handle, bool enabled);

void ColumnLabelSetDirection(Component* handle, SortDirection direction);

ColumnLabelStyle* CreateColumnLabelStyle(int defaultColor, int focusedColor, int activeColor, int disabledColor);

#endif //MANUFACTURY_COLUMN_LABEL_H
