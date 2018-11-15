#ifndef MANUFACTURY_COMPONENT_H
#define MANUFACTURY_COMPONENT_H

#include <panel.h>

typedef struct Component Component;

struct Component {
    void* spec;
    char* id;
    void (* OnKeyClick)(Component* handle, int key, unsigned long modifiers);
    void (* OnFocusGet)(Component* handle);
    //возвращает true, если происходит перефокусировка внутри компонента, иначе false и фокус переходит на следующий Component
    bool (* OnFocusChange)(Component* handle);
    void (* OnFocusLost)(Component* handle);
};

Component* CreateComponent();

void HandleMouseEvent(MEVENT event);

void HandleKeyboardEvent(int key, unsigned long modifiers);

#endif //MANUFACTURY_COMPONENT_H
