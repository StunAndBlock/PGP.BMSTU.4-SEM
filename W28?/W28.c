#include "W28.h"
#include <stdio.h>
#include <stdlib.h>
int main(unsigned short argc, char **argv) {
  if (argc < 2) {
    inform("no boxes inputted\nEXMAPLE: ./<programm_name> 14x23 143x10\n", -1);
  }

  winHandl newEnv;
  envParams newEnvParams;
  newEnvParams.boxCount = argc - 1;
  dispatch(&newEnv, createEnv(&newEnv, &newEnvParams, argv + 1));
  XDestroySubwindows(newEnv.dpy, newEnv.root);
  free(newEnv.boxes);
  XDestroyWindow(newEnv.dpy, newEnv.root);
  XCloseDisplay(newEnv.dpy);
  return 0;
}

void dispatch(winHandl *newEnv, dArr rootWindowSize) {

  XEvent event;
  dArr truePos[3];
  truePos[2] = rootWindowSize;
  int lastVisibilityState = 0;
  unsigned char flag = 1; /* exit flag */
  while (flag) {
    XNextEvent(newEnv->dpy, &event);
    switch (event.type) {
    case VisibilityNotify:
      lastVisibilityState = event.xvisibility.state;
      break;
    case ButtonRelease:
      flag = checkForOverlap(flag, lastVisibilityState, truePos[1], newEnv->dpy,
                             &event);
      break;
    case ButtonPress:
      flag = savePointerAttachmentPositionifNotRoot(&event, truePos, newEnv,
                                                    lastVisibilityState);
      break;
    case MotionNotify:
      flag = motion(flag, &event, newEnv, truePos);
      break;
    default:
      break;
    } /* switch */
  }   /* while */
} /* dispatch */