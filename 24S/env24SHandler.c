#include "24S.h"
#include "X11/Xutil.h"
#include <stdio.h>
#include <stdlib.h>

void createEnv(winHandl *newEnv) {
  newEnv->dpy = XOpenDisplay(NULL);
  newEnv->rectanglesCount = 0;
  int scr = DefaultScreen(newEnv->dpy);
  int depth = DefaultDepth(newEnv->dpy, scr);
  dArr rootWindowSize;
  rootWindowSize.box[X] = DisplayWidth(newEnv->dpy, scr);
  rootWindowSize.box[Y] = DisplayHeight(newEnv->dpy, scr);
  newEnv->gc[0] = DefaultGC(newEnv->dpy, scr);
  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(newEnv->dpy, scr);
  attr.event_mask =
      (ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | KeyPressMask);
  newEnv->root =
      XCreateWindow(newEnv->dpy, DefaultRootWindow(newEnv->dpy), 0, 0,
                    rootWindowSize.box[X] - 300, rootWindowSize.box[Y] - 300, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  hint.flags = (PMinSize | PMaxSize | PPosition);
  hint.min_width = hint.max_width = rootWindowSize.box[X] - 300;
  hint.min_height = hint.max_height = rootWindowSize.box[Y] - 300;
  hint.x = 0;
  hint.y = 0;
  XSetNormalHints(newEnv->dpy, newEnv->root, &hint);

  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(newEnv->dpy, scr);
  // attr.background_pixmap=pix;
  // attr.bit_gravity=SouthEastGravity;
  attr.event_mask = (VisibilityChangeMask | KeyPressMask);
  newEnv->selection = XCreateWindow(
      newEnv->dpy, newEnv->root, 0, 0, 10, 10, 0, depth, InputOutput,
      CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  XMapWindow(newEnv->dpy, newEnv->root);
  newEnv->gc[1] = XCreateGC(newEnv->dpy, newEnv->root, 0, 0);
  // XCopyGC(newEnv->dpy, newEnv->gc[0], 0, newEnv->gc[1]);
  XSetForeground(newEnv->dpy, newEnv->gc[1], BlackPixel(newEnv->dpy, scr));
  newEnv->gc[2] = XCreateGC(newEnv->dpy, newEnv->root, 0, 0);
  XSetForeground(newEnv->dpy, newEnv->gc[2], 0x8B00FF);
  XSetBackground(newEnv->dpy, newEnv->gc[2], 0x8B00FF);
  XSetLineAttributes(newEnv->dpy, newEnv->gc[0], 2, LineOnOffDash, CapNotLast,
                     JoinMiter);
  XSetLineAttributes(newEnv->dpy, newEnv->gc[1], 2, LineSolid, CapNotLast,
                     JoinMiter);
  XSetLineAttributes(newEnv->dpy, newEnv->gc[2], 2, LineSolid, CapNotLast,
                     JoinMiter);
}

void freeEnv(unsigned char state, winHandl *newEnv) {
  if (state)
    free(newEnv->rectangles);
  XFreeGC(newEnv->dpy, newEnv->gc[2]);
  XFreeGC(newEnv->dpy, newEnv->gc[1]);
}
