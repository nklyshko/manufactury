#include <model/data_types.h>
#include <src/log.h>
#include <view/winapi_bridge.h>
#include <model/data_source.h>
#include <view/dialog.h>
#include <view/data_dialog.h>
#include <model/array_ext.h>
#include "presenter_contract.h"
#include "model_contract.h"
#include "view/view_contract.h"

#define TESTS 400

Array* sorted = NULL;
int pos = 0;
int pageSize = 23;
Comparator* sortComparator = NULL;
SortDirection sortDirection = NONE;

/*
 * true - Работа с данными, сохраненными в существующий файл
 * false - Работа с данными, не сохраненными ни в какой файл
 * */
bool currentOpened = false;

char currentFileName[PATH_MAX] = { '\0' };
bool currentChanged = false;

void updateData(Array* data) {
    if (data == NULL) {
        if (sorted != NULL) {
            array_remove_all_free(sorted);
            array_destroy(sorted);
            sorted = NULL;
            ShowStarter();
        }
    } else {
        if (sorted == NULL) {
            ShowTable();
        }
        array_copy_shallow(data, &sorted);
        SetData(sorted);
    }
}

void setCurrentFile(char* fileName) {
    currentChanged = false;
    if (fileName == NULL) {
        currentOpened = false;
    } else {
        currentOpened = true;
        strcpy(currentFileName, fileName);
    }
}

void newFile(void) {
    setCurrentFile(NULL);
    WipeData();
    updateData(GetEmployees());
}

void InitApplication(char* param) {
    InitDataSource();
    currentFileName[0] = '\0';
    if (param == NULL) {
        ShowStarter();
    }
}

void newSaveChanges(void) {
    if (currentOpened) {
        if (WriteFile(currentFileName)) {
            newFile();
        } else {
            ShowFileWriteError();
        }
    } else {
        char fileName[PATH_MAX] = { '\0' };
        if (ShowSaveFileDialog(fileName, PATH_MAX)) {
            setCurrentFile(fileName);
            if (WriteFile(currentFileName)) {
                newFile();
            } else {
                ShowFileWriteError();
            }
        }
    }
}

void newDiscardChanges(void) {
    newFile();
}

void openSaveChanges(void) {
    char fileName[PATH_MAX] = { '\0' };
    if (currentOpened) {
        if (WriteFile(currentFileName)) {
            if (ShowSaveFileDialog(fileName, PATH_MAX)) {
                if (WriteFile(fileName)) {
                    setCurrentFile(fileName);
                } else {
                    ShowFileWriteError();
                }
            }
        } else {
            ShowFileWriteError();
        }
    } else {
        if (ShowSaveFileDialog(fileName, PATH_MAX)) {
            if (WriteFile(fileName)) {
                setCurrentFile(fileName);
                if (ShowOpenFileDialog(fileName, PATH_MAX)) {
                    if (ReadFile(fileName)) {
                        setCurrentFile(fileName);
                    } else {
                        ShowFileWriteError();
                    }
                }
            } else {
                ShowFileWriteError();
            }
        }
    }

}

void openDiscardChanges(void) {
    char fileName[PATH_MAX] = { '\0' };
    if (ShowOpenFileDialog(fileName, PATH_MAX)) {
        if (ReadFile(fileName)) {
            setCurrentFile(fileName);
            updateData(GetEmployees());
        } else {
            ShowFileReadError();
        }
    }
}

void FileNew(void) {
    if (currentChanged) {
        ShowConfirmationDialog(L"Сохранить изменения в открытом файле?", newSaveChanges, newDiscardChanges, NULL);//newSaveChanges, newDiscardChanges
    } else {
        newFile();
    }
}

void FileOpen(void) {
    if (currentChanged) {
        ShowConfirmationDialog(L"Сохранить изменения в открытом файле?", openSaveChanges, openDiscardChanges, NULL); //openSaveChanges, openDiscardChanges
    } else {
        char fileName[PATH_MAX] = { '\0' };
        if (ShowOpenFileDialog(fileName, PATH_MAX)) {
            if (ReadFile(fileName)) {
                setCurrentFile(fileName);
                updateData(GetEmployees());
            } else {
                ShowFileReadError();
            }
        }
    }
}

