#ifndef MANUFACTURY_MAIN_VIEW_H
#define MANUFACTURY_MAIN_VIEW_H

#include <global.h>
#include <array.h>

void InitMainView(void);
void StartControl(void);
void SetPos(int pos);
void SetData(Array* data);
void ShowStarter(void);
void ShowTable(void);
void ResetActiveColumnLabel(void);
void ShowFileReadError(void);
void ShowFileWriteError(void);

#endif //MANUFACTURY_MAIN_VIEW_H
