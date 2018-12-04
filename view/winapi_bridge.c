#include "winapi_bridge.h"
#include <windows.h>
#include <curses.h>
#include <src/log.h>

void ShowMessage(wchar_t* message) {
    MessageBoxW(0, message, L"Сообщение", 1);
}

bool ShowOpenFileDialog(char* fileName, int maxLength) {
    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Manufactury Files\0*.mnf\0All files\0*.*\0\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = (DWORD) maxLength;
    ofn.lpstrTitle = "Open file";
    ofn.Flags = OFN_NONETWORKBUTTON |
                OFN_FILEMUSTEXIST |
                OFN_HIDEREADONLY;
    if (!GetOpenFileName(&ofn)) {
        return false;
    }
    return true;
}

bool ShowSaveFileDialog(char* fileName, int maxLength) {
    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Manufactury Files\0*.mnf\0All files\0*.*\0\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = (DWORD) maxLength;
    ofn.lpstrTitle = "Save file";
    ofn.lpstrDefExt = "mnf";
    ofn.Flags = OFN_NONETWORKBUTTON |
                OFN_FILEMUSTEXIST |
                OFN_HIDEREADONLY;
    if (GetSaveFileName(&ofn)) return true;
    return false;
}