#include <src/log.h>
#include "label.h"

Component* CreateLabel(int x, int y, int size, wchar_t* text) {
    log_debug("Create Label");
    Component* component = CreateComponent();
    InteractivePanel* panelLabel = CreateInteractivePanel(component, x, y, size, 1);

    Label* label = malloc(sizeof(Label));
    label->size = size;
    label->text = malloc(sizeof(wchar_t) * (size + 1));
    log_debug("Label size: %d; Input text: %d", size, wcslen(text));
    wmemcpy_s(label->text, (rsize_t) size, text, (size_t) size);
    label->panelLabel = panelLabel;
    log_debug("LABEL text: %d", wcslen(label->text));
    wmove(panelLabel->window, 0, 0);
    waddwstr(panelLabel->window, label->text);

    component->spec = label;
    component->id = "Label";
    return component;
}
