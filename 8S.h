#ifndef W21_H_
#define W21_H_
#pragma once
#include <X11/Xlib.h>
#include <stdlib.h>
#define X 0
#define Y 1
#define K_ESC 9

typedef struct environment {
  Window winBox;
  unsigned int K;
} env;


typedef struct winHandl {
  Display *dpy;
  Window root;
  Window selection;
  env *rectangles;
  unsigned short rectanglesCount;
  GC gc[2];

} winHandl;

typedef struct dArr {
  short box[2];
} dArr;

unsigned char motion(XEvent *, winHandl *, dArr *);
void createEnv(winHandl *);
void inform(const char *, char);
unsigned char dispatch(winHandl *);
unsigned char mapNewBox(unsigned char, dArr *, winHandl *);
unsigned char savePAP(XEvent *, dArr *, winHandl *);
void memoryAllocator(winHandl *);
unsigned char deleteBox(unsigned short, winHandl *);
unsigned short findBox(Window, winHandl *);
void sortBoxes(env *, int, int);
void freeEnv(unsigned char, winHandl *);
#endif /*W21_H_*/
