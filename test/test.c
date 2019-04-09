
#include <stdio.h>
#include <src/log.h>
#include <conio.h>
#include "test_console.h"
#include "test_gui.h"

int main(int argc, char **argv) {
    FILE* log = fopen("test.txt", "w");
    log_set_fp(log);
    mainConsole();
//    mainGUI(argc, argv);
    fclose(log);
}