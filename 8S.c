#include "8S.h"
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
  Window* tainted;
  unsigned short taintedCount=0;
  int lastVisibilityState = 0;
  unsigned char flag = 1; /* exit flag */
  unsigned char state = 0;
  int regionNumber=0;
  while (flag) {
    XNextEvent(newEnv->dpy, &event);
    switch (event.type) {
    case VisibilityNotify:
    taintedCorrect(event.xvisibility.window,event.xvisibility.state,&tainted,&taintedCount);
    fprintf(stderr,"\t\t\t<%d>'\n\n",event.xvisibility.state);
    break;
    case ButtonRelease:

      if (event.xbutton.button == 1 ) {
        if (!newEnv->regsCount){
          createRegion(newEnv);
         
        } else {
                if(!taintedCount){
          regionNumber=addRegion(newEnv);
    
        } else {
          regionNumber=findRegion(tainted,taintedCount,newEnv);
        }
        }

        state = addToRegion(flag, truePos, newEnv,regionNumber);
        if(newEnv->regs[regionNumber].winCount>1)
        taintedCorrect(newEnv->regs[regionNumber].wins[newEnv->regs[regionNumber].winCount-2],0,&tainted,&taintedCount);
        taintedCorrect(newEnv->regs[regionNumber].wins[newEnv->regs[regionNumber].winCount-1],0,&tainted,&taintedCount);
      }
      break;
    case ButtonPress:
      if (event.xbutton.button == 1) {
        flag = savePAP(&event, truePos, newEnv);
      } else if (event.xbutton.button == 3 &&
                 event.xbutton.window != newEnv->root) {
        flag = deleteRegion();
      }
      break;
    case MotionNotify:
      flag = motion(&event, newEnv, truePos);
     // fprintf(stderr,"%d\n",taintedCount);
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
