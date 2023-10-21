#include "./combinations.h"
#include "./choose.h"
#include "stdio.h"
int main(void) {
  winEnv newEnv;
  struct Choose choose_result;
  Cb comb;
  scanf("%d%d",&comb.n,&comb.m);
  choose_result=choose(comb.n,comb.m);
  if( choose_result.opcode==-2){
    fprintf(stderr,"m>n");
  } else if ( choose_result.opcode==-1){
    fprintf(stderr,"overflow");
  } else {
    comb.result=choose_result.result;
  convertString(&comb);
  createEnv(&newEnv,&comb);
  fprintf(stdout,"C(%d,%d)=%lld",comb.n,comb.m,choose_result.result);
  configFonts(&newEnv,&comb);
  dispatch(&newEnv,&comb);
  XDestroySubwindows(newEnv.dpy, newEnv.root);
  XDestroyWindow(newEnv.dpy, newEnv.root);
  freeEnv(&newEnv);
  freeComb(&comb);
  XCloseDisplay(newEnv.dpy);
  }
  return choose_result.opcode;
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
      flag=keycontrol(event.xkey.keycode, env);
      break;

    default:
      arrangeForm(env,comb);
      break;
    }
  }
}
