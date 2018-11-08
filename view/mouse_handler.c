#include <src/log.h>
#include "mouse_handler.h"

void handleEvent(MEVENT event) {
    int mouseX = event.x;
    int mouseY = event.y;
    PANEL* panel = stack_top_panel();
    if (panel == NULL) return;

    while (panel != NULL) {
        WINDOW* w = panel_window(panel);
        int y = getbegy(w);
        int x = getbegx(w);
        int height = getmaxy(w);
        int width = getmaxx(w);
        //log_debug("handleEvent %d <= %d < %d  &&  %d <= %d < %d");
        if (mouseY >= y && mouseX >= x &&  mouseY < y + height && mouseX < x + width) {
            event.y = mouseY - y;
            event.x = mouseX - x;
            break;
        } else {
            panel = panel_below(panel);
        }
    }
    MouseHandler* handler = (MouseHandler*) panel_userptr(panel);
    if (handler != NULL) {
        handler->clickInEvent(panel, event);
    }
}
