#include "W21.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  Window root;
  Window child;
  Window fake;
  int x;
  int y;
  XWindowAttributes xwa;
  XSetWindowAttributes attr; /* created Window attributes */
  attr.override_redirect = True;
  Display *dpy = XOpenDisplay(NULL);
  int scr = DefaultScreen(dpy);
  int depth = DefaultDepth(dpy, scr);
  root = XCreateWindow(dpy, DefaultRootWindow(dpy), 0, 0, 200, 200, 0, depth,
                       InputOutput, CopyFromParent, (CWBackPixel | CWEventMask),
                       &attr);
  XGetWindowAttributes(dpy, root, &xwa);
  XMapWindow(dpy, root);
  while (1) {
    XTranslateCoordinates(dpy, DefaultRootWindow(dpy), root, 0, 0, &x, &y,
                          &fake);
    XGetWindowAttributes(dpy, root, &xwa);
    fprintf(stderr, "%d %d %d %d\n", xwa.x, xwa.y, -x, -y);
  }

  return 0;
}