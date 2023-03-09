#ifndef W21_H_
#define W21_H_
#pragma once
#include <X11/Xlib.h>

typedef struct winHandl {
  Display *dpy;
  Window root;
  Window *boxes;
} winHandl;
typedef struct envParams {
  short boxCount;
  short** boxParsed;
}


void inform(const char *, char);

#endif /*W21_H_*/
