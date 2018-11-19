#ifndef MANUFACTURY_HOTKEY_H
#define MANUFACTURY_HOTKEY_H

#include <curses.h>

#define HOTKEY_OFFSET 0x40

typedef struct HotKey HotKey;

struct HotKey {
    int key;
    unsigned long modifiers;
};

bool InitHotKeyHandler(void (* eventHandler)(HotKey* hotKey));

HotKey* CreateHotKey(char symbol, unsigned long modifiers);

wchar_t* GetHotKeyTitle(HotKey* hotKey);

void RegisterHotKeyAction(HotKey* hotKey, void (* action)(void));

bool HandleHotKeyEvent(int key, unsigned long modifiers);

#endif //MANUFACTURY_HOTKEY_H
