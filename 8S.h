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
} Region;


typedef struct winHandl {
  Display *dpy;
  Window root;
  Window selection;
  Region *regs;
  unsigned short regsCount;
  GC gc[2];

} winHandl;

typedef struct dArr {
  short box[2];
} dArr;

unsigned char motion(XEvent *, winHandl *, dArr *);
void createEnv(winHandl *);
void inform(const char *, char);
unsigned char dispatch(winHandl *);
unsigned char manageRegion(unsigned char, dArr *, winHandl *,unsigned char);
unsigned char savePAP(XEvent *, dArr *, winHandl *);
void memoryAllocator(winHandl *);
unsigned char deleteRegion(unsigned short, winHandl *);
int findWin(Window aim,Window* tainted,unsigned short);
void freeEnv(unsigned char, winHandl *);
void taintedCorrect(XEvent* ,Window* ,unsigned char*);
#endif /*W21_H_*/
