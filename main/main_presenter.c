#include <model/data_types.h>
#include <src/log.h>
#include <model/data_source.h>
#include <edit/edit_view.h>
#include <model/array_ext.h>
#include <tui/winapi_bridge.h>
#include <tui/dialog.h>
#include <edit/edit_presenter.h>
#include <tui/component/edit.h>
#include <tui/component/select.h>
#include <minmax.h>
#include <tui/component/button.h>
#include <edit/id_input_dialog.h>
#include <report/report_presenter.h>
#include <model/predicate.h>
#include "main_presenter.h"
#include "main_view.h"
#include "filter_dialog.h"

Array* sorted = NULL;
int pos = 0;
int pageSize = 23;
int sortField = 0;
SortDirection sortDirection = ASC;
Comparator* comparators[FIELDS_COUNT];

/*
 * true - Работа с данными, сохраненными в существующий файл
 * false - Работа с данными, не сохраненными ни в какой файл
 * */
bool currentOpened = false;

char currentFileName[PATH_MAX] = { '\0' };
bool currentChanged = false;
bool needSorting = false;

int (* predicates[FIELDS_COUNT]) (void* value, void* e);
void* predicateParameter = NULL;
int (* predicate)(void* value, void* e);

void updateData(Array* data) {
    if (data == NULL) {
        if (sorted != NULL) {
            array_destroy(sorted);
            sorted = NULL;
            ShowStarter();
        }
    } else {
        if (sorted == NULL) {
            ShowTable();
        } else {
            array_destroy(sorted);
            sorted = NULL;
        }
        array_copy_shallow(data, &sorted);
        sortField = 0;
        SetData(sorted);
        ResetActiveColumnLabel();
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

void deleteEntry(Employee* e) {
    currentChanged = true;
    RemoveEmployee(e);
    size_t removePos = 0;
    array_index_of(sorted, e, &removePos);
    array_remove(sorted, e, NULL);
    if (removePos >= pos && removePos < pos + pageSize) {
        SetPos(pos);
    }
}

void deleteById(int id) {
    Employee* e = GetEmployee(id);
    if (e == NULL) {
        ShowMessageDialog(L"Работник с таким табельным номером не найден", NULL);
    } else {
        deleteEntry(e);
    }
}

void changeById(int id) {
    Employee* e = GetEmployee(id);
    if (e == NULL) {
        ShowMessageDialog(L"Работник с таким табельным номером не найден", NULL);
    } else {
        ShowChangeDialog(e);
    }
}

bool filterData(const void* e) {
    return predicate(predicateParameter, (void*) e) == 0;
}

void filterAll(int fieldId, wchar_t* value) {
    bool mem = false;
    bool filter = true;
    switch (fieldId) {
        case FIELD_ID:
        case FIELD_YOB:
        case FIELD_EXPERIENCE:
        case FIELD_DEPARTMENT:
        case FIELD_PLOT:
        case FIELD_SALARY:
            predicateParameter = malloc(sizeof(int));
            mem = true;
            *((int*) predicateParameter) = parseInt(value);
            if (*((int*) predicateParameter) == -1) {
                 filter = false;
            }
            break;
        case FIELD_GENDER:
            predicateParameter = malloc(sizeof(bool));
            mem = true;
            switch (value[0]) {
                case L'М':
                    *((bool*) predicateParameter) = true;
                    break;
                case L'Ж':
                    *((bool*) predicateParameter) = false;
                    break;
                default:
                    filter = false;
                    break;
            }
            break;
        case FIELD_CLASS:
            predicateParameter = malloc(sizeof(ProfClass));
            mem = true;
            switch (value[0]) {
                case L'1':
                    *((ProfClass*) predicateParameter) = FIRST;
                    break;
                case L'2':
                    *((ProfClass*) predicateParameter) = SECOND;
                    break;
                case L'3':
                    *((ProfClass*) predicateParameter) = THIRD;
                    break;
                default:
                    filter = false;
                    break;
            }
            break;
        default:
            predicateParameter = value;
            break;
    }
    if (filter) {
        predicate = predicates[fieldId];
        Array* filtered;
        array_copy_shallow(GetEmployees(), &filtered);
        array_filter_mut(filtered, filterData);
        if (array_size(filtered) == 0) {
            ShowFilterError();
        } else {
            updateData(filtered);
        }
    } else {
        ShowFilterError();
    }
    if (mem) {
        free(predicateParameter);
        predicateParameter = NULL;
    }
}

void InitApplication(char* param) {
    comparators[FIELD_ID] = CreateComparator(EmployeeIdComparator, EmployeeIdComparatorReversed);
    comparators[FIELD_SURNAME] = CreateComparator(EmployeeSurnameComparator, EmployeeSurnameComparatorReversed);
    comparators[FIELD_NAME] = CreateComparator(EmployeeNameComparator, EmployeeNameComparatorReversed);
    comparators[FIELD_PATRONYMIC] = CreateComparator(EmployeePatronymicComparator, EmployeePatronymicComparatorReversed);
    comparators[FIELD_YOB] = CreateComparator(EmployeeYOBComparator, EmployeeYOBComparatorReversed);
    comparators[FIELD_GENDER] = CreateComparator(EmployeeGenderComparator, EmployeeGenderComparatorReversed);
    comparators[FIELD_PROFESSION] = CreateComparator(EmployeeProfessionComparator, EmployeeProfessionComparatorReversed);
    comparators[FIELD_EXPERIENCE] = CreateComparator(EmployeeExperienceComparator, EmployeeExperienceComparatorReversed);
    comparators[FIELD_CLASS] = CreateComparator(EmployeeClassComparator, EmployeeClassComparatorReversed);
    comparators[FIELD_DEPARTMENT] = CreateComparator(EmployeeDepartmentComparator, EmployeeDepartmentComparatorReversed);
    comparators[FIELD_PLOT] = CreateComparator(EmployeePlotComparator, EmployeePlotComparatorReversed);
    comparators[FIELD_SALARY] = CreateComparator(EmployeeSalaryComparator, EmployeeSalaryComparatorReversed);

    predicates[FIELD_ID] = (int (*)(void*, void*)) EmployeeIdPredicate;
    predicates[FIELD_SURNAME] = (int (*)(void*, void*)) EmployeeSurnamePredicate;
    predicates[FIELD_NAME] = (int (*)(void*, void*)) EmployeeNamePredicate;
    predicates[FIELD_PATRONYMIC] = (int (*)(void*, void*)) EmployeePatronymicPredicate;
    predicates[FIELD_YOB] = (int (*)(void*, void*)) EmployeeYOBPredicate;
    predicates[FIELD_GENDER] = (int (*)(void*, void*)) EmployeeGenderPredicate;
    predicates[FIELD_PROFESSION] = (int (*)(void*, void*)) EmployeeProfessionPredicate;
    predicates[FIELD_EXPERIENCE] = (int (*)(void*, void*)) EmployeeExperiencePredicate;
    predicates[FIELD_CLASS] = (int (*)(void*, void*)) EmployeeClassPredicate;
    predicates[FIELD_DEPARTMENT] = (int (*)(void*, void*)) EmployeeDepartmentPredicate;
    predicates[FIELD_PLOT] = (int (*)(void*, void*)) EmployeePlotPredicate;
    predicates[FIELD_SALARY] = (int (*)(void*, void*)) EmployeeSalaryPredicate;

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
            if (WriteFile(fileName)) {
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

void EditFind(void) {
    if (sorted == NULL) return;
    ShowFilterDialog(filterAll);
}

void EditCancelFind(void) {
    if (sorted == NULL) return;
    updateData(GetEmployees());
}

void EditAdd(void) {
    if (sorted == NULL) return;
    ShowAddDialog();
}

void EditDelete(void) {
    if (sorted == NULL) return;
    Component* component = GetFocusedComponent();
    if (component != NULL && component->custom != NULL) {
        deleteEntry(component->custom);
    } else {
        ShowIdInputDialog(deleteById);
    }
}

void EditChange(void) {
    if (sorted == NULL) return;
    Component* component = GetFocusedComponent();
    if (component != NULL && component->custom != NULL) {
        EditEntry(component);
    } else {
        ShowIdInputDialog(changeById);
    }
}

void ToolsExportCSV(void) {

}

void ToolsCreateReport(void) {
    if (sorted == NULL) return;
    ShowReportDialog();
}

void TableOnScrollDown(ScrollType scrollType) {
    if (sorted == NULL) return;
    int step = 1;
    if (scrollType == PAGE) {
        step = pageSize;
    }
    if (array_size(sorted) == 0 || pos == array_size(sorted) - 1) return;
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
    if (array_size(sorted) == 0 || pos == 0) return;
    if (pos - step < 0) {
        pos = 0;
    } else {
        pos -= step;
    }
    SetPos(pos);
}

void SortData(int fieldId, SortDirection direction) {
    if (sorted == NULL) return;
    if (direction == NONE) return;
    if (sortField == fieldId) { //признак сортировки не изменился
        if (sortDirection != direction) { //сортировка не требуется, дотстаочно перевернуть массив
            sortDirection = direction;
            array_reverse(sorted);
            pos = 0;
            SetPos(0);
        }
    } else { //признак сортировки изменился, требуется сортировка
        sortField = fieldId;
        sortDirection = direction;
        if (sortDirection == ASC) {
            array_sort(sorted, (int (*)(const void*, const void*)) comparators[sortField]->compare);
        } else {
            array_sort(sorted, (int (*)(const void*, const void*)) comparators[sortField]->compareReversed);
        }
        pos = 0;
        SetPos(0);
    }
}

void EditEntry(Component* handle) {
    ShowChangeDialog(handle->custom);
}

void OnIdButtonMouseClick(InteractivePanel* handle, MEVENT event) {
    if (event.bstate & BUTTON1_DOUBLE_CLICKED) {
        FocusSingleComponent(NULL);
        EditEntry(handle->holder);
    }
}

void OnIdButtonKeyClick(Component* handle, int key, unsigned long modifiers) {
    if (key == KEY_DELETE) {
        FocusSingleComponent(NULL);
        deleteEntry(handle->custom);
    } else if (key == KEY_ENTER) {
        FocusSingleComponent(NULL);
        EditEntry(handle);
    }
}

void ChangeSurname(Component* handle) {
    Employee* e = handle->custom;
    wchar_t* surname = EditGetValue(handle);
    if (wcscmp(surname, e->surname) != 0) {
        EmployeeSetSurname(e, surname);
        ColumnChanged(FIELD_SURNAME);
    }
}

void ChangeName(Component* handle) {
    Employee* e = handle->custom;
    wchar_t* name = EditGetValue(handle);
    if (wcscmp(name, e->name) != 0) {
        EmployeeSetName(e, name);
        ColumnChanged(FIELD_NAME);
    }
}

void ChangePatronymic(Component* handle) {
    Employee* e = handle->custom;
    wchar_t* patronymic = EditGetValue(handle);
    if (wcscmp(patronymic, e->patronymic) != 0) {
        EmployeeSetPatronymic(e, patronymic);
        ColumnChanged(FIELD_PATRONYMIC);
    }
}

void ChangeYOB(Component* handle) {
    Employee* e = handle->custom;
    int yob = parseInt(EditGetValue(handle));
    if (yob != e->yob) {
        e->yob = (short) yob;
        ColumnChanged(FIELD_YOB);
    }
}

void ChangeGender(Component* handle) {
    Employee* e = handle->custom;
    bool gender = ValueOfGender(SelectGetValue(handle));
    if (gender != e->gender) {
        e->gender = gender;
        ColumnChanged(FIELD_GENDER);
    }
}

void ChangeProfession(Component* handle) {
    Employee* e = handle->custom;
    wchar_t* profession = EditGetValue(handle);
    if (wcscmp(profession, e->profession) != 0) {
        EmployeeSetProfession(e, profession);
        ColumnChanged(FIELD_PROFESSION);
    }
}

void ChangeExperience(Component* handle) {
    Employee* e = handle->custom;
    int experience = parseInt(EditGetValue(handle));
    if (experience != e->experience) {
        e->experience = (char) experience;
        ColumnChanged(FIELD_EXPERIENCE);
    }
}

void ChangeClass(Component* handle) {
    Employee* e = handle->custom;
    ProfClass class = ValueOfProfClass(SelectGetValue(handle));
    if (class != e->class) {
        e->class = class;
        ColumnChanged(FIELD_CLASS);
    }
}

void ChangeDepartment(Component* handle) {
    Employee* e = handle->custom;
    int department = parseInt(EditGetValue(handle));
    if (department != e->department) {
        e->department = (char) department;
        ColumnChanged(FIELD_DEPARTMENT);
    }
}

void ChangePlot(Component* handle) {
    Employee* e = handle->custom;
    int plot = parseInt(EditGetValue(handle));
    if (plot != e->plot) {
        e->plot = (char) plot;
        ColumnChanged(FIELD_PLOT);
    }
}

void ChangeSalary(Component* handle) {
    Employee* e = handle->custom;
    int salary = parseInt(EditGetValue(handle));
    if (salary != e->salary) {
        e->salary = (char) salary;
        ColumnChanged(FIELD_SALARY);
    }
}

void ColumnChanged(int fieldId) {
    currentChanged = true;
    if (sortField == fieldId) {
        needSorting = true;
    }
}

void EntryAdded(Employee* e) {
    currentChanged = true;
    int updated = 0;
    if (sortDirection == ASC) {
        updated = array_sorted_add(sorted, e, (int (*)(void*, void*)) comparators[sortField]->compare, NULL);
    } else {
        updated = array_sorted_add(sorted, e, (int (*)(void*, void*)) comparators[sortField]->compareReversed, NULL);
    }
    if (updated >= pos && updated < pos + pageSize) {
        SetPos(pos);
    }
}

void EntryChanged(Employee* e) {
    if (needSorting) {
        needSorting = false;
        size_t oldPos;
        if (array_index_of(sorted, e, &oldPos) != CC_OK) oldPos = 0;
        if (sortDirection == ASC) {
            array_sort(sorted, (int (*)(const void*, const void*)) comparators[sortField]->compare);
        } else {
            array_sort(sorted, (int (*)(const void*, const void*)) comparators[sortField]->compareReversed);
        }
        size_t newPos;
        if (array_index_of(sorted, e, &newPos) != CC_OK) newPos = 0;
        if (newPos != oldPos) {
            pos = (int) (newPos - max((oldPos - pos), 0));
            SetPos(pos);
        }
    } else {
        ShowEntryChanges(e);
    }
}
