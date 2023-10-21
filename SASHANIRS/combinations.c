#include "combinations.h"
#include "stdio.h"
int main(void) {
  winEnv newEnv;
  ODH num;
  createEnv(&newEnv);
  int ber;
  scanf("%d",&ber);
  dispatch(&newEnv, &num);
  XDestroySubwindows(newEnv.dpy, newEnv.root);
  XDestroyWindow(newEnv.dpy, newEnv.root);
  freeEnv(&newEnv);
  XCloseDisplay(newEnv.dpy);
  
}

void dispatch(winEnv *env, ODH *num) {
  unsigned char flag = 1;
  char e = 0;
  XEvent event;

  while (flag) {
    XNextEvent(env->dpy, &event);
    switch (event.type) {
      break;
    case KeyPress:
      keycontrol(event.xkey.keycode, env, num);
      break;
    case ButtonPress:
      flag = control(event.xbutton.window, env, num);
      break;

    default:
      XDrawString(env->dpy, env->root, env->gc[0], 60,
                  60, "C", 1);
      break;
    }
  }
}
