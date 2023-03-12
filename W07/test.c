#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static Display *dpy;
static Window root;
int main() {
  dpy = XOpenDisplay(NULL);

  int scr = DefaultScreen(dpy);
  int depth = DefaultDepth(dpy, scr);
  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  XFontStruct *fn; /* Font parameters structure */
  char *fontname = "9x15";
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(dpy, scr);
  // attr.event_mask = (ButtonPressMask);
  Window win;

  /* Font custom */
  if ((fn = XLoadQueryFont(dpy, fontname)) == NULL) {
    fprintf(stderr, "a");
  }

  root = XCreateWindow(dpy, DefaultRootWindow(dpy), 10, 10, 300, 300, 0, depth,
                       InputOutput, CopyFromParent,
                       (CWOverrideRedirect | CWBackPixel), &attr);
  attr.override_redirect = True;
  attr.background_pixel = WhitePixel(dpy, scr);
  attr.event_mask = (KeyPressMask);
  win = XCreateWindow(dpy, root, 10, 10, 40, 40, 1, depth, InputOutput,
                      CopyFromParent,
                      (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  XMapWindow(dpy, root);
  XMapSubwindows(dpy, root);
  GC gc = XCreateGC(dpy, root, 0, NULL);
  XSetFont(dpy, gc, fn->fid);
  XSetForeground(dpy, gc, BlackPixel(dpy, scr));

  // XFlush(dpy);
  char *string1 = "Hi! I'm a window, who are you?";
  char *string2 = "To terminate program, press any key";
  char *string3 = "or button while in this window.";
  char *string4 = "Screen Dimensions:";
  int len1, len2, len3, len4;
  int width1, width2, width3;
  char cd_height[50], cd_width[50], cd_depth[50];
  int font_height;
  int initial_y_offset, x_offset;
  /* Need length for both XTextWidth and XDrawString */
  len1 = strlen(string1);
  len2 = strlen(string2);
  len3 = strlen(string3);
  /* Get string widths for centering */
  width1 = XTextWidth(fn, string1, len1);
  width2 = XTextWidth(fn, string2, len2);
  width3 = XTextWidth(fn, string3, len3);
  /* Output text, centered on each line */
  font_height = fn->ascent + fn->descent;
  /* Output text, centered on each line */
  /* Copy numbers into string variables */

  while (1) {
    XDrawString(dpy, win, gc, 10, 10, "1", 1);
    XEvent event;
    XNextEvent(dpy, &event);
    switch (event.type) {
    case KeyPress:
      XDrawString(dpy, win, gc, 10, 10, "1", 1);
      fprintf(stderr, "1");
      break;
    case ButtonPress:
    default:
      break;
    }
  }
}