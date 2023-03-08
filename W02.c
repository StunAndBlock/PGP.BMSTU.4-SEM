
#include "W02.h"

#include <stdio.h>

Display *dpy;
winHandl field;

int dispatch() {
  XEvent event;  /* Event structure */
  byte flag = 1; /* exit flag */
  while (flag) {
    XNextEvent(dpy, &event);
    switch (event.type) {
    case ButtonPress:
      // changeColor_legacy(dpy, event.xbutton.window, &field); -- legacy
      mouseDrive(dpy, &event);

      break;
    case KeyPress:
      kbDrive(dpy, &event, &field, &flag);
      break;
    default:

      break;
    } /* switch */
  }   /* while */
  return (0);
} /* dispatch */

int main(int argc, char *argv[]) {
  if (argc < 3)
    fprintf(stderr, "Default: xpat 16x4 32x32\n");
  dpy = XOpenDisplay(NULL);
  field.nParam = parseFieldParametres(dpy, argv[1], argv[2]);

  createField(&field, dpy);
  paletteMapCreate(dpy);
  dispatch();

  for (unsigned short i = 0; i < field.nParam.arr[NY_F]; i++)
    XDestroySubwindows(dpy, field.row[i]);
  XDestroySubwindows(dpy, field.root);
  XDestroyWindow(dpy, field.root);
  XCloseDisplay(dpy);
  freeField(&field);
  return (0);
}