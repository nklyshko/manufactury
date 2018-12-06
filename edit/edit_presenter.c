#include <model/data_source.h>
#include <model/array_ext.h>
#include <model/comparator.h>
#include <main/main_presenter.h>
#include "edit_presenter.h"
#include "edit_view.h"

Employee* currentEntry;

void addOnIdChange(int id) {
    if (id <= 0 || EmployeeIdExists(id)) {
        DataIdCorrectness(false);
    } else {
        DataIdCorrectness(true);
    }
}

void addOnConfirm(void) {
    Employee* e = GetEnteredData();
    AddEmployee(e);
    EntryAdded(e);
}

void addOnCancel(void) {

}


void ShowAddDialog(void) {
    ShowDataDialog(NULL, addOnIdChange, addOnConfirm, addOnCancel);
}

void editOnIdChange(int id) {
    if (id != currentEntry->id && (id <= 0 || EmployeeIdExists(id))) {
        DataIdCorrectness(false);
    } else {
        DataIdCorrectness(true);
    }
}

void editOnConfirm(void) {

}

void editOnCancel(void) {

}

void ShoEditDialog(Employee* e) {
    ShowDataDialog(e, editOnIdChange, editOnConfirm, editOnCancel);
}
