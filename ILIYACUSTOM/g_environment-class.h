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
Pixmap main_pix;
} Envi;
// typedef struct Environment Envi;



#endif // END ENV_H