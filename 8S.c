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
  int ee=1;
  newEnv->taintedCount=0;
  int lastVisibilityState = 0;
  unsigned char flag = 1; /* exit flag */
  unsigned char state = 0;
  int regionNumber=0;
  while (flag) {
    XNextEvent(newEnv->dpy, &event);
    switch (event.type) {
    case VisibilityNotify:
   
    taintedCorrect(event.xvisibility.window,event.xvisibility.state,newEnv);
    //fprintf(stderr,"\t\t\tV<%d>'\n\n",event.xvisibility.state);
    
    newEnv->regs[regionNumber].head++;
    break;
    case ButtonRelease:

      if (event.xbutton.button == 1 ) {
        if (!newEnv->regsCount){
          createRegion(newEnv);
         
        } else {
                if(!newEnv->taintedCount){
          regionNumber=addRegion(newEnv);
    
        } else {
          regionNumber=findRegion(newEnv);
        }
        }
       
        state = addToRegion(flag, truePos, newEnv,regionNumber);
        if(newEnv->regs[regionNumber].head)
        taintedCorrect(newEnv->regs[regionNumber].wins[newEnv->regs[regionNumber].winCount-1],event.xvisibility.state,newEnv);
         fprintf(stderr,"WINS IN REGION{{%d}}:%d\n",regionNumber,newEnv->regs[regionNumber].winCount);
        newEnv->regs[regionNumber].head=0;
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
