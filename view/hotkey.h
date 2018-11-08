#ifndef MANUFACTURY_HOTKEY_H
#define MANUFACTURY_HOTKEY_H

#include <global.h>

#define HOTKEY_OFFSET 0x40

#define KEY_CTRL PDC_KEY_MODIFIER_CONTROL
#define KEY_SHIFT PDC_KEY_MODIFIER_SHIFT
#define KEY_ALT PDC_KEY_MODIFIER_ALT

typedef struct {
    int key;
    unsigned long modifiers;
} HotKey;

HotKey CreateHotKey(char symbol, unsigned long modifiers);

bool TestHotKey(HotKey h, int ch, unsigned long modifiers);

wchar_t* GetHotKeyTitle(HotKey h);

#endif //MANUFACTURY_HOTKEY_H
