#include "W28.h"
#include "stdio.h"
#include "stdlib.h"
#define TRUE_ROOT 0
#define ROOT 1
unsigned char checkForOverlap(unsigned char flag, int lastVisibilityState,
                              dArr pos, Display *dpy, XEvent *ev) {
  if (flag == 6) {
    inform("POINTER IS OUT OF ROOT BOUNDS ->RECOVER ->", 1);

  } else if (flag == 2) {
    inform("MOTION DID NOT PERFORM ->", 1);

  } else if (lastVisibilityState) {
    inform("MOTION PERFORMED INCORRECT ->", 1);
    XMoveWindow(dpy, ev->xbutton.window, pos.box[X], pos.box[Y]);
  } else {
    inform("MOTION PERFORMED CORRECT ->", 1);
  }
  inform("DISATTACHED\n", 1);
  return 1;
}

unsigned char motion(unsigned char flag, XEvent *ev, winHandl *newEnv,
                     dArr *truePos) {
  if (flag == 1 || flag == 2 || flag == 3)
    if (ev->xmotion.state & Button1Mask || ev->xmotion.state & Button2Mask ||
        ev->xmotion.state & Button3Mask) {
      void *trashPointer = malloc(sizeof(int) + sizeof(Window));

      int XY[2][2];
      XTranslateCoordinates(newEnv->dpy, DefaultRootWindow(newEnv->dpy),
                            newEnv->root, 0, 0, &XY[TRUE_ROOT][X],
                            &XY[TRUE_ROOT][Y], trashPointer);
      XQueryPointer(newEnv->dpy, ev->xbutton.window, trashPointer, trashPointer,
                    &XY[ROOT][X], &XY[ROOT][Y], trashPointer, trashPointer,
                    trashPointer);

      if (XY[ROOT][X] + XY[TRUE_ROOT][X] < 0 ||
          XY[ROOT][X] + XY[TRUE_ROOT][X] > truePos[2].box[X] ||

          XY[ROOT][Y] + XY[TRUE_ROOT][Y] < 0 ||
          XY[ROOT][Y] + XY[TRUE_ROOT][Y] > truePos[2].box[Y]) {
        XMoveWindow(newEnv->dpy, ev->xbutton.window, truePos[1].box[X],
                    truePos[1].box[Y]);
        return 6;
      }
      XMoveWindow(newEnv->dpy, ev->xbutton.window,
                  XY[ROOT][X] + XY[TRUE_ROOT][X] - truePos[0].box[X],
                  XY[ROOT][Y] + XY[TRUE_ROOT][Y] - truePos[0].box[Y]);
      free(trashPointer);
      return 3;
    }

  return 6;
}

unsigned char savePointerAttachmentPositionifNotRoot(XEvent *ev, dArr *truePos,
                                                     winHandl *newEnv,
                                                     unsigned char l) {

  if (ev->xbutton.window == newEnv->root) {
    inform("POINTER ATTACHED TO ROOT ->EXITING\n", 1);
    return 0;
  } else {
    XRaiseWindow(newEnv->dpy, ev->xbutton.window);
    XWindowAttributes xwa;
    XGetWindowAttributes(newEnv->dpy, ev->xbutton.window, &xwa);
    truePos[1].box[X] = xwa.x;
    truePos[1].box[Y] = xwa.y;
    truePos[0].box[X] = ev->xbutton.x;
    truePos[0].box[Y] = ev->xbutton.y;
  }
  inform("POINTER ATTACHED ->", 1);
  return 2;
}
