#include <tui/layout.h>
#include <tui/component/label.h>
#include <tui/styles.h>
#include "report_view.h"
#include "report_presenter.h"

#define EXP_COL_LABEL_ID 0
#define COUNT_COL_LABEL_ID 1
#define SUM_COL_LABEL_ID 2
#define C1_COL_LABEL_ID 3
#define C2_COL_LABEL_ID 4
#define C3_COL_LABEL_ID 5

Layout* reportTable;
Component* dataLabels[6][4];



void InitReportView(int color) {
    int x = (COLS - REPORT_WIDTH) / 2;
    int y = (LINES - REPORT_HEIGHT) / 2;
    reportTable = CreateLayout(x, y, REPORT_WIDTH, REPORT_HEIGHT);
    WINDOW* w = reportTable->window;
    wbkgd(w, COLOR_PAIR(color));
    mvwaddwstr(w, 0, 0, L"┌───────────┬──────────────────────────────┬─────┐"
                         "│           │Количество рабочих по разрядам│     │"
                         "│Стаж работы├─────────┬──────────┬─────────┤Всего│"
                         "│           │    1    │     2    │    3    │     │"
                         "├───────────┼─────────┼──────────┼─────────┼─────┤"
                         "│ До 6      │         │          │         │     │"
                         "│ С 6 до 11 │         │          │         │     │"
                         "│ С 11 до 16│         │          │         │     │"
                         "│ С 16 до 21│         │          │         │     │"
                         "│ С 21 до 25│         │          │         │     │"
                         "│ Свыше 25  │         │          │         │     │"
                         "└───────────┴─────────┴──────────┴─────────┴─────┘");

    for (int l = 0 ; l < 6;l++) {
        dataLabels[l][0] = CreateLabel(dataDialogLabelStyle, x + 13, y + 5 + l, 9, L"");
        dataLabels[l][1] = CreateLabel(dataDialogLabelStyle, x + 13 + 10, y + 5 + l, 10, L"");
        dataLabels[l][2] = CreateLabel(dataDialogLabelStyle, x + 13 + 10 + 11, y + 5 + l, 9, L"");
        dataLabels[l][3] = CreateLabel(dataDialogLabelStyle, x + 13 + 10 + 11 + 10, y + 5 + l, 5, L"");
        for (int c = 0; c < 4; c++) {
            LayoutAddComponent(reportTable, dataLabels[l][c]);
        }
    }

    Component* saveButton = CreateButton(dataDialogButtonStyle, x + 2, y + REPORT_HEIGHT - 2, 11, L" Сохранить ", ReportSave);
    LayoutAddComponent(reportTable, saveButton);
    Component* deleteButton = CreateButton(dataDialogButtonStyle, x + REPORT_WIDTH - 13, y + REPORT_HEIGHT - 2, 11, L"  Удалить  ", ReportDelete);
    LayoutAddComponent(reportTable, deleteButton);
}


void ShowReport(int** reportData) {
    for (int l = 0; l < 6; l++) {
        wchar_t s[5];
        swprintf(s, 5, L"%d", reportData[l][0]);
        LabelSetText(dataLabels[l][0], s);
        swprintf(s, 5, L"%d", reportData[l][1]);
        LabelSetText(dataLabels[l][1], s);
        swprintf(s, 5, L"%d", reportData[l][2]);
        LabelSetText(dataLabels[l][2], s);
        swprintf(s, 5, L"%d", reportData[l][3]);
        LabelSetText(dataLabels[l][3], s);
    }
    ActivateLayout(reportTable);
}