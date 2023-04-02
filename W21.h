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
  Window selection;
  GC gc[3];
} winHandl;

typedef struct dArr {
  short box[2];
} dArr;

typedef struct envParams {
  XRectangle box;
  dArr boxPose;
  dArr boxSize;
} envParams;
unsigned char motion(XEvent *, winHandl *, dArr *);
void createEnv(winHandl *, envParams *, char **);
void inform(const char *, char);
dArr parseBoxes(char **, envParams *, Display *);
unsigned short uItos(unsigned int);
void dispatch();
unsigned char checkForOverlap(unsigned char, int, dArr*, winHandl *, XEvent *);
unsigned char savePointerAttachmentPositionifNotRoot(XEvent *, dArr *,
                                                     winHandl *);
#endif /*W21_H_*/
