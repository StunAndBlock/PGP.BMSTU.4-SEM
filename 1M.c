#include "1M.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
int main() {
  Display *dpy;
  Window win;
  GC gc;
  int scr;
  XArrow r;

  unsigned long tone;
  dpy = XOpenDisplay(NULL);
  scr = DefaultScreen(dpy);
  win = DefaultRootWindow(dpy);
  scr = DefaultScreen(dpy);
  gc = XCreateGC(dpy, win, 0, 0);
  tone = WhitePixel(dpy, scr);
  XSetForeground(dpy, gc, tone);

  Atom wdw[1];
  unsigned w = 640, h = 480;
  XSetWindowAttributes attr;
  XGCValues gval;
  unsigned long amask;
  Window root = win;
  XSizeHints hint;
  configure_arrow(&r, w, h, 0);
  amask = (CWOverrideRedirect | CWBackPixel);
  XGetGCValues(dpy, gc, GCBackground, &gval);
  attr.background_pixel = gval.background;
  attr.override_redirect = False;
  win = XCreateWindow(dpy, root, 0, 0, w, h, 1, CopyFromParent, InputOutput,
                      CopyFromParent, amask, &attr);
  hint.flags = (PMinSize);
  hint.min_width = 480;
  hint.min_height = 480;
  wdw[0] = XInternAtom(dpy, "WM_DELETE_WINDOW", True);
  XSetWMProtocols(dpy, win, wdw, 1);
  XSetNormalHints(dpy, win, &hint);
  XStoreName(dpy, win, "1M BERKOVICH");
  XMapWindow(dpy, win);

  unsigned long emask;
  XEvent event;
  int freeze = -1;
  unsigned delay = DELAY;
  int multi = (1 << 12);
  int count = 0;

  int reconf;
  emask = (ExposureMask | KeyPressMask | StructureNotifyMask | KeyReleaseMask |
           FocusChangeMask);
  XSelectInput(dpy, win, emask);
  while (multi != 0) {
    event.type = 0;
    XCheckWindowEvent(dpy, win, emask, &event);
    if (event.type == ConfigureNotify) {
      w = event.xconfigure.width;
      h = event.xconfigure.height;
      reconf = 1;
    } else {
      if (reconf == 1)
        reconfigure(&r, w, h);
      reconf = 0;
      switch (event.type) {
      case Expose:
        redraw(&event, gc, &r);
        break;
      case KeyPress:
        multi = key_check(&event);
        switch (multi) {
        case 3:
          configure_arrow(&r, w, h, 0);
          break;
        case 6:
          configure_arrow(&r, w, h, 1);
          break;
        case 4:
          configure_arrow(&r, w, h, 3);
          break;
        case 5:
          configure_arrow(&r, w, h, 2);
          break;
        case 2:
        case 1:
          freeze = 1;
          reverse(multi, &r);
          break;
        default:
          break;
        }
        if (multi == 3 || multi == 4 || multi == 5 || multi == 6)
          draw_arrow(dpy, win, gc, &r);
        break;
      case KeyRelease:
        multi = key_check(&event);
        switch (multi) {
        case 2:
        case 1:
          freeze = -1;
          break;
        default:
          break;
        }
        break;
      case FocusIn:
        rep5355(dpy, AutoRepeatModeOff);
        break;
      case FocusOut:
        rep5355(dpy, AutoRepeatModeOn);
        break;
      default:
        break;
      }
    }
    if ((freeze < 0))
      continue;
    if (count++ < delay)
      continue;
    count = 0;
    draw_arrow(dpy, win, gc, &r);
    amod2pi(&r);
  }

  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return (0);
}