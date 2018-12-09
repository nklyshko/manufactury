#ifndef MANUFACTURY_REPORT_PARAM_DIALOG_H
#define MANUFACTURY_REPORT_PARAM_DIALOG_H

#include <tui/layout.h>
#include <tui/styles.h>

void InitReportParamDialog(int color);

void ShowReportParamDialog(void (* onConfirm)(wchar_t* param));


#endif //MANUFACTURY_REPORT_PARAM_DIALOG_H
