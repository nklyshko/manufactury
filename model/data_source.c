#include <array.h>
#include <stdio.h>
#include <io.h>
#include <errno.h>
#include "data_source.h"
#include "data_types.h"
#include "array_ext.h"
#include "comparator.h"

#ifdef _WIN32
#define FILE_SEPARATOR   '\\'
#else
#define FILE_SEPARATOR   '/'
#endif

#define FILE_MARK "mnf"
#define FILE_MARK_LENGTH 3
#define BACKUP_PREFIX "backup"
#define BAKCUP_PREFIX_SIZE 7

Array* employees;

int namePos(char* path, int len) {
    int i = len;
    while (i >= 0) {
        if (path[i] == FILE_SEPARATOR) return i + 1;
        i--;
    }
    return 0;
}

void InitDataSource(void) {
    array_new(&employees);
}

void AddEmployee(Employee* e) {
    array_sorted_add(employees, e, (int (*)(void*, void*)) EmployeeIdComparator);
}

void RemoveEmployee(Employee* e) {
    array_remove(employees, e, NULL);
}

bool EmployeeIdExists(Employee* e) {
    return array_sorted_contains(employees, e, (int (*)(void*, void*)) EmployeeIdComparator);
}

Array* GetEmployees(void) {
    return employees;
}

bool ReadFile(char* fileName) {
    FILE* file = fopen(fileName, "rb");
    if (file == NULL) return errno == ENOENT;
    if (fseek(file, 1, SEEK_SET) != 0) {
        fclose(file);
        return false;
    }

    char mark[FILE_MARK_LENGTH + 1];
    mark[FILE_MARK_LENGTH] = '\0';
    if (fread(mark, FILE_MARK_LENGTH, 1, file) != 1 || strcmp(mark, FILE_MARK) != 0) {
        fclose(file);
        return false;
    }

    size_t dataSize = sizeof(Employee);
    fseek(file, 0, SEEK_END);
    int dataLength = (ftell(file) - FILE_MARK_LENGTH - 1);
    if (dataLength % dataSize != 0) {
        fclose(file);
        return false;
    }

    WipeData();
    int fileSize = (int) (dataLength / dataSize);
    Employee* e;
    fseek(file, FILE_MARK_LENGTH + 1, SEEK_SET);
    for (int i = 0; i < fileSize; i++) {
        e = malloc(dataSize);
        if (fread(e, dataSize, 1, file) == 0) {
            free(e);
            break;
        }
        array_add(employees, e);
    }
    fclose(file);
    if (array_size(employees) == fileSize) {
        return true;
    } else {
        array_remove_all_free(employees);
        return false;
    }
}

bool WriteFile(char* fileName) {
    FILE* file = fopen(fileName, "wb");
    if (file == NULL) return false;

    int v = 0; //version byte, unused
    if (fwrite(&v, 1, 1, file) != 1 || fwrite(FILE_MARK, FILE_MARK_LENGTH, 1, file) != 1) {
        fclose(file);
        return false;
    }

    ArrayIter iter;
    array_iter_init(&iter, employees);
    Employee* e = NULL;
    size_t dataSize = sizeof(Employee);
    while (array_iter_next(&iter, (void**) &e) != CC_ITER_END) {
        if (fwrite(e, dataSize, 1, file) != 1) {
            fclose(file);
            return false;
        }
    }
    return fclose(file) == 0;
}

bool BackupFile(char* fileName) {
    int len = (int) strlen(fileName);
    char* backupFileName = malloc((strlen(fileName) + BAKCUP_PREFIX_SIZE) * sizeof(char));
    strcpy(backupFileName, fileName);
    int p = namePos(fileName, len);
    memmove(backupFileName + p + BAKCUP_PREFIX_SIZE, backupFileName + p, (size_t) (len - p) + 1);
    memcpy(backupFileName + p, BACKUP_PREFIX, BAKCUP_PREFIX_SIZE);
    if (access(backupFileName, F_OK) != -1) {
        if (remove(backupFileName) != 0) return false;
    }
    return rename(fileName, backupFileName) == 0;
}

void WipeData() {
    array_remove_all_free(employees);
}