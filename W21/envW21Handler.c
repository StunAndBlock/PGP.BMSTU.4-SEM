#include "W21.h"
#include "X11/Xutil.h"
#include <stdio.h>
#include <stdlib.h>

void createEnv(winHandl *newEnv, envParams *newEnvParams, char **args) {
  newEnv->dpy = XOpenDisplay(NULL);
  newEnvParams->boxSizes =
      (dArr *)malloc(sizeof(dArr) * newEnvParams->boxCount);
  newEnvParams->boxPoses =
      (dArr *)malloc(sizeof(dArr) * newEnvParams->boxCount);
  dArr rootWindowSize = parseBoxes(args, newEnvParams, newEnv->dpy);
  if (newEnvParams->boxCount == 0) {
    free(newEnvParams->boxSizes);
    free(newEnvParams->boxPoses);
    inform("nothing to create\n", -1);
  }

  int scr = DefaultScreen(newEnv->dpy);
  int depth = DefaultDepth(newEnv->dpy, scr);
  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(newEnv->dpy, scr);
  attr.event_mask = (ButtonPressMask);
  newEnv->root = XCreateWindow(
      newEnv->dpy, DefaultRootWindow(newEnv->dpy), 100, 500,
      rootWindowSize.box[X], rootWindowSize.box[Y], 0, depth, InputOutput,
      CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  hint.flags = (PMinSize | PMaxSize | PPosition);
  hint.min_width = hint.max_width = rootWindowSize.box[X];
  hint.min_height = hint.max_height = rootWindowSize.box[Y];
  hint.x = 100;
  hint.y = 100;
  XSetNormalHints(newEnv->dpy, newEnv->root, &hint);

  newEnv->boxes = (Window *)malloc(sizeof(Window) * newEnvParams->boxCount);
  attr.override_redirect = True;
  attr.event_mask = (ButtonPressMask | ButtonReleaseMask | ButtonMotionMask |
                     VisibilityChangeMask);
  attr.background_pixel = 0xFF0000;
  for (unsigned short i = 0; i < newEnvParams->boxCount; i++) {
    newEnv->boxes[i] = XCreateWindow(
        newEnv->dpy, newEnv->root, newEnvParams->boxPoses[i].box[X],
        newEnvParams->boxPoses[i].box[Y], newEnvParams->boxSizes[i].box[X],
        newEnvParams->boxSizes[i].box[Y], 1, depth, InputOutput, CopyFromParent,
        (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  }

  XMapWindow(newEnv->dpy, newEnv->root);
  XMapSubwindows(newEnv->dpy, newEnv->root);
  free(newEnvParams->boxSizes);
  free(newEnvParams->boxPoses);
}

dArr parseBoxes(char **args, envParams *newEnvParams, Display *dpy) {
  unsigned int *ptr = (unsigned int *)malloc(sizeof(unsigned int));
  int scr = DefaultScreen(dpy);
  int maxWidth = DisplayWidth(dpy, scr);
  int maxHeight = DisplayHeight(dpy, scr);
  dArr rootWindowSize;
  rootWindowSize.box[X] = 0;
  rootWindowSize.box[Y] = 0;
  unsigned int X_V = 0;
  unsigned int Y_V = 0;
  unsigned short j = 1;
  for (unsigned short i = 1; i <= newEnvParams->boxCount; i++, j++) {
    switch (XParseGeometry(args[i - 1], ptr, ptr, &X_V, &Y_V)) {
    case 0:
      newEnvParams->boxSizes[j - 1].box[X] = uItos(X_V);
      newEnvParams->boxSizes[j - 1].box[Y] = uItos(Y_V);
      inform("№", 1);
      fprintf(stderr, "<%d>", i);
      inform("\t\t\t\t\tCANNOT BE PARSED\t\t\t  ->SKIPPED\n", 1);
      j--;

      break;
    case 4:
      newEnvParams->boxSizes[j - 1].box[X] = uItos(X_V);
      inform("№", 1);
      fprintf(stderr, "<%d> %dxE", i, newEnvParams->boxSizes[j - 1].box[X]);

      newEnvParams->boxSizes[j - 1].box[Y] =
          newEnvParams->boxSizes[j - 1].box[X];
      fprintf(stderr, "->%dx%d", newEnvParams->boxSizes[j - 1].box[X],
              newEnvParams->boxSizes[j - 1].box[Y]);
      inform("\tWARNING Y IS EMPTY, TRYING TO MAKE A SQUARE", 1);
      if (newEnvParams->boxSizes[j - 1].box[Y]) {
        if (rootWindowSize.box[Y] + newEnvParams->boxSizes[j - 1].box[Y] + 2 <
                maxHeight &&
            rootWindowSize.box[X] + newEnvParams->boxSizes[j - 1].box[X] + 2 <
                maxWidth) {
          inform("\t\t\t  ->ACCEPTED\n", 1);

          newEnvParams->boxPoses[j - 1].box[Y] = 0;
          newEnvParams->boxPoses[j - 1].box[X] = rootWindowSize.box[X];
          rootWindowSize.box[Y] += newEnvParams->boxSizes[j - 1].box[Y] + 2;
          rootWindowSize.box[X] += newEnvParams->boxSizes[j - 1].box[X] + 2;
        } else {
          inform("\t\t\t\t\t\tBOX OUT OF BOUNDS\t  ->SKIPPED\n", 1);
          j--;
        }
      } else {
        inform("\tZERO VALUE\t  ->SKIPPED\n", 1);
        j--;
      }
      break;
    case 8:
      newEnvParams->boxSizes[j - 1].box[Y] = uItos(Y_V);
      inform("№", 1);
      fprintf(stderr, "<%d> Ex%d", i, newEnvParams->boxSizes[j - 1].box[Y]);

      newEnvParams->boxSizes[j - 1].box[X] =
          newEnvParams->boxSizes[j - 1].box[Y];
      fprintf(stderr, "->%dx%d", newEnvParams->boxSizes[j - 1].box[X],
              newEnvParams->boxSizes[j - 1].box[Y]);
      inform("\tWARNING X IS EMPTY, TRYING TO MAKE A SQUARE", 1);
      if (newEnvParams->boxSizes[j - 1].box[X]) {
        if (rootWindowSize.box[Y] + newEnvParams->boxSizes[j - 1].box[Y] + 2 <
                maxHeight &&
            rootWindowSize.box[X] + newEnvParams->boxSizes[j - 1].box[X] + 2 <
                maxWidth) {
          inform("\t\t\t  ->ACCEPTED\n", 1);

          newEnvParams->boxPoses[j - 1].box[Y] = 0;
          newEnvParams->boxPoses[j - 1].box[X] = rootWindowSize.box[X];
          rootWindowSize.box[Y] += newEnvParams->boxSizes[j - 1].box[Y] + 2;
          rootWindowSize.box[X] += newEnvParams->boxSizes[j - 1].box[X] + 2;
        } else {
          inform("\t\t\t\t\t\tBOX OUT OF BOUNDS\t  ->SKIPPED\n", 1);
          j--;
        }
      } else {
        inform("\tZERO VALUE\t  ->SKIPPED\n", 1);
        j--;
      }
      break;
    case 12:
      newEnvParams->boxSizes[j - 1].box[X] = uItos(X_V);
      newEnvParams->boxSizes[j - 1].box[Y] = uItos(Y_V);
      inform("№", 1);
      fprintf(stderr, "<%d> %dx%d", i, newEnvParams->boxSizes[j - 1].box[X],
              newEnvParams->boxSizes[j - 1].box[Y]);
      if (newEnvParams->boxSizes[j - 1].box[X] &&
          newEnvParams->boxSizes[j - 1].box[Y]) {
        if (rootWindowSize.box[Y] + newEnvParams->boxSizes[j - 1].box[Y] + 2 <
                maxHeight &&
            rootWindowSize.box[X] + newEnvParams->boxSizes[j - 1].box[X] + 2 <
                maxWidth) {
          inform("\t\t\t\t\t\t\t\t\t  ->ACCEPTED\n", 1);

          newEnvParams->boxPoses[j - 1].box[Y] = 0;
          newEnvParams->boxPoses[j - 1].box[X] = rootWindowSize.box[X];

          rootWindowSize.box[Y] += newEnvParams->boxSizes[j - 1].box[Y] + 2;
          rootWindowSize.box[X] += newEnvParams->boxSizes[j - 1].box[X] + 2;
        } else {
          inform("\t\t\t\t\t\tBOX OUT OF BOUNDS\t  ->SKIPPED\n", 1);
          j--;
        }
      } else {
        inform("\t\t\t\t\t\t\tZERO VALUE\t  ->SKIPPED\n", 1);
        j--;
      }
      break;
    default:
      break;
    }
  }
  j--;
  free(ptr);
  newEnvParams->boxCount = j;
  return rootWindowSize;
}

unsigned short uItos(unsigned int value) {
  unsigned short ret = value;
  if (ret != value)
    inform("value conversion error", -1);
  return ret;
}
