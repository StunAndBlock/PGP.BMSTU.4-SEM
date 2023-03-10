#include "W21.h"
#include <stdio.h>
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
  unsigned int mask;
  int root_x, root_y;
  int rel_x, rel_y;
  int rel_x_, rel_y_;
  Window root_window;
  Window child;
  int true_root_x;
  int true_root_y;

  while (flag) {
    XNextEvent(newEnv->dpy, &event);
    switch (event.type) {
    case ButtonPress:
      if (event.xbutton.window == newEnv->root) {
        flag = 0;
      } else {
        rel_x_ = event.xbutton.x;
        rel_y_ = event.xbutton.y;
      }
      break;
    case MotionNotify:
      XTranslateCoordinates(newEnv->dpy, DefaultRootWindow(newEnv->dpy),
                            newEnv->root, 0, 0, &true_root_x, &true_root_y,
                            &child);
      XQueryPointer(newEnv->dpy, event.xbutton.window, &root_window, &child,
                    &root_x, &root_y, &rel_x, &rel_y, &mask);
      if (event.xmotion.state & Button1Mask ||
          event.xmotion.state & Button2Mask) {
        // fprintf(stderr, "%d %d\t%d %d\n", root_x + true_root_x,
        //       root_y + true_root_y, rel_x, rel_y);
        XMoveWindow(newEnv->dpy, event.xbutton.window,
                    root_x + true_root_x - rel_x_,
                    root_y + true_root_y - rel_y_);
        flag = 14;
      }
      break;
    case ButtonRelease:
      if (flag == 14) {
        checkForOverlap(newEnv->root, event.xbutton.window, newEnv->dpy);
        inform("2", 1);
        flag = 1;
      }
      break;
    case KeyPress:
      flag = 0;
      break;
    default:

      break;
    } /* switch */
  }   /* while */
} /* dispatch */