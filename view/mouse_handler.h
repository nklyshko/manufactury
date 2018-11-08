#ifndef MANUFACTURY_MOUSE_HANDLER_H
#define MANUFACTURY_MOUSE_HANDLER_H

#include <global.h>
#include <curses.h>
#include <panel.h>

typedef struct {
    void (* clickInEvent)(PANEL*, MEVENT);
    void* attribute;
} MouseHandler;

void handleEvent(MEVENT event);

#endif //MANUFACTURY_MOUSE_HANDLER_H
