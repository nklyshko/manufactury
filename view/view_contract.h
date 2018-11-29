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

void ShowProcessing(void);
void HideProcessing(void);
void ShowSaveDialog(); //Show WINAPI save dialog, save request to controller with selected filename
//void ShowError(chtype* error);
//void ShowEditor();
//void setTitle(string s);

#endif //MANUFACTURY_VIEW_CONTRACT_H
