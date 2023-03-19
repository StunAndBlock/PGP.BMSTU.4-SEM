#include "W23.h"
#include "stdio.h"
#include "stdlib.h"
#define TRUE_ROOT 0
#define ROOT 1

unsigned short findCurW(Window win, Window *boxes, unsigned short count) {
  for (unsigned short i = 0; i < count; i++) {
    if (win == boxes[i])
      return i;
  }
}

Window findNumWindow(winHandl *newEnv, unsigned short comId,
                     unsigned short count) {
  for (int i = 0; i < count; i++) {
    if (comId == newEnv->id[i])
      return newEnv->boxes[i];
  }
}
unsigned char checkForOverlap(unsigned char flag, dArr pos, XEvent *ev,
                              winHandl *newEnv, unsigned short count,
                              char *status) {
  if (flag == 3) {
    unsigned short currentWI =
        newEnv->id[findCurW(ev->xbutton.window, newEnv->boxes, count)];
    unsigned short k = 0;
    unsigned short windowI[2];
    XWindowAttributes xwa;
    unsigned short stash;
    Window win;
    for (unsigned short i = 0; i < count; i++) {
      fprintf(stderr, "%d", status[i]);
      if (!status[i])
        windowI[k++] = newEnv->id[i];
    }

    fprintf(stderr, "\n");
    fprintf(stderr, "%d ", currentWI);
    if (k == 2) {
      fprintf(stderr, "{%d %d}\n", windowI[0], windowI[1]);
      if (currentWI < windowI[0]) {
        for (unsigned short i = currentWI + 1; i <= windowI[0]; i++) {
          win = findNumWindow(newEnv, i, count);
          XGetWindowAttributes(newEnv->dpy, win, &xwa);
          XMoveWindow(newEnv->dpy, win, xwa.x - WHBOX - 8, xwa.y);
        }
        win = findNumWindow(newEnv, windowI[1], count);
        XGetWindowAttributes(newEnv->dpy, win, &xwa);
        XMoveWindow(newEnv->dpy, ev->xbutton.window, xwa.x - WHBOX - 8, xwa.y);
      } else if (currentWI > windowI[1]) {

        for (unsigned short i = windowI[1]; i < currentWI; i++) {
          win = findNumWindow(newEnv, i, count);
          XGetWindowAttributes(newEnv->dpy, win, &xwa);
          XMoveWindow(newEnv->dpy, win, xwa.x + WHBOX + 8, xwa.y);
        }
        win = findNumWindow(newEnv, windowI[0], count);
        XGetWindowAttributes(newEnv->dpy, win, &xwa);
        XMoveWindow(newEnv->dpy, ev->xbutton.window, xwa.x + WHBOX + 8, xwa.y);

       // for (unsigned short i = windowI[1]; i < currentWI; i++) {
         // newEnv->id[i] = newEnv->id[i + 1];
       // }
       // newEnv->id[currentWI] = windowI[1];
      }

    } else {
      XMoveWindow(newEnv->dpy, ev->xbutton.window, pos.box[X], pos.box[Y]);
    }
    // for (unsigned short i = 0; i < count; i++) {
    // fprintf(stderr, "%d-%ld\n", newEnv->id[i], newEnv->boxes[i] % 1000);
    //}
  }
  return 1;
}

unsigned char motion(XEvent *ev, winHandl *newEnv, dArr *truePos,
                     unsigned short count) {
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
    if (XY[ROOT][X] + XY[TRUE_ROOT][X] - truePos[0].box[X] <
            -truePos[0].box[X] ||
        XY[ROOT][X] + XY[TRUE_ROOT][X] > (WHBOX + 8) * count + 2) {
      XMoveWindow(newEnv->dpy, ev->xbutton.window, truePos[1].box[X],
                  truePos[1].box[Y]);
      free(trashPointer);
      return 7;
    }
    XMoveWindow(newEnv->dpy, ev->xbutton.window,
                XY[ROOT][X] + XY[TRUE_ROOT][X] - truePos[0].box[X],
                truePos[1].box[Y]);
  }
  free(trashPointer);
  return 3;
}

unsigned char savePointerAttachmentPositionifNotRoot(XEvent *ev, dArr *truePos,
                                                     winHandl *newEnv,
                                                     unsigned short count) {

  if (ev->xbutton.window == newEnv->boxes[0] ||
      ev->xbutton.window == newEnv->boxes[count - 1]) {

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
  return 2;
}

void fill(winHandl *env, envParams *newEnvParams) {
  for (unsigned short i = 1; i < newEnvParams->boxCount - 1; i++)
    XDrawString(env->dpy, env->boxes[i], env->gc, env->cell.x, env->cell.y,
                newEnvParams->reString[i - 1], 1);
}

void rewamp(winHandl *newEnv, envParams *newEnvParams){
unsigned short dx = 4;
  for (unsigned short i = 0; i < newEnvParams->boxCount; i++, dx += WHBOX + 8) {
  XMoveWindow(newEnv->dpy, newEnv->boxes[i],dx,2);
    newEnv->id[i] = i;
  }


}