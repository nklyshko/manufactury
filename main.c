#include <stdio.h>
#include <curses.h>
#include <panel.h>
#include <src/log.h>
#include "global.h"
#include "model_contract.h"
#include "view/view_contract.h"
#include "presenter_contract.h"

#define LOG_FILE "log.txt"

int main(int argc, char** argv) {
    FILE* log = fopen(LOG_FILE, "a");
    log_set_fp(log);
    InitView();
    InitApplication(NULL);
    StartControl();
    DestroyView();
    fclose(log);
}