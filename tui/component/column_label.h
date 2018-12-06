#ifndef MANUFACTURY_COLUMN_LABEL_H
#define MANUFACTURY_COLUMN_LABEL_H

#include <model/data_types.h>
#include <model/comparator.h>
#include <tui/interactive_panel.h>

typedef struct ColumnLabel ColumnLabel;
typedef struct ColumnLabelStyle ColumnLabelStyle;

struct ColumnLabel {
    ColumnLabelStyle* style;
    bool enabled;
    int size;
    int fieldId;
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

Component* CreateColumnLabel(ColumnLabelStyle* style, int x, int y, int size, int fieldId, wchar_t* text);

void ColumnLabelSetEnabled(Component* handle, bool enabled);

void ColumnLabelSetDirection(Component* handle, SortDirection direction);

ColumnLabelStyle* CreateColumnLabelStyle(int defaultColor, int focusedColor, int activeColor, int disabledColor);

#endif //MANUFACTURY_COLUMN_LABEL_H
