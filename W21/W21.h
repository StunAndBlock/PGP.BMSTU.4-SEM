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
unsigned char motion(XEvent *, winHandl *, dArr *);
void createEnv(winHandl *, envParams *, char **);
void inform(const char *, char);
dArr parseBoxes(char **, envParams *, Display *);
unsigned short uItos(unsigned int);
void dispatch();
unsigned char checkForOverlap(unsigned char, int, dArr, Display *, XEvent *);
unsigned char savePointerAttachmentPositionifNotRoot(XEvent *, dArr *,
                                                     winHandl *, unsigned char);
#endif /*W21_H_*/
