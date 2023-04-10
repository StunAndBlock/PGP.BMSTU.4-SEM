#ifndef W21_H_
#define W21_H_
#pragma once
#include <X11/Xlib.h>
#include <stdlib.h>
#define X 0
#define Y 1
#define K_ESC 9

typedef struct region {
  Window* wins;
  unsigned short winCount;
  unsigned short* connections;
  int head;
} _Region;

typedef struct winHandl {
  Display *dpy;
  Window root;
  Window selection;
  _Region *regs;
  unsigned short regsCount;
  Window* tainted;
  unsigned short taintedCount;
  GC gc[2];

} winHandl;

typedef struct dArr {
  short box[2];
} dArr;

unsigned char motion(XEvent *, winHandl *, dArr *);
void createEnv(winHandl *);
unsigned char dispatch(winHandl *);
unsigned char addToRegion(unsigned char, dArr *, winHandl *,int);
unsigned char savePAP(XEvent *, dArr *, winHandl *);
void memoryAllocator(winHandl *newEnv,int);
int findWin(Window aim,Window* tainted,unsigned short);
void freeEnv(unsigned char, winHandl *);
void taintedCorrect(Window currWin,int,winHandl*);
void createRegion(winHandl *newEnv);
unsigned char deleteRegion();
int findRegion(winHandl* newEnv);
int addRegion(winHandl *newEnv);
#endif /*W21_H_*/