void FileSave(void) {
    if (currentChanged) {
        if (currentOpened) {
            WriteFile(currentFileName);
            currentChanged = false;
        } else {
            char fileName[PATH_MAX] = {'\0'};
            if (ShowSaveFileDialog(fileName, PATH_MAX)) {
                if (WriteFile(fileName)) {
                    setCurrentFile(fileName);
                } else {
                    ShowFileWriteError();
                }
            }
        }
    }
}

void FileSaveAs(void) {
    char fileName[PATH_MAX] = { '\0' };
    if (ShowSaveFileDialog(fileName, PATH_MAX)) { //Имя для файла выбрано
        if (currentOpened) {
            if (strcmp(currentFileName, fileName) == 0) { //Выбран тот же файл
                if (WriteFile(currentFileName)) {
                    currentChanged = false;
                } else {
                    ShowFileWriteError();
                }
            } else { //Выбран другой файл
                if (WriteFile(fileName)) {
                    setCurrentFile(fileName);
                } else {
                    ShowFileWriteError();
                }
            }
        } else {
            if (WriteFile(currentFileName)) {
                setCurrentFile(fileName);
            } else {
                ShowFileWriteError();
            }
        }
    }
}

void newEmployee(void) {
    currentChanged = true;
    Employee* e = GetEnteredData();
    if (EmployeeIdExists(e)) {
        //TODO: показать ошибку в диалоге добавления(т.е. не закрывать диалог автоматически по нажатию ОК)
    } else {
        AddEmployee(e);
        int updated = 0;
        if (sortComparator == NULL) {
            updated = array_sorted_add(sorted, e, (int (*)(void*, void*)) EmployeeIdComparator);
        } else {
            if (sortDirection == ASC) {
                updated = array_sorted_add(sorted, e, (int (*)(void*, void*)) sortComparator->compare);
            } else {
                updated = array_sorted_add(sorted, e, (int (*)(void*, void*)) sortComparator->compareReversed);
            }
        };
        if (updated >= pos && updated < pos + pageSize) {
            SetPos(pos);
        }
    }
}

void EditAdd(void) {
    if (sorted == NULL) return;
    ShowAddDialog(newEmployee, NULL);
}

void ToolsExportCSV(void) {

}

void TableOnScrollDown(ScrollType scrollType) {
    if (sorted == NULL) return;
    int step = 1;
    if (scrollType == PAGE) {
        step = pageSize;
    }
    if (pos == array_size(sorted) - 1) return;
    if (pos + step > array_size(sorted) - 1) {
        pos = (int) (array_size(sorted) - 1);
    } else {
        pos += step;
    }
    SetPos(pos);
}

void TableOnScrollUp(ScrollType scrollType) {
    if (sorted == NULL) return;
    int step = 1;
    if (scrollType == PAGE) {
        step = pageSize;
    }
    if (pos == 0) return;
    if (pos - step < 0) {
        pos = 0;
    } else {
        pos -= step;
    }
    SetPos(pos);
}

void SortData(Comparator* comparator, SortDirection direction) {
    if (sorted == NULL) return;
    if (direction == NONE) return;
    if (sortComparator == comparator) { //признак сортировки не изменился
        if (sortDirection != direction) { //сортировка не требуется, дотстаочно перевернуть массив
            sortDirection = direction;
            array_reverse(sorted);
            pos = 0;
            SetPos(0);
        }
    } else { //признак сортировки изменился, требуется сортировка
        sortComparator = comparator;
        sortDirection = direction;
        if (sortDirection == ASC) {
            array_sort(sorted, (int (*)(const void*, const void*)) sortComparator->compare);
        } else {
            array_sort(sorted, (int (*)(const void*, const void*)) sortComparator->compareReversed);
        }
        pos = 0;
        SetPos(0);
    }
}
