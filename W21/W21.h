#ifndef W21_H_
#define W21_H_
#pragma once
#include <X11/Xlib.h>

typedef struct winHandl {
  Display *dpy;
  int scr;
  int depth;
  Window root;
  Window *boxes;
} winHandl;

void inform(const char *, char);

#endif /*W21_H_*/
