#ifndef W21_H_
#define W21_H_
#pragma once
#include <X11/Xlib.h>
#define X 0
#define Y 1

typedef struct winHandl {
  Display *dpy;
  Window root;
  Window *boxes;
} winHandl;

typedef struct dArr {
  short box[2];
} dArr;

typedef struct envParams {
  unsigned short boxCount;
  dArr *boxPoses;
  dArr *boxSizes;
} envParams;

void createEnv(winHandl *, envParams *, char **);
void inform(const char *, char);
dArr parseBoxes(char **, envParams *newEnvParams);
unsigned short uItos(unsigned int);
void dispatch();
unsigned char checkForOverlap(Window, Window, Display *dpy);
#endif /*W21_H_*/
