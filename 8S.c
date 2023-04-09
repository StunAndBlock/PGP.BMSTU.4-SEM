#include "8S.h"
#include <stdio.h>

int main(void) {
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
  dArr truePos[2];
  Window* tainted;
  unsigned char taintedCount=0;
  int lastVisibilityState = 0;
  unsigned char flag = 1; /* exit flag */
  unsigned char state = 0;
  while (flag) {
    XNextEvent(newEnv->dpy, &event);
    switch (event.type) {
    case VisibilityNotify:
    taintedCorrect(tainted,&taintedCount);
    case ButtonRelease:
      if (event.xbutton.button == 1 ) {
        if (taintedCount){
        state = addToRegion(flag, truePos, newEnv);
      }
      break;
    case ButtonPress:
      if (event.xbutton.button == 1) {
        flag = savePAP(&event, truePos, newEnv);
      } else if (event.xbutton.button == 3 &&
                 event.xbutton.window != newEnv->root) {
        flag = deleteRegin();
      }
      break;
    case MotionNotify:
      flag = motion(&event, newEnv, truePos);
      break;
    case KeyPress:
      if (event.xkey.keycode == K_ESC)
        flag = 0;
      break;
    default:
      break;
    } /* switch */
  }   /* while */
  return state;
} /* dispatch */
