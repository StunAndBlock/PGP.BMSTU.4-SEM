#include "W21.h"
#include "X11/Xutil.h"
#include <stdio.h>
#include <stdlib.h>

void createEnv(winHandl *newEnv, envParams *newEnvParams, char **args) {
  newEnv->dpy = XOpenDisplay(NULL);
  int scr = DefaultScreen(newEnv->dpy);
  int depth = DefaultDepth(newEnv->dpy, scr);
  dArr rootWindowSize;
  rootWindowSize.box[X]= DisplayWidth(newEnv->dpy, scr);
  rootWindowSize.box[Y]= DisplayHeight(newEnv->dpy, scr);

  newEnv->gc[0] = DefaultGC(newEnv->dpy, scr);
  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(newEnv->dpy, scr);
  attr.event_mask = (ButtonPressMask | ButtonReleaseMask | ButtonMotionMask);
  newEnv->root = XCreateWindow(
      newEnv->dpy, DefaultRootWindow(newEnv->dpy), 0, 0,
      rootWindowSize.box[X]-300, rootWindowSize.box[Y]-300, 0, depth, InputOutput,
      CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  hint.flags = (PMinSize | PMaxSize | PPosition);
  hint.min_width = hint.max_width = rootWindowSize.box[X]-300;
  hint.min_height = hint.max_height = rootWindowSize.box[Y]-300;
  hint.x = 0;
  hint.y = 0;
  XSetNormalHints(newEnv->dpy, newEnv->root, &hint);

  Pixmap pix = XCreatePixmap(newEnv->dpy, DefaultRootWindow(newEnv->dpy), 10, 10, depth);

  XDrawRectangle(newEnv->dpy,pix,newEnv->gc[0],0,0,10,10);
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(newEnv->dpy, scr);
  //attr.background_pixmap=pix;
 // attr.bit_gravity=SouthEastGravity;
  newEnv->selection=XCreateWindow(newEnv->dpy,newEnv->root,0,0,10,10,0,depth, InputOutput,
  CopyFromParent, (CWOverrideRedirect| CWBackPixel), &attr);
  XMapWindow(newEnv->dpy, newEnv->root);
  newEnv->gc[1] = XCreateGC(newEnv->dpy, newEnv->root, 0, 0);
 // XCopyGC(newEnv->dpy, newEnv->gc[0], 0, newEnv->gc[1]);
  XSetForeground(newEnv->dpy, newEnv->gc[1],
                 WhitePixel(newEnv->dpy, scr));
    newEnv->gc[2] = XCreateGC(newEnv->dpy, newEnv->root, 0, 0);
     XSetForeground(newEnv->dpy, newEnv->gc[2],
                0x8B00FF);            
  XSetLineAttributes(newEnv->dpy, newEnv->gc[0], 2, LineOnOffDash, CapNotLast, JoinMiter);
  XSetLineAttributes(newEnv->dpy, newEnv->gc[1], 2, 	LineSolid, CapNotLast, JoinMiter);
   XSetLineAttributes(newEnv->dpy, newEnv->gc[2], 2, LineOnOffDash, CapNotLast, JoinMiter);
}


