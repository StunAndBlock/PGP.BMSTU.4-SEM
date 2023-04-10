#include "R4.h"
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
  int lastVisibilityState = 0;
  unsigned char flag = 1; /* exit flag */
  unsigned char state = 0;
  while (flag) {
    XNextEvent(newEnv->dpy, &event);
    switch (event.type) {
    case VisibilityNotify:
    if(flag==4)
      flag = deleteBox(findBox(event.xvisibility.window, newEnv), newEnv);
      break;
    case ButtonRelease:
      if (event.xbutton.button == 1) {
        state = mapNewBox(flag, lastVisibilityState, truePos, newEnv);
      }
      for(int i=0;i<newEnv->rectanglesCount;i++){
        fprintf(stderr,"[%d]%ld {%d}\n",i,newEnv->rectangles[i].winBox,newEnv->rectanglesCount);
      }
      fprintf(stderr,"----\n");
      break;
    case ButtonPress:
      if (event.xbutton.button == 1) {
        flag = savePAP(&event, truePos, newEnv);
      } else if (event.xbutton.button == 3 &&
                 event.xbutton.window != newEnv->root) {
        flag = deleteBox(findBox(event.xbutton.window, newEnv), newEnv);
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
