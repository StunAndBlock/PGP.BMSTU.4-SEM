#include "8S.h"
#include "stdio.h"
#define TRUE_ROOT 0
#define ROOT 1
unsigned char addToRegion(unsigned char flag,
                        dArr *truePos, winHandl *newEnv,int regionNumber) {
  if ( flag == 3) {
 memoryAllocator(newEnv,regionNumber);
    XWindowAttributes xwa;
    XSetWindowAttributes attr;
    int scr = DefaultScreen(newEnv->dpy);
    int depth = DefaultDepth(newEnv->dpy, scr);

    attr.override_redirect = False;
    attr.background_pixel=0XABCDEF;
    attr.event_mask = (ButtonPressMask | ButtonReleaseMask | KeyPressMask|VisibilityChangeMask);

    XGetWindowAttributes(newEnv->dpy, newEnv->selection, &xwa);

    newEnv->regs[regionNumber].wins[newEnv->regs[regionNumber].winCount-1] =
        XCreateWindow(newEnv->dpy, newEnv->root, xwa.x, xwa.y, xwa.width,
                      xwa.height, 0, depth, InputOutput, CopyFromParent,
                      (CWOverrideRedirect | CWBackPixel| CWEventMask), &attr);
    XUnmapWindow(newEnv->dpy, newEnv->selection);

    XMapWindow(newEnv->dpy,
               newEnv->regs[regionNumber].wins[newEnv->regs[regionNumber].winCount-1]);
  } 
  return 1;
}

unsigned char motion(XEvent *ev, winHandl *newEnv, dArr *truePos) {
  if (ev->xmotion.state & Button1Mask) {
    XWindowChanges new;
    void *trashPointer = malloc(sizeof(int) + sizeof(Window));
    int XY[2][2];
    XTranslateCoordinates(newEnv->dpy, DefaultRootWindow(newEnv->dpy),
                          newEnv->root, 0, 0, &XY[TRUE_ROOT][X],
                          &XY[TRUE_ROOT][Y], trashPointer);
    XQueryPointer(newEnv->dpy, ev->xbutton.window, trashPointer, trashPointer,
                  &XY[ROOT][X], &XY[ROOT][Y], trashPointer, trashPointer,
                  trashPointer);

    if (XY[TRUE_ROOT][X] + XY[ROOT][X] - truePos[0].box[X] > 0 &&
        XY[TRUE_ROOT][Y] + XY[ROOT][Y] - truePos[0].box[Y] < 0) {
      // XDrawRectangle(newEnv->dpy,newEnv->root,newEnv->gc[1],truePos[0].box[X],truePos[1].box[Y],truePos[1].box[X]-truePos[0].box[X],truePos[0].box[Y]-truePos[1].box[Y]);
      new.x = truePos[0].box[X];
      new.y = XY[TRUE_ROOT][Y] + XY[ROOT][Y];
      new.width = XY[TRUE_ROOT][X] + XY[ROOT][X] - truePos[0].box[X];
      new.height = truePos[0].box[Y] - XY[TRUE_ROOT][Y] - XY[ROOT][Y];
      XConfigureWindow(newEnv->dpy, newEnv->selection,
                       (CWX | CWY | CWHeight | CWWidth), &new);
      XDrawRectangle(newEnv->dpy, newEnv->selection, newEnv->gc[0], 2, 2,
                     new.width - 4, new.height - 4);
    } else if (XY[TRUE_ROOT][X] + XY[ROOT][X] - truePos[0].box[X] < 0 &&
               XY[TRUE_ROOT][Y] + XY[ROOT][Y] - truePos[0].box[Y] < 0) {
      new.x = XY[TRUE_ROOT][X] + XY[ROOT][X];
      new.y = XY[TRUE_ROOT][Y] + XY[ROOT][Y];
      new.width = truePos[0].box[X] - XY[TRUE_ROOT][X] - XY[ROOT][X];
      new.height = truePos[0].box[Y] - XY[TRUE_ROOT][Y] - XY[ROOT][Y];
      XConfigureWindow(newEnv->dpy, newEnv->selection,
                       (CWX | CWY | CWHeight | CWWidth), &new);
      XDrawRectangle(newEnv->dpy, newEnv->selection, newEnv->gc[0], 2, 2,
                     new.width - 4, new.height - 4);
    } else if (XY[TRUE_ROOT][X] + XY[ROOT][X] - truePos[0].box[X] < 0 &&
               XY[TRUE_ROOT][Y] + XY[ROOT][Y] - truePos[0].box[Y] > 0) {
      new.x = XY[TRUE_ROOT][X] + XY[ROOT][X];
      new.y = truePos[0].box[Y];
      new.width = truePos[0].box[X] - XY[TRUE_ROOT][X] - XY[ROOT][X];
      new.height = XY[TRUE_ROOT][Y] + XY[ROOT][Y] - truePos[0].box[Y];
      XConfigureWindow(newEnv->dpy, newEnv->selection,
                       (CWX | CWY | CWHeight | CWWidth), &new);
      XDrawRectangle(newEnv->dpy, newEnv->selection, newEnv->gc[0], 2, 2,
                     new.width - 4, new.height - 4);
    } else if (XY[TRUE_ROOT][X] + XY[ROOT][X] - truePos[0].box[X] > 0 &&
               XY[TRUE_ROOT][Y] + XY[ROOT][Y] - truePos[0].box[Y] > 0) {
      new.x = truePos[0].box[X];
      new.y = truePos[0].box[Y];
      new.width = XY[TRUE_ROOT][X] + XY[ROOT][X] - truePos[0].box[X];
      new.height = XY[TRUE_ROOT][Y] + XY[ROOT][Y] - truePos[0].box[Y];
      XConfigureWindow(newEnv->dpy, newEnv->selection,
                       (CWX | CWY | CWWidth | CWHeight), &new);
      XDrawRectangle(newEnv->dpy, newEnv->selection, newEnv->gc[0], 2, 2,
                     new.width - 4, new.height - 4);
    }

    XMapWindow(newEnv->dpy, newEnv->selection);
    XRaiseWindow(newEnv->dpy, newEnv->selection);
    free(trashPointer);
    truePos[1].box[X] = XY[TRUE_ROOT][X] + XY[ROOT][X];
    truePos[1].box[Y] = XY[TRUE_ROOT][Y] + XY[ROOT][Y];
  }

  return 3;
}

