#include "W07.h"

int main(void) {
  winEnv newEnv;
  ODH num;
  createEnv(&newEnv);
  constructODH(&newEnv, &num);
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
    case Expose:
      if (!e) {
        fill(env, num);
        eraseConvert(env, num, 0);
        e++;
      }
      break;
    default:

      break;
    }
  }
}
