#include <stdio.h>
#include <curses.h>
#include <panel.h>
#include <src/log.h>
#include "global.h"
#include "model_contract.h"
#include "view/view_contract.h"
#include "presenter_contract.h"

#define LOG_FILE "log.txt"

int main() {
    FILE* log = fopen(LOG_FILE, "a");
    log_set_fp(log);
    InitView();
    fclose(log);
//    initscr();
//    cbreak();
//    noecho();
//    nodelay(stdscr, TRUE);
//    mouse_on(ALL_MOUSE_EVENTS);
//    keypad(stdscr, TRUE);
//    PDC_save_key_modifiers(true);
//    resize_term(25, 100);
//    PANEL* main = new_panel(stdscr);
//    mvprintw(4, 5, "gabfshbfhbsahbds");
//    WINDOW* w = newwin(3, 50, 3, 3);
//    PANEL* pan = new_panel(w);
//    mvwprintw(w, 1, 2, "Test ||||||||||||||⬆   %d", KEY_RESIZE);
//    bool visible = true;
//    update_panels();
//    doupdate();
//    int c = 0;
//    while (c != 'q') {
//        c = getch();
//        if (c == ERR)
//            continue;
//        unsigned long m = PDC_get_key_modifiers();
//        mvprintw(20, 1, "%d         %d   ", c, m);
//        if (c == KEY_F(3)) {
//            mvprintw(0, 0, "%d", visible);
//            if (visible) {
//                hide_panel(pan);
//                visible = false;
//            } else {
//                show_panel(pan);
//                visible = true;
//            }
//            touchwin(stdscr);
//            update_panels();
//            doupdate();
//        }
//    }
}