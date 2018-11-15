#include <curses.h>
#include <panel.h>
#include <view/component.h>
#include <view/component/edit.h>
#include <view/component/label.h>
#include "src/log.h"
#include "view/hotkey.h"

void TestS(void) {
    mvaddstr(11, 1, "SAVE   ");
}

void TestC(void) {
    mvaddstr(11, 1, "COPY   ");
}

void TestV(void) {
    mvaddstr(11, 1, "PASTE  ");
}

void EventHandler(HotKey* h) {
    mvprintw(12, 1, "Event: %c %d          ", h->key, h->modifiers);
}

int main() {
    FILE* log = fopen("test.txt", "w");
    log_set_fp(log);

    //инициализация главного окна
    initscr();
    //режим распознавания каждого нажатия клавиши без ожадания Enter
    cbreak();
    //отключение отображения введенного символа
    noecho();
    //отключение курсора
    curs_set(0);
    //неблокирующий ввод
    nodelay(stdscr, TRUE);
    //распознавание функциональных кнопок клавиатуры(F1, ...)
    keypad(stdscr, TRUE);
    //сохранение модификаторов нажатых клавиш при чтении(Ctrl, Alt, Shift, ...)
    PDC_save_key_modifiers(TRUE);
    //поддержка цвета
    start_color();
    //поддержка мыши
    mouse_set(ALL_MOUSE_EVENTS);

    InitHotKeyHandler(EventHandler);

    RegisterHotKeyAction(CreateHotKey('A', KEY_CTRL | KEY_SHIFT), TestS);
    RegisterHotKeyAction(CreateHotKey('C', KEY_CTRL), TestC);
    RegisterHotKeyAction(CreateHotKey('Z', KEY_CTRL), TestV);

//    init_pair(1, COLOR_GREEN, COLOR_YELLOW);
//    WINDOW* w = newwin(3, 3, 4, 4);
//    wbkgd(w, COLOR_PAIR(1) | L't');
//    PANEL* panel = new_panel(w);
//    show_panel(panel);
//    update_panels();

    Component* c = CreateComponent();
    c->id = "main";
    CreateInteractivePanel(c, 0, 0, 80, 24);

    CreateLabel(1, 8, 10, L"Test ёЁ bel");
    CreateEdit(15, 8, 7);

    update_panels();
    doupdate();

    MEVENT event;
    int input = getch();
    while (input != KEY_F(3)) {
        input = getch();
        if (input != ERR) {
            //mvaddstr(11, 1, "          ");
            
            unsigned long modifiers = PDC_get_key_modifiers();
            if (input == KEY_MOUSE) {
                nc_getmouse(&event);
                HandleMouseEvent(event);
//                if (panel_hidden(panel) == OK) {
//                    show_panel(panel);
//                } else {
//                    hide_panel(panel);
//                }
                //log_debug("MOUSE EVENT %d %d", event.y, event.x);
            } else {
                if (!HandleHotKeyEvent(input, modifiers)) {
                    HandleKeyboardEvent(input, modifiers);
                }
            }
            //mvprintw(23, 1, "Key: %d %d             ", input, modifiers);
            //movecurs(panel, 1, 1);
            update_panels();
            doupdate();
        }
    }

    //завершение работы curses
    endwin();
    fclose(log);
}