unsigned char savePAP(XEvent *ev, dArr *truePos, winHandl *newEnv) {
  if (ev->xbutton.window == newEnv->root) {
    truePos[0].box[X] = ev->xbutton.x;
    truePos[0].box[Y] = ev->xbutton.y;

    truePos[1].box[X] = truePos[0].box[X];
    truePos[1].box[Y] = truePos[0].box[Y];
    // fprintf(stderr,"{%d %d}\n",truePos[0].box[X],truePos[0].box[Y]);
    return 2;
  }
  return 1;
}

void memoryAllocator(winHandl* newEnv,int RegN) {
  if(newEnv->regs[RegN].winCount){
      Window* stash=(Window*)realloc(newEnv->regs[RegN].wins,++(newEnv->regs[RegN].winCount));
      if(stash==NULL){
        exit(-1);
      }
      newEnv->regs[RegN].wins=stash;
    } else {
      newEnv->regs[RegN].wins=(Window*)malloc(sizeof(Window)*(++(newEnv->regs[RegN].winCount)));
      
    }
    fprintf(stderr,"WINCOUNT:::%d)",newEnv->regs[RegN].winCount);
}



void taintedCorrect(Window curWin,int state,Window** tainted,unsigned short *taintedCount){
if (!(*taintedCount)){
  *tainted=(Window*)malloc(sizeof(Window));
  (*taintedCount)++;
  *tainted[0]=curWin;
 // fprintf(stderr,"DELETED\n");
} else {
      int pos=findWin(curWin,tainted,*taintedCount);
     fprintf(stderr,"FOUND:<%d>\n",pos);
      if(pos!=-1 && !state){
      for (unsigned short i=pos ; i < --(*taintedCount); i++) {
    *tainted[i] = *tainted[i+1];
      }
  if (!(*taintedCount)){
    free(*tainted);
    return;
  }

      } else if (pos){
          Window *stash = (Window *)realloc(*tainted,
                              sizeof(Window) * (++(*taintedCount)));
    if (stash == NULL) {
    fprintf(stderr, "MEMORY ERROR, informed by <taintedCorrect> function");
    exit(-1);
      }
      *tainted= stash;
      *tainted[(*taintedCount)-1]=curWin;
  }

}
}


int findWin(Window aim,Window** tainted,unsigned short taintedCount){
for (int i = 0; i < taintedCount; i++) {
    if (aim==*tainted[i])
    return i; 
}
return -1;
}
int findRegion(Window* tainted,unsigned short taintedCount,winHandl* newEnv){
  int c[newEnv->regsCount];
  unsigned short f=0;
  for(unsigned short i=0;i<taintedCount;i++){
      for(unsigned short j=0;j<newEnv->regsCount;j++){
        for(unsigned short k=0;k<newEnv->regs[j].winCount;k++){
            if(tainted[i]==newEnv->regs[j].wins[k])
            c[f++]=j;
        }
      }
  }
  for(int i=0;i<f;i++)
  fprintf(stderr,"{%d}",c[i]);
  fprintf(stderr,"\n");
  return c[0];
}
void createRegion(winHandl *newEnv){
    newEnv->regs=(_Region*)malloc(sizeof(_Region));
    newEnv->regs[newEnv->regsCount].winCount=0;
    newEnv->regs[(newEnv->regsCount)++].connections=NULL;
}

int addRegion(winHandl *newEnv){
  _Region* stash=( _Region*)realloc(newEnv->regs,++(newEnv->regsCount));
  if (stash==NULL){
     fprintf(stderr, "MEMORY ERROR, informed by <addRegion> function");
    exit(-1);
  }
  newEnv->regs=stash;
  newEnv->regs[(newEnv->regsCount)-1].winCount=0;
  newEnv->regs[(newEnv->regsCount)-1].connections=NULL;
}

unsigned char deleteRegion(){
  return 4;
}