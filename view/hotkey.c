#include <curses.h>
#include <src/log.h>
#include "hotkey.h"

HotKey CreateHotKey(char symbol, unsigned long modifiers) {
    HotKey h;
    h.key = (int) symbol - HOTKEY_OFFSET;
    h.modifiers = modifiers;
    wchar_t t = L'N';
    return h;
}

bool TestHotKey(HotKey h, int ch, unsigned long modifiers) {
    return h.key == ch && h.modifiers == modifiers;
}

wchar_t* GetHotKeyTitle(HotKey h) {
    const int bufSize = 13;
    wchar_t* result = malloc(sizeof(wchar_t) * bufSize);

    //промежуточный буфер
    wchar_t buf[bufSize];

    buf[0] = (wchar_t) (h.key + HOTKEY_OFFSET);
    buf[1] = '\0';

    if (h.modifiers & KEY_SHIFT) {
        swprintf(result, bufSize, L"%s+%s", L"↑", buf);
        wcscpy(buf, result);
    }
    if (h.modifiers & KEY_ALT) {
        swprintf(result, bufSize, L"%s+%s", L"Alt", buf);
        wcscpy(buf, result);
    }
    if (h.modifiers & KEY_CTRL) {
        swprintf(result, bufSize, L"%s+%s", L"Ctrl", buf);
    }
    return result;
}
