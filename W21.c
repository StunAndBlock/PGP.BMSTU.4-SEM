#include "W21.h"
#include <stdio.h>
#include <stdlib.h>
int main(unsigned short argc, char **argv) {

  winHandl newEnv;
  envParams newEnvParams;
  
  createEnv(&newEnv, &newEnvParams, argv + 1);
  dispatch(&newEnv);
  XDestroySubwindows(newEnv.dpy, newEnv.root);
  free(newEnv.boxes);
  XDestroyWindow(newEnv.dpy, newEnv.root);
  XCloseDisplay(newEnv.dpy);
  return 0;
}

void dispatch(winHandl *newEnv) {
  XEvent event;
  dArr truePos[2];
  int lastVisibilityState = 0;
  unsigned char flag = 1; /* exit flag */
  while (flag) {
    XNextEvent(newEnv->dpy, &event);
    switch (event.type) {
    case VisibilityNotify:
      lastVisibilityState = event.xvisibility.state;
    break;
   case ButtonRelease:
      flag = checkForOverlap(flag, lastVisibilityState, truePos, newEnv,
                             &event);
              
     break;
    case ButtonPress:
     flag = savePointerAttachmentPositionifNotRoot(&event, truePos, newEnv
                                                   );
      break;
    case MotionNotify:
      flag = motion(&event, newEnv, truePos);
      break;
    default:
      break;
    } /* switch */
  }   /* while */
} /* dispatch */