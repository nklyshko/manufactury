#include <src/log.h>
#include "scroll_bar.h"

int divUp(int a, int b) {
    int r = a / b;
    if (a % b != 0) r++;
    return r;
}

void ScrollBarOnMouseClick(InteractivePanel* handle, MEVENT event) {
    ScrollBar* scrollBar = handle->holder->spec;
    if (event.y == 0) {
        scrollBar->layout->OnScrollUp(SINGLE);
    } else if (event.y == scrollBar->size - 1) {
        scrollBar->layout->OnScrollDown(SINGLE);
    }
}

void ScrollBarShow(Component* handle) {
    ScrollBar* scrollBar = handle->spec;
    wbkgd(scrollBar->panel->window, COLOR_PAIR(scrollBar->style->color));
    PanelShow(scrollBar->panel);
}

void ScrollBarHide(Component* handle) {
    ScrollBar* scrollBar = handle->spec;
    PanelHide(scrollBar->panel);
}

Component* CreateScrollBar(ScrollBarStyle* style, int x, int y, int height, Layout* layout) {
    Component* handle = CreateComponent();
    ScrollBar* scrollBar = malloc(sizeof(ScrollBar));
    scrollBar->style = style;
    scrollBar->layout = layout;
    scrollBar->height = height;
    scrollBar->size = 1;
    scrollBar->pos = 0;
    scrollBar->thumb = height - 2;
    scrollBar->count = 1;

    InteractivePanel* panel = CreateInteractivePanel(handle, x, y, 1, height);
    WINDOW* w = panel->window;
    wbkgd(w, COLOR_PAIR(style->color));
    waddch(w, L'▲');
    for (int i = 1; i < scrollBar->height; i++) {
        waddch(w, ACS_CKBOARD);
    }
    waddch(w, L'▼');
    panel->OnMouseClick = ScrollBarOnMouseClick;
    scrollBar->panel = panel;

    handle->id = malloc(sizeof(char) * 10);
    handle->id[10] = '\0';
    sprintf(handle->id, "%s %d", "Scroll", GetNextId());

    handle->spec = scrollBar;
    handle->Show = ScrollBarShow;
    handle->Hide = ScrollBarHide;
    return handle;
}

void ScrollBarSetNumber(Component* handle, int number) {
    ScrollBar* scrollBar = handle->spec;
    if (number > scrollBar->count) return;
    scrollBar->number = number; //абсолютный номер элемента
    WINDOW* w = scrollBar->panel->window;
    wmove(w, scrollBar->pos + 1, 0);
    for (int i = 0; i < scrollBar->thumb; i++) {
        waddch(w, ACS_CKBOARD);
    }
    scrollBar->pos = scrollBar->number / scrollBar->step; //позиция ползунка
    wmove(w, scrollBar->pos + 1, 0);
    for (int i = 0; i < scrollBar->thumb; i++) {
        waddch(w, ACS_BLOCK);
    }
}

void ScrollBarSetCount(Component* handle, int count) {
    ScrollBar* scrollBar = handle->spec;
    scrollBar->count = count;
    int pages = divUp(scrollBar->count, scrollBar->height);
    if (pages >= scrollBar->height - 2) {
        scrollBar->size = scrollBar->height - 2;
    } else if (pages == 0) {
        scrollBar->size = 1;
    } else {
        scrollBar->size = pages;
    }
    scrollBar->thumb = (scrollBar->height - 2) - scrollBar->size + 1;
    scrollBar->step = scrollBar->count / scrollBar->size;
}

ScrollBarStyle* CreateScrollBarStyle(int color) {
    ScrollBarStyle* style = malloc(sizeof(ScrollBarStyle));
    style->color = color;
    return style;
}
