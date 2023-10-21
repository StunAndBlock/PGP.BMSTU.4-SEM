#include "combinations.h"
#include "X11/Xutil.h"
#include "stdlib.h"
#include "math.h"
void createEnv(winEnv *env,Cb* comb) {

  env->dpy = XOpenDisplay(NULL);
  int scr = DefaultScreen(env->dpy);
  int depth = DefaultDepth(env->dpy, scr);
  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(env->dpy, scr);
  attr.event_mask = (ExposureMask | KeyPressMask);

  env->gc_C = DefaultGC(env->dpy, scr);
  env->gc_Num = XCreateGC(env->dpy,RootWindow(env->dpy,scr),0,NULL);
  int temp=ceil(comb->result_len/3.0);
  int WIN_RESULT_W= temp * CELL_SIZE_FORM ;
  int WIN_W =WIN_RESULT_W + 2*CELL_SIZE_FORM+4*OFFSET; 
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
  attr.background_pixel = WhitePixel(env->dpy, scr);
  attr.event_mask = (KeyPressMask);
  size_t dy=OFFSET;
  for(size_t i=0; i<CELL_COUNT;i++,dy+=CELL_SIZE_FORM+OFFSET){
    env->forms[i].win=XCreateWindow(env->dpy, env->root, OFFSET, dy, CELL_SIZE_FORM,
                    CELL_SIZE_FORM, 1, depth, InputOutput, CopyFromParent,
                    (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
    if(i==1){
    env->forms[3].win=XCreateWindow(env->dpy, env->root, 2*OFFSET+CELL_SIZE_FORM, dy, CELL_SIZE_FORM,
                    CELL_SIZE_FORM, 1, depth, InputOutput, CopyFromParent,
                    (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
    env->forms[4].win=XCreateWindow(env->dpy, env->root, 3*OFFSET+2*CELL_SIZE_FORM, dy, WIN_RESULT_W,
                    CELL_SIZE_FORM, 1, depth, InputOutput, CopyFromParent,
                    (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);                    
    }
  }

  XSetNormalHints(env->dpy, env->root, &hint);
  XMapWindow(env->dpy,env->root);
  XMapSubwindows(env->dpy,env->root);
  
}

void freeEnv(winEnv *env) {
  XFreeGC(env->dpy, env->gc_Num);
}
void freeComb(Cb* comb){
  free(comb->n_str);
  free(comb->m_str);
  free(comb->result_str);

}


