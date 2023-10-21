#include "combinations.h"
#include "stdio.h"
int main(void) {
  winEnv newEnv;
  createEnv(&newEnv);
  Cb comb;
  scanf("%d%d",&comb.n,&comb.m);
  convertString(&comb);
  configFonts(&newEnv,&comb);
  dispatch(&newEnv,&comb);
  XDestroySubwindows(newEnv.dpy, newEnv.root);
  XDestroyWindow(newEnv.dpy, newEnv.root);
  freeEnv(&newEnv);
  XCloseDisplay(newEnv.dpy);
  
}

void dispatch(winEnv *env,Cb* comb) {
  unsigned char flag = 1;
  char e = 0;
  XEvent event;

  while (flag) {
    XNextEvent(env->dpy, &event);
    switch (event.type) {
      break;
    case KeyPress:
      keycontrol(event.xkey.keycode, env);
      break;
    case ButtonPress:
      flag = control(event.xbutton.window, env);
      break;

    default:
      arrangeForm(env,comb);
      break;
    }
  }
}
