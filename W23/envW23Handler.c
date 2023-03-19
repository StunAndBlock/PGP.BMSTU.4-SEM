#include "W23.h"
#include "X11/Xutil.h"
#include <stdio.h>
#include <stdlib.h>

void createEnv(winHandl *newEnv, envParams *newEnvParams) {
  newEnv->dpy = XOpenDisplay(NULL);

  XFontStruct *fn; /* Font parameters structure */
  char *fontname = "9x15";
  int scr = DefaultScreen(newEnv->dpy);
  int depth = DefaultDepth(newEnv->dpy, scr);
  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  int maxWidth = DisplayWidth(newEnv->dpy, scr);
  if ((WHBOX + 8) * newEnvParams->boxCount + 2 > maxWidth) {
    fprintf(stderr, "too many words for screen\n");
    exit(-1);
  }
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(newEnv->dpy, scr);
  attr.event_mask = (ExposureMask | KeyPressMask);

  if ((fn = XLoadQueryFont(newEnv->dpy, fontname)) == NULL)
    exit(-1);

  newEnv->cell.width = fn->max_bounds.width;
  newEnv->cell.height = fn->max_bounds.ascent + fn->max_bounds.descent;
  newEnv->cell.x = (WHBOX - fn->max_bounds.width) / 2;
  newEnv->cell.y =
      WHBOX / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;

  newEnv->root =
      XCreateWindow(newEnv->dpy, DefaultRootWindow(newEnv->dpy), 100, 500,
                    (WHBOX + 8) * newEnvParams->boxCount + 2, WHBOX + 4 + 2, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  hint.flags = (PMinSize | PMaxSize | PPosition);
  hint.min_width = hint.max_width = (WHBOX + 8) * newEnvParams->boxCount + 2;
  hint.min_height = hint.max_height = WHBOX + 4 + 2;
  hint.x = 100;
  hint.y = 100;
  XSetNormalHints(newEnv->dpy, newEnv->root, &hint);

  newEnv->boxes = (Window *)malloc(sizeof(Window) * newEnvParams->boxCount);
  newEnv->id =
      (unsigned short *)malloc(sizeof(unsigned short) * newEnvParams->boxCount);
  attr.override_redirect = True;
  attr.event_mask = (ButtonPressMask | ButtonReleaseMask | ButtonMotionMask |
                     VisibilityChangeMask | KeyPressMask );
  attr.background_pixel = 0xFF0000;
  unsigned short dx = 4;
  for (unsigned short i = 0; i < newEnvParams->boxCount; i++, dx += WHBOX + 8) {
    newEnv->boxes[i] =
        XCreateWindow(newEnv->dpy, newEnv->root, dx, 2, WHBOX, WHBOX, 1, depth,
                      InputOutput, CopyFromParent,
                      (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
    newEnv->id[i] = i;
  }

  XMapWindow(newEnv->dpy, newEnv->root);
  XMapSubwindows(newEnv->dpy, newEnv->root);
  ;

  newEnv->gc = XCreateGC(newEnv->dpy, newEnv->root, 0, 0);
  XSetFont(newEnv->dpy, newEnv->gc, fn->fid);
  XSetForeground(newEnv->dpy, newEnv->gc, BlackPixel(newEnv->dpy, scr));
  XFreeFont(newEnv->dpy, fn);
}

void transformArgs(char *arg, envParams *newEnvParams) {
  newEnvParams->reString = (char **)malloc(sizeof(char *));
  char **stash;
  for (newEnvParams->boxCount = 0; *arg; arg++) {
    newEnvParams->reString[newEnvParams->boxCount] =
        (char *)malloc(sizeof(char) * 2);
    newEnvParams->reString[newEnvParams->boxCount][0] = *arg;
    newEnvParams->reString[newEnvParams->boxCount++][1] = '\0';
    stash = realloc(newEnvParams->reString,
                    sizeof(char *) * (newEnvParams->boxCount + 1));
    newEnvParams->reString = stash;
  }
  newEnvParams->boxCount += 2;
}

void freeEnv(winHandl *newEnv, envParams *newEnvParams) {
  for (int i = 0; i < newEnvParams->boxCount - 2; i++) {

    free(newEnvParams->reString[i]);
  }
  free(newEnvParams->reString);
  free(newEnv->boxes);
  free(newEnv->id);
  XFreeGC(newEnv->dpy, newEnv->gc);
}
