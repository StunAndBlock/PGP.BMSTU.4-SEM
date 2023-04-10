#include "R4.h"
#include "stdio.h"
#define TRUE_ROOT 0
#define ROOT 1
unsigned char mapNewBox(unsigned char flag, int lastVisibilityState,
                        dArr *truePos, winHandl *newEnv) {
  if (flag == 3) {
    memoryAllocator(newEnv);
    XWindowAttributes xwa;
    XSetWindowAttributes attr;
    int scr = DefaultScreen(newEnv->dpy);
    int depth = DefaultDepth(newEnv->dpy, scr);

    attr.override_redirect = False;
    attr.background_pixel = 0XABCDEF;
    attr.event_mask = (ButtonPressMask | ButtonReleaseMask |
                        KeyPressMask | VisibilityChangeMask);

    XGetWindowAttributes(newEnv->dpy, newEnv->selection, &xwa);


    newEnv->rectangles[newEnv->rectanglesCount - 1].winBox =
        XCreateWindow(newEnv->dpy, newEnv->root, xwa.x, xwa.y, xwa.width,
                      xwa.height, 0, depth, InputOutput, CopyFromParent,
                      (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
    XUnmapWindow(newEnv->dpy, newEnv->selection);
    XMapWindow(newEnv->dpy,
               newEnv->rectangles[newEnv->rectanglesCount - 1].winBox);

  } else {
    XUnmapWindow(newEnv->dpy, newEnv->selection);
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
      XDrawRectangle(newEnv->dpy, newEnv->selection, newEnv->gc, 2, 2,
                     new.width - 4, new.height - 4);
    } else if (XY[TRUE_ROOT][X] + XY[ROOT][X] - truePos[0].box[X] < 0 &&
               XY[TRUE_ROOT][Y] + XY[ROOT][Y] - truePos[0].box[Y] < 0) {
      new.x = XY[TRUE_ROOT][X] + XY[ROOT][X];
      new.y = XY[TRUE_ROOT][Y] + XY[ROOT][Y];
      new.width = truePos[0].box[X] - XY[TRUE_ROOT][X] - XY[ROOT][X];
      new.height = truePos[0].box[Y] - XY[TRUE_ROOT][Y] - XY[ROOT][Y];
      XConfigureWindow(newEnv->dpy, newEnv->selection,
                       (CWX | CWY | CWHeight | CWWidth), &new);
      XDrawRectangle(newEnv->dpy, newEnv->selection, newEnv->gc, 2, 2,
                     new.width - 4, new.height - 4);
    } else if (XY[TRUE_ROOT][X] + XY[ROOT][X] - truePos[0].box[X] < 0 &&
               XY[TRUE_ROOT][Y] + XY[ROOT][Y] - truePos[0].box[Y] > 0) {
      new.x = XY[TRUE_ROOT][X] + XY[ROOT][X];
      new.y = truePos[0].box[Y];
      new.width = truePos[0].box[X] - XY[TRUE_ROOT][X] - XY[ROOT][X];
      new.height = XY[TRUE_ROOT][Y] + XY[ROOT][Y] - truePos[0].box[Y];
      XConfigureWindow(newEnv->dpy, newEnv->selection,
                       (CWX | CWY | CWHeight | CWWidth), &new);
      XDrawRectangle(newEnv->dpy, newEnv->selection, newEnv->gc, 2, 2,
                     new.width - 4, new.height - 4);
    } else if (XY[TRUE_ROOT][X] + XY[ROOT][X] - truePos[0].box[X] > 0 &&
               XY[TRUE_ROOT][Y] + XY[ROOT][Y] - truePos[0].box[Y] > 0) {
      new.x = truePos[0].box[X];
      new.y = truePos[0].box[Y];
      new.width = XY[TRUE_ROOT][X] + XY[ROOT][X] - truePos[0].box[X];
      new.height = XY[TRUE_ROOT][Y] + XY[ROOT][Y] - truePos[0].box[Y];
      XConfigureWindow(newEnv->dpy, newEnv->selection,
                       (CWX | CWY | CWWidth | CWHeight), &new);
      XDrawRectangle(newEnv->dpy, newEnv->selection, newEnv->gc, 2, 2,
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

void memoryAllocator(winHandl *newEnv) {
  if (!newEnv->rectanglesCount) {
    newEnv->rectangles =
        (env *)malloc(sizeof(env) * (++(newEnv->rectanglesCount)));

  } else {
    env *stashptr = (env *)realloc(newEnv->rectangles,
                                   sizeof(env) * (++(newEnv->rectanglesCount)));
    newEnv->rectangles = stashptr;
  }
  if (newEnv->rectangles == NULL) {
    fprintf(stderr, "MEMORY ERROR, informed by <memomryAllocator> function");
    exit(-1);
  }
}




int findBox(Window winToDel, winHandl *newEnv) {
  for (unsigned short i = 0; i < newEnv->rectanglesCount; i++) {
    if (winToDel == newEnv->rectangles[i].winBox)
      return i;
  }
  return -1;
}
unsigned char deleteBox(unsigned short pos, winHandl *newEnv) {
  XUnmapWindow(newEnv->dpy, newEnv->rectangles[pos].winBox);
  XDestroyWindow(newEnv->dpy, newEnv->rectangles[pos].winBox);
  fprintf(stderr,"<%d>",pos);
  newEnv->rectanglesCount--;
  for (unsigned short i = pos; i < newEnv->rectanglesCount; i++) {
    newEnv->rectangles[i].winBox = newEnv->rectangles[i + 1].winBox;
  
  }
  env *stash = (env *)realloc(newEnv->rectangles,
                              sizeof(env) * (newEnv->rectanglesCount));
  newEnv->rectangles = stash;
  fprintf(stderr,"<%d>",newEnv->rectanglesCount);
  return 4;
}
