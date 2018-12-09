#include <model/data_source.h>
#include <tui/dialog.h>
#include <tui/winapi_bridge.h>
#include "report_presenter.h"
#include "report_param_dialog.h"
#include "report_view.h"

#define LINES_COUNT 6
#define COLUMNS_COUNT 4

int** reportData;
wchar_t* report = NULL;

int expGroup(char experience) {
   if (experience > 25) {
       return 5;
   } else {
       return (experience - 1) / 5;
   }
}

void generateReport(wchar_t* param) {
    reportData = malloc(sizeof(int*) * LINES_COUNT);
    report = malloc(sizeof(wchar_t) * (REPORT_HEIGHT * REPORT_WIDTH + 1));
    for (int i = 0; i < LINES_COUNT; i++) {
        reportData[i] = malloc(sizeof(int) * COLUMNS_COUNT);
        memset(reportData[i], 0, sizeof(int) * COLUMNS_COUNT);
    }
    Array* employees = GetEmployees();
    ArrayIter iter;
    array_iter_init(&iter, employees);
    Employee* next;
    while (array_iter_next(&iter, (void**) &next) != CC_ITER_END) {
        if (wcscmp(next->profession, param) == 0) {
            int group = expGroup(next->experience);
            reportData[group][next->class - 1]++;
            reportData[group][3]++;
        }
    }

}

void clearData(void) {
    if (reportData != NULL) {
        for (int i = 0; i < LINES_COUNT; i++) {
            free(reportData[i]);
        }
        free(reportData);
        reportData = NULL;
    }
}

void onParamEntered(wchar_t* param) {
    generateReport(param);
    ShowReport(reportData);
}

void ReportSave(Component* handle) {
    char reportFile[PATH_MAX] = { '\0' };
    if (!ShowSaveReportDialog(reportFile, PATH_MAX)) return;

    FILE* f = fopen(reportFile, "wb");
    if (fprintf(f, "┌───────────┬──────────────────────────────┬─────┐\n"
                   "│           │Количество рабочих по разрядам│     │\n"
                   "│Стаж работы├─────────┬──────────┬─────────┤Всего│\n"
                   "│           │    1    │     2    │    3    │     │\n"
                   "├───────────┼─────────┼──────────┼─────────┼─────┤\n") < 0
     || fprintf(f, "│ До 6      │%9d│%10d│%9d│%5d│\n", reportData[0][0], reportData[0][1], reportData[0][2], reportData[0][3]) < 0
     || fprintf(f, "│ С 6 до 11 │%9d│%10d│%9d│%5d│\n", reportData[1][0], reportData[1][1], reportData[1][2], reportData[1][3]) < 0
     || fprintf(f, "│ С 11 до 16│%9d│%10d│%9d│%5d│\n", reportData[2][0], reportData[2][1], reportData[2][2], reportData[2][3]) < 0
     || fprintf(f, "│ С 16 до 21│%9d│%10d│%9d│%5d│\n", reportData[3][0], reportData[3][1], reportData[3][2], reportData[3][3]) < 0
     || fprintf(f, "│ С 21 до 25│%9d│%10d│%9d│%5d│\n", reportData[4][0], reportData[4][1], reportData[4][2], reportData[4][3]) < 0
     || fprintf(f, "│ Свыше 25  │%9d│%10d│%9d│%5d│\n", reportData[5][0], reportData[5][1], reportData[5][2], reportData[5][3]) < 0
     || fprintf(f, "└───────────┴─────────┴──────────┴─────────┴─────┘\n") < 0
     || fclose(f)) {
        ShowMessageDialog(L"Ошибка сохранения отчета", NULL);
    } else {
        ActivateLayout(NULL);
    }
    clearData();
}

void ReportDelete(Component* handle) {
    ActivateLayout(NULL);
    clearData();
}

void ShowReportDialog(void) {
    ShowReportParamDialog(onParamEntered);
}
