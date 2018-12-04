#ifndef MANUFACTURY_VIEW_CONTRACT_H
#define MANUFACTURY_VIEW_CONTRACT_H

#include <global.h>
#include <array.h>

void InitView(void);
void DestroyView(void);
void StartControl(void);
void SetPos(int pos);
void SetData(Array* data);
void ShowStarter(void);
void ShowTable(void);
void ResetActiveColumnLabel(void);
void ShowFileReadError(void);
void ShowFileWriteError(void);

#endif //MANUFACTURY_VIEW_CONTRACT_H
