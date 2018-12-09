#ifndef MANUFACTURY_REPORT_VIEW_H
#define MANUFACTURY_REPORT_VIEW_H

#include <curses.h>

#define REPORT_WIDTH 50
#define REPORT_HEIGHT 14

void InitReportView(int color);

WINDOW* GetReportWindow(void);

void ShowReport(int** reportData);

#endif //MANUFACTURY_REPORT_VIEW_H
