#ifndef MANUFACTURY_MAIN_VIEW_H
#define MANUFACTURY_MAIN_VIEW_H

#include <global.h>
#include <array.h>
#include <model/data_types.h>

void InitMainView(void);
void StartControl(void);
void SetPos(int pos);
void SetData(Array* data);
void ShowStarter(void);
void ShowTable(void);
void ResetActiveColumnLabel(void);
void ShowFileReadError(void);
void ShowFileWriteError(void);
void ShowEntryChanges(Employee* e);

#endif //MANUFACTURY_MAIN_VIEW_H
