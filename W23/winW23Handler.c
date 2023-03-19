#include "W23.h"
#include "stdio.h"
#include "stdlib.h"
#define TRUE_ROOT 0
#define ROOT 1
unsigned char checkForOverlap(unsigned char flag, int lastVisibilityState,
                              dArr pos, Display *dpy, XEvent *ev,
                              winHandl *newEnv, unsigned short count) {

  for (unsigned short i = 0; i < count; i++) {
    XWindowAttributes xwa;
    XGetWindowAttributes(newEnv->dpy, newEnv->boxes[i], &xwa);
    fprintf(stderr, "%d", xwa.map_state);
  }

  /* if (flag != 3) {
     // inform("MOTION DO NOT PERFORMED ->", 1);

   } else if (lastVisibilityState) {
     //   inform("MOTION PERFORMED INCORRECT ->", 1);
     XMoveWindow(dpy, ev->xbutton.window, pos.box[X], pos.box[Y]);
   } else {
     //   inform("MOTION PERFORMED CORRECT ->", 1);
   }
   // inform("DISATTACHED\n", 1);*/
  return 1;
}

unsigned char motion(XEvent *ev, winHandl *newEnv, dArr *truePos) {
  void *trashPointer = malloc(sizeof(int) + sizeof(Window));
  int XY[2][2];
  XTranslateCoordinates(newEnv->dpy, DefaultRootWindow(newEnv->dpy),
                        newEnv->root, 0, 0, &XY[TRUE_ROOT][X],
                        &XY[TRUE_ROOT][Y], trashPointer);
  XQueryPointer(newEnv->dpy, ev->xbutton.window, trashPointer, trashPointer,
                &XY[ROOT][X], &XY[ROOT][Y], trashPointer, trashPointer,
                trashPointer);
  if (ev->xmotion.state & Button1Mask || ev->xmotion.state & Button2Mask ||
      ev->xmotion.state & Button3Mask) {
    XMoveWindow(newEnv->dpy, ev->xbutton.window,
                XY[ROOT][X] + XY[TRUE_ROOT][X] - truePos[0].box[X],
                XY[ROOT][Y] + XY[TRUE_ROOT][Y] - truePos[0].box[Y]);
  }
  free(trashPointer);
  return 3;
}

unsigned char savePointerAttachmentPositionifNotRoot(XEvent *ev, dArr *truePos,
                                                     winHandl *newEnv,
                                                     unsigned char l,
                                                     unsigned short count) {

  if (ev->xbutton.window == newEnv->boxes[0] ||
      ev->xbutton.window == newEnv->boxes[count - 1]) {
    // inform("POINTER ATTACHED TO ROOT ->EXITING\n", 1);
    return 0;
  } else if (!l) {
    XWindowAttributes xwa;
    XGetWindowAttributes(newEnv->dpy, ev->xbutton.window, &xwa);
    truePos[1].box[X] = xwa.x;
    truePos[1].box[Y] = xwa.y;
    truePos[0].box[X] = ev->xbutton.x;
    truePos[0].box[Y] = ev->xbutton.y;
  }
  // inform("POINTER ATTACHED ->", 1);
  return 2;
}

void fill(winHandl *env, envParams *newEnvParams) {
  for (unsigned short i = 1; i < newEnvParams->boxCount - 1; i++)
    XDrawString(env->dpy, env->boxes[i], env->gc, env->cell.x, env->cell.y,
                newEnvParams->reString[i - 1], 1);
}