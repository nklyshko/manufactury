#include <curses.h>
#include "src/log.h"
#include "view/hotkey.h"

void TestS(void) {
    mvaddstr(3, 1, "SAVE   ");
}

void TestC(void) {
    mvaddstr(3, 1, "COPY   ");
}

void TestV(void) {
    mvaddstr(3, 1, "PASTE  ");
}

void EventHandler(HotKey* h) {
    mvprintw(5, 1, "Event: %c %d          ", h->key, h->modifiers);
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

    MEVENT event;
    move(0 ,0);
    int input = ERR;
    while (input != KEY_F(3)) {
        input = getch();
        if (input != ERR) {

            mvaddstr(5, 1, "                ");

            if (input == KEY_MOUSE) {
                nc_getmouse(&event);
                //log_debug("MOUSE EVENT %d %d", event.y, event.x);
            } else {
                if (!HandleKeyClick(input, PDC_get_key_modifiers())) {
                    mvprintw(7, 1, "Key: %d %d             ", input, PDC_get_key_modifiers());
                }
            }
            move(0, 0);
            doupdate();
        }
    }

    //завершение работы curses
    endwin();
    fclose(log);
}