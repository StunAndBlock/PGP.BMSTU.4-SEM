#include "W07.h"
#include <X11/Xutil.h>
#include <stdlib.h>

void createEnv(winEnv *env) {

  env->dpy = XOpenDisplay(NULL);
  int scr = DefaultScreen(env->dpy);
  int depth = DefaultDepth(env->dpy, scr);
  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  XFontStruct *fn; /* Font parameters structure */
  char *fontname = "9x15";
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(env->dpy, scr);
  attr.event_mask = (ExposureMask | KeyPressMask);

  env->gc[0] = DefaultGC(env->dpy, scr);

  /* Font custom */
  if ((fn = XLoadQueryFont(env->dpy, fontname)) == NULL)
    exit(-1);
  XSetFont(env->dpy, env->gc[0], fn->fid);

  env->cell.width = fn->max_bounds.width;
  env->cell.height = fn->max_bounds.ascent + fn->max_bounds.descent;
  env->cell.x = (CELL_SIZE - fn->max_bounds.width) / 2;
  env->cell.y =
      CELL_SIZE / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;

  env->root =
      XCreateWindow(env->dpy, DefaultRootWindow(env->dpy), 300, 300, WIN_W,
                    WIN_H, 0, depth, InputOutput, CopyFromParent,
                    (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  hint.flags = (PMinSize | PMaxSize | PPosition);
  hint.min_width = hint.max_width = WIN_W;
  hint.min_height = hint.max_height = WIN_H;
  hint.x = 300;
  hint.y = 300;
  XSetNormalHints(env->dpy, env->root, &hint);

  env->cellArr = (Window *)malloc(sizeof(Window) * CELL_COUNT);
  env->info = (Window *)malloc(sizeof(Window) * 6);
  unsigned short dx = 2;
  attr.override_redirect = True;
  attr.event_mask = (ButtonPressMask | KeyPressMask);
  attr.background_pixel = WhitePixel(env->dpy, scr);
  for (unsigned short i = 0; i < CELL_COUNT; i++, dx += OFFSET + CELL_SIZE) {
    env->cellArr[i] =
        XCreateWindow(env->dpy, env->root, dx, 2, CELL_SIZE, CELL_SIZE, 1,
                      depth, InputOutput, CopyFromParent,
                      (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  }
  dx = 2;
  attr.override_redirect = True;
  attr.background_pixel = WhitePixel(env->dpy, scr);
  for (unsigned short i = 0; i < 6; i++, dx += OFFSET + CELL_SIZE) {
    env->info[i] = XCreateWindow(env->dpy, env->root, dx,
                                 CELL_SIZE + OFFSET + 2, CELL_SIZE, CELL_SIZE,
                                 1, depth, InputOutput, CopyFromParent,
                                 (CWOverrideRedirect | CWBackPixel), &attr);
  }
  attr.override_redirect = True;
  attr.background_pixel = WhitePixel(env->dpy, scr);
  attr.event_mask = (ButtonPressMask);
  env->exit = XCreateWindow(
      env->dpy, env->root, WIN_W - OFFSET - CELL_SIZE, 2 + CELL_SIZE + OFFSET,
      CELL_SIZE, CELL_SIZE, 1, depth, InputOutput, CopyFromParent,
      (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  XMapWindow(env->dpy, env->root);
  XMapSubwindows(env->dpy, env->root);
  env->gc[1] = XCreateGC(env->dpy, env->root, 0, 0);
  XCopyGC(env->dpy, env->gc[0], GCFont, env->gc[1]);
  XSetForeground(env->dpy, env->gc[1],
                 WhitePixel(env->dpy, scr)); /* WhitePixel(dpy, src)); */
  XFreeFont(env->dpy, fn);
}

void freeEnv(winEnv *env) {
  XFreeGC(env->dpy, env->gc[1]);
  free(env->cellArr);
  free(env->info);
}
