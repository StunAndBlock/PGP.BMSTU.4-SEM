#ifndef R4_H_
#define R4_H_
#pragma once
#include <X11/Xlib.h>
#include <stdlib.h>
#define X 0
#define Y 1
#define K_ESC 9

typedef struct environment {
  Window winBox;
} env;

typedef struct tainted {
  unsigned short taintedCount;
  Window *winBox;
} tainted;

typedef struct winHandl {
  Display *dpy;
  Window root;
  Window selection;
  env *rectangles;
  unsigned short rectanglesCount;
  GC gc;

} winHandl;

typedef struct dArr {
  short box[2];
} dArr;

unsigned char motion(XEvent *, winHandl *, dArr *);
void createEnv(winHandl *);
void inform(const char *, char);
unsigned char dispatch(winHandl *);
unsigned char mapNewBox(unsigned char, int, dArr *, winHandl *);
unsigned char savePAP(XEvent *, dArr *, winHandl *);
void memoryAllocator(winHandl *);
void memoryAllocatorForTainted(tainted *);
void drawTainted(tainted *, winHandl *);
unsigned char deleteBox(unsigned short, winHandl *);
int findBox(Window, winHandl *);
void sortBoxes(env *, int, int);
void freeEnv(unsigned char, winHandl *);
#endif /*R4_H_*/
