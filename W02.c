
#include "W02.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <stdio.h>
static Display *dpy;
int dispatch() {

  XEvent event; /* Event structure */
  int flag = 0; /* exit flag */
  while (flag == 0) {
    fprintf(stderr, "10\n");
    XNextEvent(dpy, &event);
    switch (event.type) {
    // case Expose:      rebox(&event);
    //             break;
    // case ButtonPress: //(&event);
    // flag = 1;
    //  fprintf(stderr, "10\n");
    //  break;
    case KeyPress:
      flag = 1; // kbdrive(&event);;
      break;
    default:
      fprintf(stderr, "--\n");
      break;
    } /* switch */
  }   /* while */
  return (0);
} /* dispatch */

void createField() {
  static unsigned XSP = 4;   /* x-space between 2 boxes in any row */
  static unsigned YSP = 4;   /* y-space between 2 rows */
  static unsigned BW = 32;   /* Box width */
  static unsigned BH = 32;   /* Box height */
  int x, y;                  /* windows' location */
  unsigned w, h;             /* windows' size */
  int dx, dy;                /* interwindow distance */
  int src;                   /* screen number */
  int depth;                 /* screen depth */
  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  src = DefaultScreen(dpy);
  depth = DefaultDepth(dpy, src);
  gc[0] = DefaultGC(dpy, src);
  w = NX * BW + (NX + 1) * XSP + 2 * NX + 2;
  h = NY * BH + (NY + 1) * YSP + 4 * NY;
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(dpy, src);
  x = X0;
  y = Y0;
  root = XCreateWindow(dpy, DefaultRootWindow(dpy), 0, 0, 300, 300, 0, depth,
                       InputOutput, CopyFromParent,
                       (CWOverrideRedirect | CWBackPixel), &attr);
  hint.flags = (PMinSize | PMaxSize | PPosition);
  hint.min_width = hint.max_width = w;
  hint.min_height = hint.max_height = h;
  hint.x = x;
  hint.y = y;
  // XSetNormalHints(dpy, root, &hint);
  XMapWindow(dpy, root);
  XStoreName(dpy, root, "W02");
  gc[0] = XCreateGC(dpy, root, 0, 0);

  XSetForeground(dpy, gc[0], 0x00FFFF);
}

int main(int argc, char *argv[]) {
  if (argc < 2)
    fprintf(stderr, "Default: xpat 16x4+0+0\n");
  XParseGeometry(argv[1], NULL, NULL, &NX, &NY);
  // alloc(NX, NY);
  dpy = XOpenDisplay(NULL);

  createField();
  dispatch();
  // XDestroySubwindows(dpy, root);
  fprintf(stderr, "11\n");
  XDestroyWindow(dpy, root);
  XCloseDisplay(dpy);
  // dealloc(pos, box, row);
  return (0);
}