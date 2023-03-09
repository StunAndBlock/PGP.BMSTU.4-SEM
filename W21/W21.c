#include "W21.h"
#include <stdlib.h>

int main(unsigned short argc, char **argv) {
  if (argc < 2) {
    inform("no boxes inputted\nEXMAPLE: ./<programm_name> 14x23 143x10\n", -1);
  }
  winHandl newEnv;
  envParams newEnvParams;
  newEnvParams.boxCount = argc - 1;
  createEnv(&newEnv, &newEnvParams, argv + 1);
  dispatch(&newEnv);
  XDestroyWindow(newEnv.dpy, newEnv.root);
  XCloseDisplay(newEnv.dpy);
  return 0;
}

void dispatch(winHandl *newEnv) {
  XEvent event;           /* Event structure */
  unsigned char flag = 1; /* exit flag */
  while (flag) {
    XNextEvent(newEnv->dpy, &event);
    switch (event.type) {
    case ButtonPress:
      flag = 0;
      break;
    case KeyPress:
      flag = 0;
      break;
    default:

      break;
    } /* switch */
  }   /* while */
} /* dispatch */