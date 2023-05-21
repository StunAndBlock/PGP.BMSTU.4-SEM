#include "1M.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <math.h>
#define MAX(X, Y) ((X) > (Y)) ? (X) : (Y)
#define MIN(X, Y) ((X) > (Y)) ? (Y) : (X)
int configure_arrow(XArrow *pr, int w, int h, int smesh) {

  pr->A[0] = M_PI / 2;
  pr->A[1] = M_PI * 4 / 3;
  pr->A[2] = M_PI * 5 / 3;
  reset(pr, smesh);
  pr->c.x = w / 2;
  pr->c.y = h / 2;
  pr->dA = (pr->dA < 0 ? -1 : 1) * M_PI / 360;
  reconfigure(pr, w, h);
  return 0;
}
int reconfigure(XArrow *pr, int w, int h) {
  pr->R[0] = MIN(w / 3, h / 3);
  pr->R[1] = pr->R[2] = pr->R[0] / 2;
  pr->c.x = w / 2;
  pr->c.y = h / 2;
  return 0;
}
int draw_arrow(Display *dpy, Window win, GC gc, XArrow *pr) {
  XClearWindow(dpy, win);
  int x1, x2, y1, y2;
  for (int i = 0; i < NPOINTS; i++) {
    x1 = pr->R[i] * cos(pr->A[i]);
    x2 = pr->R[(i + 1) % NPOINTS] * cos(pr->A[(i + 1) % NPOINTS]);
    y1 = pr->R[i] * sin(pr->A[i]);
    y2 = pr->R[(i + 1) % NPOINTS] * sin(pr->A[(i + 1) % NPOINTS]);
    XDrawLine(dpy, win, gc, pr->c.x + x1, pr->c.y - y1, pr->c.x + x2,
              pr->c.y - y2);
  }
  XFillArc(dpy, win, gc, pr->c.x - C_DOT_RADIUS / 2, pr->c.y - C_DOT_RADIUS / 2,
           C_DOT_RADIUS, C_DOT_RADIUS, 0, 360 * 64);
  XFlush(dpy);
  return 0;
}
int reset(XArrow *pr, int smesh) {
  for (int i = 0; i < NPOINTS; i++) {
    pr->A[i] += smesh * M_PI / 2;
    if (pr->A[i] > 2 * M_PI)
      pr->A[i] -= 2 * M_PI;
  }
  return 0;
}
int redraw(XEvent *ev, GC gc, XArrow *pr) {
  static XRectangle clip[32];
  static int n = 0;
  clip[n].x = ev->xexpose.x;
  clip[n].y = ev->xexpose.y;
  clip[n].width = ev->xexpose.width;
  clip[n].height = ev->xexpose.height;
  n++;
  if ((ev->xexpose.count > 0) && (n < 32))
    return (0);
  XSetClipRectangles(ev->xexpose.display, gc, 0, 0, clip, n, Unsorted);
  draw_arrow(ev->xexpose.display, ev->xexpose.window, gc, pr);
  XSetClipMask(ev->xexpose.display, gc, None);
  return (n = 0);
}
int reverse(int where, XArrow *pr) {
  if (where == 1) {
    pr->dA = DA;
    return 1;
  }
  if (where == 2) {
    pr->dA = -DA;
    return 1;
  }
  return -1;
}
int amod2pi(XArrow *pr) {
  for (int i = 0; i < NPOINTS; i++) {
    pr->A[i] += (pr->dA);
    if (pr->A[i] == 2 * M_PI)
      pr->A[i] = (0);
    else if (pr->A[i] == (0))
      pr->A[i] = 2 * M_PI;
  }
  return 0;
}
int key_check(XEvent *ev) {
  KeySym ks = XLookupKeysym((XKeyEvent *)ev, 1);
  if ((ks == XK_A) && (ev->xkey.state & ControlMask))
    return 0; /*код выхода*/
  if (ks == XK_plus)
    return 1;
  if (ks == XK_underscore)
    return 2;
  if (ks == XK_Up)
    return 3;
  if (ks == XK_Right)
    return 4;
  if (ks == XK_Down)
    return 5;
  if (ks == XK_Left)
    return 6;
  return ev->xkey.keycode;
}
int rep5355(Display *dpy, int r) {
  XKeyboardControl kbval;
  kbval.key = XKeysymToKeycode(dpy, XK_plus);
  kbval.auto_repeat_mode = r;
  XChangeKeyboardControl(dpy, (KBKey | KBAutoRepeatMode), &kbval);
  kbval.key = XKeysymToKeycode(dpy, XK_underscore);
  XChangeKeyboardControl(dpy, (KBKey | KBAutoRepeatMode), &kbval);
  return (r);
}