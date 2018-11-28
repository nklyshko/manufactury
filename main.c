#include <stdio.h>
#include <curses.h>
#include <panel.h>
#include <src/log.h>
#include "global.h"
#include "model_contract.h"
#include "view/view_contract.h"
#include "presenter_contract.h"

#define LOG_FILE "log.txt"

int main() {
    FILE* log = fopen(LOG_FILE, "a");
    log_set_fp(log);
    InitView();
    StartControl();
    fclose(log);
}