#include "W23.h"
#include <stdio.h>
#include <stdlib.h>
int main(unsigned short argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "no word inputed\n");
    exit(-1);
  } else if (argc > 2) {
    fprintf(stderr, "too many words inputed\n");
    exit(-1);
  }
  envParams newEnvParams;
  transformArgs(*(argv + 1), &newEnvParams);
  winHandl newEnv;
  createEnv(&newEnv, &newEnvParams);
  dispatch(&newEnv, &newEnvParams);
  XDestroySubwindows(newEnv.dpy, newEnv.root);
  XDestroyWindow(newEnv.dpy, newEnv.root);
  XCloseDisplay(newEnv.dpy);
  freeEnv(&newEnv, &newEnvParams);
  return 0;
}

void dispatch(winHandl *newEnv, envParams *newEnvParams) {
  XEvent event;
  dArr truePos[2];
  int lastVisibilityState = 0;
  unsigned char flag = 1; /* exit flag */
  char e = 1;
  while (flag) {
    XNextEvent(newEnv->dpy, &event);
    switch (event.type) {
    case VisibilityNotify:
      lastVisibilityState = event.xvisibility.state;
      // fprintf(stderr, "%d", event.xvisibility.state);
      break;
    case ButtonRelease:
      flag = checkForOverlap(flag, lastVisibilityState, truePos[1], newEnv->dpy,
                             &event, newEnv, newEnvParams->boxCount);
      break;
    case ButtonPress:
      flag = savePointerAttachmentPositionifNotRoot(
          &event, truePos, newEnv, lastVisibilityState, newEnvParams->boxCount);
      break;
    case MotionNotify:
      flag = motion(&event, newEnv, truePos);
      break;
    case Expose:
      if (e) {
        fill(newEnv, newEnvParams);
        e--;
      }
      break;
    default:
      break;
    } /* switch */
  }   /* while */
} /* dispatch */