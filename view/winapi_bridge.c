#include "winapi_bridge.h"
#include <windows.h>

void ShowMessage(wchar_t* message) {
    MessageBoxW(0, message, L"Сообщение", 1);
}