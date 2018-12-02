#include "textarea.h"


void TextAreaShow(Component* handle) {
    TextArea* textArea = handle->spec;
    wbkgd(textArea->panel->window, COLOR_PAIR(textArea->style->color));
    PanelShow(textArea->panel);
}

void TextAreaHide(Component* handle) {
    TextArea* textArea = handle->spec;
    PanelHide(textArea->panel);
}

bool TextAreaOnFocusGet(Component* handle) {
    return false;
}

Component* CreateTextArea(TextAreaStyle* style, int x, int y, int width, int height) {
    Component* handle = CreateComponent();
    TextArea* textArea = malloc(sizeof(TextArea));
    textArea->style = style;
    textArea->width = width;
    textArea->height = height;
    textArea->size = height * width;
    textArea->text = malloc(sizeof(wchar_t) * textArea->size);

    InteractivePanel* panelTextArea = CreateInteractivePanel(handle, x, y, width, height);
    textArea->panel = panelTextArea;

    handle->id = malloc(sizeof(char) * 10);
    handle->id[10] = '\0';
    sprintf(handle->id, "%s %d", "TextArea", GetNextId());

    handle->spec = textArea;
    handle->Show = TextAreaShow;
    handle->Hide = TextAreaHide;
    handle->OnFocusGet = TextAreaOnFocusGet;
    return handle;
}

void TextAreaSetContent(Component* handle, wchar_t* text) {
    TextArea* textArea = handle->spec;
    WINDOW* w = textArea->panel->window;
    wmemcpy_s(textArea->text, (size_t) textArea->size, text, (size_t) textArea->size); //wcscpy_s не работает
    wchar_t* word = malloc(sizeof(char) * textArea->size);
    wmemset(word, L'\0', (size_t) textArea->size);
    int len = (int) wcslen(text);
    int pos = 0;

    int line = 0;
    int lineLen = 0;

    int wordLen = 0;
    wclear(w);
    wmove(w, 0, 0);
    while (len) {
        if (pos >= len) {
            if (lineLen != 0) {
                waddch(w, ' ');
                lineLen++;
            }
            waddwstr(w, word);
            lineLen += wordLen;
            int offset = (textArea->width - lineLen) / 2;
            wmove(w, line, 0);
            for (int i = 0; i < offset; i++) {
                winsch(w, ' ');
            }
            break;
        }
        if (text[pos] == L' ') {
            if (lineLen != 0) {
                waddch(w, ' ');
                lineLen++;
            }
            waddwstr(w, word);
            lineLen += wordLen;
            wmemset(word, L'\0', (size_t) textArea->size);
            wordLen = 0;
        } else {
            if (lineLen + wordLen >= textArea->width) {
                int offset = (textArea->width - (lineLen - wordLen)) / 2;
                wmove(w, line, 0);
                for (int i = 0; i < offset; i++) {
                    winsch(w, ' ');
                }
                lineLen = 0;
                line++;
                if (line >= textArea->height) break;
                wmove(w, line, 0);
            }
            word[wordLen] = text[pos];
            wordLen++;
        }
        pos++;
    }
    free(word);
}

TextAreaStyle* CreateTextAreaStyle(int color) {
    TextAreaStyle* style = malloc(sizeof(TextAreaStyle));
    style->color = color;
    return style;
}