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
        fprintf(stderr,"((%d %d))\n",truePos[1].box[X]-truePos[0].box[X],truePos[1].box[Y]-truePos[0].box[Y]);
        if(truePos[1].box[X]-truePos[0].box[X]>0 && truePos[1].box[Y]-truePos[0].box[Y]<0){
          XDrawRectangle(newEnv->dpy,newEnv->root,newEnv->gc[1],truePos[0].box[X],truePos[1].box[Y],truePos[1].box[X]-truePos[0].box[X],truePos[0].box[Y]-truePos[1].box[Y]);
        } else if (truePos[1].box[X]-truePos[0].box[X]<0 && truePos[1].box[Y]-truePos[0].box[Y]<0){
          XDrawRectangle(newEnv->dpy,newEnv->root,newEnv->gc[1],truePos[1].box[X],truePos[1].box[Y],truePos[0].box[X]-truePos[1].box[X],truePos[0].box[Y]-truePos[1].box[Y]);
        } else if (truePos[1].box[X]-truePos[0].box[X]<0 && truePos[1].box[Y]-truePos[0].box[Y]>0){
          XDrawRectangle(newEnv->dpy,newEnv->root,newEnv->gc[1],truePos[1].box[X],truePos[0].box[Y],truePos[0].box[X]-truePos[1].box[X],truePos[1].box[Y]-truePos[0].box[Y]);
        } else {
          XDrawRectangle(newEnv->dpy,newEnv->root,newEnv->gc[1],truePos[0].box[X],truePos[0].box[Y],truePos[1].box[X]-truePos[0].box[X],truePos[1].box[Y]-truePos[0].box[Y]);
        }
  }
  return 1;
}

unsigned char motion(XEvent *ev, winHandl *newEnv, dArr *truePos) {
    if (ev->xmotion.state & Button1Mask ) {
  void *trashPointer = malloc(sizeof(int) + sizeof(Window));
  int XY[2][2];
  XTranslateCoordinates(newEnv->dpy, DefaultRootWindow(newEnv->dpy),
                        newEnv->root, 0, 0, &XY[TRUE_ROOT][X],
                        &XY[TRUE_ROOT][Y], trashPointer);
  XQueryPointer(newEnv->dpy, ev->xbutton.window, trashPointer, trashPointer,
                &XY[ROOT][X], &XY[ROOT][Y], trashPointer, trashPointer,
                trashPointer);
  XDrawLine(newEnv->dpy,newEnv->root,newEnv->gc[1],truePos[0].box[X],truePos[0].box[Y],truePos[1].box[X],truePos[0].box[Y]); //bottom line errase
  XDrawLine(newEnv->dpy,newEnv->root,newEnv->gc[1],truePos[0].box[X],truePos[0].box[Y],truePos[0].box[X],truePos[1].box[Y]); //left line errase
  XDrawLine(newEnv->dpy,newEnv->root,newEnv->gc[1],truePos[0].box[X],truePos[1].box[Y],truePos[1].box[X],truePos[1].box[Y]); //top line errase
  XDrawLine(newEnv->dpy,newEnv->root,newEnv->gc[1],truePos[1].box[X],truePos[0].box[Y],truePos[1].box[X],truePos[1].box[Y]); // right line errase
  
  XDrawLine(newEnv->dpy,newEnv->root,newEnv->gc[0],truePos[0].box[X],truePos[0].box[Y],XY[TRUE_ROOT][X]+XY[ROOT][X],truePos[0].box[Y]); //bottom line draw
  XDrawLine(newEnv->dpy,newEnv->root,newEnv->gc[0],truePos[0].box[X],truePos[0].box[Y],truePos[0].box[X],XY[TRUE_ROOT][Y]+XY[ROOT][Y]); //left line draw
  XDrawLine(newEnv->dpy,newEnv->root,newEnv->gc[0],truePos[0].box[X],XY[TRUE_ROOT][Y]+XY[ROOT][Y],XY[TRUE_ROOT][X]+XY[ROOT][X],XY[TRUE_ROOT][Y]+XY[ROOT][Y]); //top line draw
  XDrawLine(newEnv->dpy,newEnv->root,newEnv->gc[0],XY[TRUE_ROOT][X]+XY[ROOT][X],truePos[0].box[Y],XY[TRUE_ROOT][X]+XY[ROOT][X],XY[TRUE_ROOT][Y]+XY[ROOT][Y]); // right line draw
  // XDrawRectangle(newEnv->dpy,newEnv->root,newEnv->gc[0],truePos[0].box[X],XY[TRUE_ROOT][Y]+XY[ROOT][Y],XY[TRUE_ROOT][X]+XY[ROOT][X]-truePos[0].box[X],10);
   fprintf(stderr,"{%d %d} {%d %d}\n",truePos[0].box[X],truePos[0].box[Y],XY[TRUE_ROOT][X]+XY[ROOT][X],XY[TRUE_ROOT][Y]+XY[ROOT][Y]);
  free(trashPointer);
  truePos[1].box[X]=XY[TRUE_ROOT][X]+XY[ROOT][X];
  truePos[1].box[Y]=XY[TRUE_ROOT][Y]+XY[ROOT][Y];
  }
  
  return 3;
}

unsigned char savePointerAttachmentPositionifNotRoot(XEvent *ev, dArr *truePos,
                                                     winHandl *newEnv,
                                                     unsigned char l) {

  if (ev->xbutton.window == newEnv->root) {
    truePos[0].box[X] = ev->xbutton.x;
    truePos[0].box[Y] = ev->xbutton.y;
    truePos[1].box[X]=truePos[0].box[X];truePos[1].box[Y]=truePos[0].box[Y];
    fprintf(stderr,"{%d %d}\n",truePos[0].box[X],truePos[0].box[Y]);
    return 2;
  }
  return 128;
}