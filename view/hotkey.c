#include <list.h>
#include <curses.h>
#include <src/log.h>
#include "hotkey.h"

#define A_CODE 0x01 //первая буква в алфавите
#define Z_CODE 0x1a //последняя буква в алфавите

typedef struct HotKeyAction HotKeyAction;

struct HotKeyAction{
    HotKey* hotKey;
    void (* action)(void);
};

List* registeredHotKeys;
void (* hotKeyEventHandler)(HotKey* hotKey);

bool InitHotKeyHandler(void (* eventHandler)(HotKey* hotKey)) {
    hotKeyEventHandler = eventHandler;
    if (list_new(&registeredHotKeys) == CC_ERR_ALLOC) {
        return FALSE;
    }
    return TRUE;
}

HotKey* CreateHotKey(char symbol, unsigned long modifiers) {
    HotKey* hotKey = malloc(sizeof(HotKey));
    hotKey->key = (int) symbol - HOTKEY_OFFSET;
    hotKey->modifiers = modifiers;
    return hotKey;
}

bool TestHotKey(HotKey* hotKey, int ch, unsigned long modifiers) {
    return hotKey->key == ch && hotKey->modifiers == modifiers;
}

wchar_t* GetHotKeyTitle(HotKey* hotKey) {
    const int bufSize = 13;
    wchar_t* result = malloc(sizeof(wchar_t) * bufSize);

    //промежуточный буфер
    wchar_t buf[bufSize];

    buf[0] = (wchar_t) (hotKey->key + HOTKEY_OFFSET);
    buf[1] = '\0';

    if (hotKey->modifiers & KEY_SHIFT) {
        swprintf(result, bufSize, L"%s+%s", L"↑", buf);
        wcscpy(buf, result);
    }
    if (hotKey->modifiers & KEY_ALT) {
        swprintf(result, bufSize, L"%s+%s", L"Alt", buf);
        wcscpy(buf, result);
    }
    if (hotKey->modifiers & KEY_CTRL) {
        swprintf(result, bufSize, L"%s+%s", L"Ctrl", buf);
    }
    return result;
}

void RegisterHotKeyAction(HotKey* hotKey, void (* action)(void)) {
    HotKeyAction* hotKeyAction = malloc(sizeof(HotKeyAction));
    hotKeyAction->hotKey = hotKey;
    hotKeyAction->action = action;
    list_add(registeredHotKeys, hotKeyAction);
}

bool HandleHotKeyEvent(int key, unsigned long modifiers) {
    if (key < A_CODE || key > Z_CODE) return FALSE;
    ListIter li;
    list_iter_init(&li, registeredHotKeys);
    HotKeyAction* hotKeyAction;
    while (list_iter_next(&li, (void**) &hotKeyAction) != CC_ITER_END) {
        HotKey* hotKey = hotKeyAction->hotKey;
        if (hotKey->key == key && hotKey->modifiers == modifiers) {
            hotKeyAction->action();
            hotKeyEventHandler(hotKey);
            return TRUE;
        }
    }
    return FALSE;
}