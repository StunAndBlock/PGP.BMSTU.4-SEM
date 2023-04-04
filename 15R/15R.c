#include "15R.h"
#include <stdio.h>
#include <stdlib.h>
int main(unsigned short argc, char **argv) {

  winHandl newEnv;

  createEnv(&newEnv);
  freeEnv(dispatch(&newEnv), &newEnv);
  XDestroySubwindows(newEnv.dpy, newEnv.root);
  XDestroyWindow(newEnv.dpy, newEnv.root);
  XCloseDisplay(newEnv.dpy);

  return 0;
}

unsigned char dispatch(winHandl *newEnv) {
  XEvent event;
  tainted rectangles;
  rectangles.taintedCount = 0;
  dArr truePos[2];
  int lastVisibilityState = 0;
  unsigned char flag = 1; /* exit flag */
  unsigned char state = 0;
  while (flag) {
    XNextEvent(newEnv->dpy, &event);
    switch (event.type) {
    case VisibilityNotify:
      lastVisibilityState = event.xvisibility.state;
      if (lastVisibilityState &&
          event.xvisibility.window != newEnv->selection) {
        memoryAllocatorForTainted(&rectangles);
        rectangles.winBox[rectangles.taintedCount - 1] =
            event.xvisibility.window;
      }

      break;
    case ButtonRelease:
      if (event.xbutton.button == 1) {
        state = checkForOverlap(flag, lastVisibilityState, truePos, newEnv);
        if (rectangles.taintedCount) {
          free(rectangles.winBox);
          rectangles.taintedCount = 0;
        }
      }
      if ((flag == 2 || flag == 3 || flag == 4) && newEnv->rectanglesCount) {
        XWindowAttributes xwa;
        for (unsigned short i = 0; i < newEnv->rectanglesCount; i++) {
          XGetWindowAttributes(newEnv->dpy, newEnv->rectangles[i].winBox, &xwa);
          XDrawRectangle(newEnv->dpy, newEnv->rectangles[i].winBox,
                         newEnv->gc[1], 1, 1, xwa.width - 2, xwa.height - 2);
        }
      }
      break;
    case ButtonPress:
      if (event.xbutton.button == 1) {
        flag = savePointerAttachmentPositionifNotRoot(&event, truePos, newEnv);
      }
      break;
    case MotionNotify:
      flag = motion(&event, newEnv, truePos);
      if (rectangles.taintedCount) {
        drawTainted(&rectangles, newEnv);
      }
      break;
    case KeyPress:
      if ((event.xkey.state & ControlMask) && event.xkey.keycode == K_R)
        flag = 0;
      break;
    default:
      break;
    } /* switch */
  }   /* while */
  
  return state;
} /* dispatch */