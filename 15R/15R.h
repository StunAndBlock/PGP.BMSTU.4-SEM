#ifndef W21_H_
#define W21_H_
#pragma once
#include <X11/Xlib.h>
#define X 0
#define Y 1

#define K_R 27
typedef struct environment {
  Window winBox;
} env;

typedef struct tainted {
  unsigned short taintedCount;
  Window *winBox;
} tainted;

typedef struct dArr {
  short box[2];
} dArr;

typedef struct winHandl {
  Display *dpy;
  Window root;
  Window selection;
  Pixmap pix;
  dArr rtwn;
  env *rectangles;
  unsigned short rectanglesCount;
  GC gc[4];

} winHandl;



unsigned char motion(XEvent *, winHandl *, dArr *);
void createEnv(winHandl *);
void inform(const char *, char);
unsigned char dispatch(winHandl *);
unsigned char checkForOverlap(unsigned char, int, dArr *, winHandl *);
unsigned char savePointerAttachmentPositionifNotRoot(XEvent *, dArr *,
                                                     winHandl *);
void memoryAllocator(winHandl *);
void memoryAllocatorForTainted(tainted *);
void drawTainted(tainted *, winHandl *);
unsigned char deleteBox(unsigned short, winHandl *);
unsigned short findBox(Window, winHandl *);
void sortBoxes(env *, int, int);
void freeEnv(unsigned char, winHandl *);
#endif /*W21_H_*/
