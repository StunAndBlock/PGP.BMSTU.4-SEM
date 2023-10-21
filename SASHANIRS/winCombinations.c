#include "combinations.h"
#include <X11/Xutil.h>
#include <stdlib.h>

void createEnv(winEnv *env) {

  env->dpy = XOpenDisplay(NULL);
  int scr = DefaultScreen(env->dpy);
  int depth = DefaultDepth(env->dpy, scr);
  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  XFontStruct *fn; /* Font parameters structure */
  char *fontname = "-bitstream-courier 10 pitch-medium-r-normal--50-0-0-0-m-0-iso10646-1";
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
  env->cell.x = (CELL_SIZE_FORM - fn->max_bounds.width) / 2;
  env->cell.y =
      CELL_SIZE_FORM / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;

  env->root =
      XCreateWindow(env->dpy, DefaultRootWindow(env->dpy), 300, 300, WIN_W,
                    WIN_H, 0, depth, InputOutput, CopyFromParent,
                    (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  hint.flags = (PMinSize | PMaxSize | PPosition);
  hint.min_width = hint.max_width = WIN_W;
  hint.min_height = hint.max_height = WIN_H;
  hint.x = 300;
  hint.y = 300;
  attr.override_redirect = False;
  attr.background_pixel = BlackPixel(env->dpy, scr);
  attr.event_mask = (ButtonPressMask);
  size_t dy=OFFSET;
  for(size_t i=0; i<CELL_COUNT;i++,dy+=CELL_SIZE_FORM+OFFSET){
    env->forms[i]=XCreateWindow(env->dpy, env->root, OFFSET, dy, CELL_SIZE_FORM,
                    CELL_SIZE_FORM, 0, depth, InputOutput, CopyFromParent,
                    (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  }

  XSetNormalHints(env->dpy, env->root, &hint);
  XMapWindow(env->dpy,env->root);
  //XMapSubwindows(env->dpy,env->root);
  XFreeFont(env->dpy, fn);
}

void freeEnv(winEnv *env) {
  XFreeGC(env->dpy, env->gc[1]);

}
