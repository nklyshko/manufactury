#ifndef MANUFACTURY_HOTKEY_H
#define MANUFACTURY_HOTKEY_H

#include <curses.h>

#define HOTKEY_OFFSET 0x40

#define KEY_CTRL PDC_KEY_MODIFIER_CONTROL
#define KEY_SHIFT PDC_KEY_MODIFIER_SHIFT
#define KEY_ALT PDC_KEY_MODIFIER_ALT

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
