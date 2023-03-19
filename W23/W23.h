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
  unsigned short *id;
  GC gc;
  XRectangle cell;
} winHandl;

typedef struct dArr {
  short box[2];
} dArr;

typedef struct envParams {
  unsigned short boxCount;
  char **reString;
} envParams;
unsigned char motion(XEvent *, winHandl *, dArr *, unsigned short );
void createEnv(winHandl *, envParams *);
dArr parseBoxes(char **, envParams *, Display *);
unsigned short uItos(unsigned int);
void dispatch();
unsigned char checkForOverlap(unsigned char, dArr, XEvent *, winHandl *,
                              unsigned short , char *);
unsigned char savePointerAttachmentPositionifNotRoot(XEvent *, dArr *,
                                                     winHandl *,
                                                     unsigned short);
void transformArgs(char *, envParams *);
void freeEnv(winHandl *, envParams *);
void fill(winHandl *, envParams *);
void rewamp(winHandl *, envParams *);
#endif /*W21_H_*/
