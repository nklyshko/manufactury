#ifndef MANUFACTURY_GLOBAL_H
#define MANUFACTURY_GLOBAL_H

#include <stdlib.h>
#include <mem.h>
#include <malloc.h>
#include <curses.h>
#include <panel.h>

#define movecurs(panel, x, y) move(getbegy(panel_window(panel)) + y, getbegx(panel_window(panel)) + x)

#endif //MANUFACTURY_GLOBAL_H