#ifndef W21_H_
#define W21_H_
#pragma once
#include <X11/Xlib.h>
#define X 0
#define Y 1
#define WHBOX 32 * 4
#define K_ESC 9
typedef struct winHandl {
  Display *dpy;
  Window root;
  Window *boxes;
  GC gc;
  XRectangle cell;
} winHandl;

typedef struct dArr {
  short box[2];
} dArr;

typedef struct envParams {
  unsigned short boxCount;
  dArr *boxPoses;
  char **reString;
} envParams;
unsigned char motion(XEvent *, winHandl *, dArr *);
void createEnv(winHandl *, envParams *);
dArr parseBoxes(char **, envParams *, Display *);
unsigned short uItos(unsigned int);
void dispatch();
unsigned char checkForOverlap(unsigned char, int, dArr, Display *, XEvent *,
                              winHandl *newEnv, unsigned short count);
unsigned char savePointerAttachmentPositionifNotRoot(XEvent *, dArr *,
                                                     winHandl *, unsigned char,
                                                     unsigned short);
void transformArgs(char *, envParams *);
void freeEnv(winHandl *, envParams *);
void fill(winHandl *, envParams *);
#endif /*W21_H_*/
