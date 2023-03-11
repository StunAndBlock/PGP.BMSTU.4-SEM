#include "W07.h"
#include <stdlib.h>
#include <X11/Xutil.h>


void createEnv(winEnv* env){


env->dpy = XOpenDisplay(NULL);
  int scr = DefaultScreen(env->dpy);
  int depth = DefaultDepth(env->dpy, scr);
  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(env->dpy, scr);
  attr.event_mask = (ButtonPressMask);
  env->root = XCreateWindow(
      env->dpy, DefaultRootWindow(env->dpy), 300, 300,
      WIN_W,WIN_H , 0, depth, InputOutput,
      CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  hint.flags = (PMinSize | PMaxSize | PPosition);
  hint.min_width = hint.max_width = WIN_W;
  hint.min_height = hint.max_height = WIN_H;
  hint.x = 300;
  hint.y = 300;
  XSetNormalHints(env->dpy, env->root, &hint);

  env->cellArr =(Window *)malloc(sizeof(Window) * CELL_COUNT);
  unsigned short dx=2;
  attr.override_redirect = True;
  attr.event_mask = (ButtonPressMask | ButtonReleaseMask | ButtonMotionMask |
                     VisibilityChangeMask);
  attr.background_pixel = WhitePixel(env->dpy,scr);
  for (unsigned short i = 0; i < CELL_COUNT; i++;dx+=OFFSET) {
    env->cellArr[i] = XCreateWindow(
        env->dpy, env->root, dx,
        2, CELL_SIZE,CELL_SIZE, 1, depth, InputOutput, CopyFromParent,
        (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  }

  XMapWindow(newEnv->dpy, newEnv->root);
  XMapSubwindows(newEnv->dpy, newEnv->root);
}

void freeEnv(winEnv* env){
    free(env->cellArr);
}






