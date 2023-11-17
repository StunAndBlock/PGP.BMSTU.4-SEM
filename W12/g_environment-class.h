#ifndef G_ENVIRONMENT_CLASS_H
#define G_ENVIRONMENT_CLASS_H
#pragma once //for >=C+11 STANDART
#include "X11/Xlib.h"
#include "./g_configurations.h"

typedef struct Environment {
Display* dpy;
int depth;
GC paint_gc;
GC erase_gc;
XRectangle font_aligns;
XRectangle font_aligns_exit;
Window root_win;
Window main_win;
Window exit_win;
Window rowsblock_win;
Window binrowblock_win;
Window complementbinrowblock_win;
Window binrow_wins[BIT_WINDOW_AMOUNT];
Window complementbinrow_wins[BIT_WINDOW_AMOUNT];
char bin_str[BIT_WINDOW_AMOUNT];
char complementbin_str[BIT_WINDOW_AMOUNT];

} Envi;
// typedef struct Environment Envi;



#endif // END ENV_H