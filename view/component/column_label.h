#ifndef MANUFACTURY_COLUMN_LABEL_H
#define MANUFACTURY_COLUMN_LABEL_H

#include <view/interactive_panel.h>
#include <model/data_types.h>
#include <model/comparator.h>

typedef struct ColumnLabel ColumnLabel;
typedef struct ColumnLabelStyle ColumnLabelStyle;

struct ColumnLabel {
    ColumnLabelStyle* style;
    bool enabled;
    int size;
    SortDirection activeDirection;
    wchar_t* text;
    InteractivePanel* panel;
    Comparator* comparator;
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
