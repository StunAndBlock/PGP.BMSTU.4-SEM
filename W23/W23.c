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
  freeEnv(&newEnv, &newEnvParams);
  XDestroySubwindows(newEnv.dpy, newEnv.root);
  XDestroyWindow(newEnv.dpy, newEnv.root);
  XCloseDisplay(newEnv.dpy);

  return 0;
}

void dispatch(winHandl *newEnv, envParams *newEnvParams) {
  XEvent event;
  dArr truePos[2];
  unsigned char flag = 1; /* exit flag */
  char e = 1;
  char status[newEnvParams->boxCount];
  for (int i = 0; i < newEnvParams->boxCount; i++) {
    status[i] = 0;
  }
  while (flag) {
    XNextEvent(newEnv->dpy, &event);
    switch (event.type) {
    case VisibilityNotify:
      fill(newEnv, newEnvParams);
      for (int i = 0; i < newEnvParams->boxCount; i++) {
        if (newEnv->boxes[i] == event.xvisibility.window)
          if (status[i]) {
            status[i] = 0;
          } else {
            status[i] = 1;
          }
      }
      break;
    case ButtonRelease:
      flag = checkForOverlap(flag, truePos[1], &event, newEnv,
                             newEnvParams->boxCount, status);
      break;
    case ButtonPress:
      flag = savePointerAttachmentPositionifNotRoot(&event, truePos, newEnv,
                                                    newEnvParams->boxCount);
      break;
    case MotionNotify:
      flag = motion(&event, newEnv, truePos, newEnvParams->boxCount);

      break;
    case Expose:
      if (e) {
        fill(newEnv, newEnvParams);
        e--;
      }
      break;
      case KeyPress:
      if(event.xkey.keycode==K_ESC)
      rewamp(newEnv,newEnvParams);
      break;
    default:
      break;
    } /* switch */
  }   /* while */
} /* dispatch */