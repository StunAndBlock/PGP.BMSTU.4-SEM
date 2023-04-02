#include "W21.h"
#include "stdio.h"
#include "stdlib.h"
#define TRUE_ROOT 0
#define ROOT 1
unsigned char checkForOverlap(unsigned char flag, int lastVisibilityState,
                              dArr* truePos,winHandl* newEnv, XEvent *ev) {
  if (flag != 3) {
    inform("MOTION DID NOT PERFORM ->", 1);

  } else {
    XUnmapWindow(newEnv->dpy,newEnv->selection);
  }
  return 1;
}

unsigned char motion(XEvent *ev, winHandl *newEnv, dArr *truePos) {
    if (ev->xmotion.state & Button1Mask ) {
      XWindowChanges new;
  void *trashPointer = malloc(sizeof(int) + sizeof(Window));
  int XY[2][2];
  XTranslateCoordinates(newEnv->dpy, DefaultRootWindow(newEnv->dpy),
                        newEnv->root, 0, 0, &XY[TRUE_ROOT][X],
                        &XY[TRUE_ROOT][Y], trashPointer);
  XQueryPointer(newEnv->dpy, ev->xbutton.window, trashPointer, trashPointer,
                &XY[ROOT][X], &XY[ROOT][Y], trashPointer, trashPointer,
                trashPointer);



       if(XY[TRUE_ROOT][X]+XY[ROOT][X]-truePos[0].box[X]>0 && XY[TRUE_ROOT][Y]+XY[ROOT][Y]-truePos[0].box[Y]<0){
          //XDrawRectangle(newEnv->dpy,newEnv->root,newEnv->gc[1],truePos[0].box[X],truePos[1].box[Y],truePos[1].box[X]-truePos[0].box[X],truePos[0].box[Y]-truePos[1].box[Y]);
          new.x=truePos[0].box[X];
          new.y=XY[TRUE_ROOT][Y]+XY[ROOT][Y];
          new.width=XY[TRUE_ROOT][X]+XY[ROOT][X]-truePos[0].box[X];
          new.height=truePos[0].box[Y]-XY[TRUE_ROOT][Y]-XY[ROOT][Y];
          XConfigureWindow(newEnv->dpy,newEnv->selection,(CWX | CWY | CWHeight | CWWidth),&new);
          XDrawRectangle(newEnv->dpy,newEnv->selection,newEnv->gc[0],2,2,new.width-4,new.height-4);
        } else if (XY[TRUE_ROOT][X]+XY[ROOT][X]-truePos[0].box[X]<0 && XY[TRUE_ROOT][Y]+XY[ROOT][Y]-truePos[0].box[Y]<0){
          new.x=XY[TRUE_ROOT][X]+XY[ROOT][X];
          new.y=XY[TRUE_ROOT][Y]+XY[ROOT][Y];
          new.width=truePos[0].box[X]-XY[TRUE_ROOT][X]-XY[ROOT][X];
          new.height=truePos[0].box[Y]-XY[TRUE_ROOT][Y]-XY[ROOT][Y];
          XConfigureWindow(newEnv->dpy,newEnv->selection,(CWX | CWY | CWHeight | CWWidth),&new);
          XDrawRectangle(newEnv->dpy,newEnv->selection,newEnv->gc[0],2,2,new.width-4,new.height-4);
        } else if (XY[TRUE_ROOT][X]+XY[ROOT][X]-truePos[0].box[X]<0 && XY[TRUE_ROOT][Y]+XY[ROOT][Y]-truePos[0].box[Y]>0){
          new.x=XY[TRUE_ROOT][X]+XY[ROOT][X];
          new.y=truePos[0].box[Y];
          new.width=truePos[0].box[X]-XY[TRUE_ROOT][X]-XY[ROOT][X];
          new.height=XY[TRUE_ROOT][Y]+XY[ROOT][Y]-truePos[0].box[Y];
          XConfigureWindow(newEnv->dpy,newEnv->selection,(CWX | CWY | CWHeight | CWWidth),&new);
          XDrawRectangle(newEnv->dpy,newEnv->selection,newEnv->gc[0],2,2,new.width-4,new.height-4);
        } else if (XY[TRUE_ROOT][X]+XY[ROOT][X]-truePos[0].box[X]>0 && XY[TRUE_ROOT][Y]+XY[ROOT][Y]-truePos[0].box[Y]>0){
          new.x=truePos[0].box[X];
          new.y=truePos[0].box[Y];
          new.width=XY[TRUE_ROOT][X]+XY[ROOT][X]-truePos[0].box[X];
          new.height=XY[TRUE_ROOT][Y]+XY[ROOT][Y]-truePos[0].box[Y];
          XConfigureWindow(newEnv->dpy,newEnv->selection,(CWX | CWY | CWWidth | CWHeight),&new);
          XDrawRectangle(newEnv->dpy,newEnv->selection,newEnv->gc[0],2,2,new.width-4,new.height-4);
        }

XMapWindow(newEnv->dpy, newEnv->selection);
  /*XDrawLine(newEnv->dpy,newEnv->selection,newEnv->gc[1],truePos[0].box[X],truePos[0].box[Y],truePos[1].box[X],truePos[0].box[Y]); //bottom line errase
  XDrawLine(newEnv->dpy,newEnv->selection,newEnv->gc[1],truePos[0].box[X],truePos[0].box[Y],truePos[0].box[X],truePos[1].box[Y]); //left line errase
  XDrawLine(newEnv->dpy,newEnv->selection,newEnv->gc[1],truePos[0].box[X],truePos[1].box[Y],truePos[1].box[X],truePos[1].box[Y]); //top line errase
  XDrawLine(newEnv->dpy,newEnv->selection,newEnv->gc[1],truePos[1].box[X],truePos[0].box[Y],truePos[1].box[X],truePos[1].box[Y]); // right line errase
  
  XDrawLine(newEnv->dpy,newEnv->selection,newEnv->gc[0],truePos[0].box[X],truePos[0].box[Y],XY[TRUE_ROOT][X]+XY[ROOT][X],truePos[0].box[Y]); //bottom line draw
  XDrawLine(newEnv->dpy,newEnv->selection,newEnv->gc[0],truePos[0].box[X],truePos[0].box[Y],truePos[0].box[X],XY[TRUE_ROOT][Y]+XY[ROOT][Y]); //left line draw
  XDrawLine(newEnv->dpy,newEnv->selection,newEnv->gc[0],truePos[0].box[X],XY[TRUE_ROOT][Y]+XY[ROOT][Y],XY[TRUE_ROOT][X]+XY[ROOT][X],XY[TRUE_ROOT][Y]+XY[ROOT][Y]); //top line draw
  XDrawLine(newEnv->dpy,newEnv->selection,newEnv->gc[0],XY[TRUE_ROOT][X]+XY[ROOT][X],truePos[0].box[Y],XY[TRUE_ROOT][X]+XY[ROOT][X],XY[TRUE_ROOT][Y]+XY[ROOT][Y]); // right line drawn */
  // XDrawRectangle(newEnv->dpy,newEnv->root,newEnv->gc[0],truePos[0].box[X],XY[TRUE_ROOT][Y]+XY[ROOT][Y],XY[TRUE_ROOT][X]+XY[ROOT][X]-truePos[0].box[X],10);
   fprintf(stderr,"{%d %d} {%d %d}\n",truePos[0].box[X],truePos[0].box[Y],XY[TRUE_ROOT][X]+XY[ROOT][X],XY[TRUE_ROOT][Y]+XY[ROOT][Y]);
  free(trashPointer);
  truePos[1].box[X]=XY[TRUE_ROOT][X]+XY[ROOT][X];
  truePos[1].box[Y]=XY[TRUE_ROOT][Y]+XY[ROOT][Y];
  }
  
  return 3;
}

unsigned char savePointerAttachmentPositionifNotRoot(XEvent *ev, dArr *truePos,
                                                     winHandl *newEnv) {

  if (ev->xbutton.window == newEnv->root) {
    truePos[0].box[X] = ev->xbutton.x;
    truePos[0].box[Y] = ev->xbutton.y;
    
    truePos[1].box[X]=truePos[0].box[X];truePos[1].box[Y]=truePos[0].box[Y];
    fprintf(stderr,"{%d %d}\n",truePos[0].box[X],truePos[0].box[Y]);
    return 2;
  }
  return 128;
}