#include "./g_environment-class.h"
#include "./w_environment-definitions.h"
#include "./l_calculations-definitions.h"
#include "stdio.h"
int dispatch(Envi*);

int main(){
    Envi prog;
    prepare(&prog);
    // configurateFonts(&prog);
    configurateColors(&prog);
    configuratePixmap(&prog);
    configurateWindows(&prog);
    dispatch(&prog);
    freeEnvironment(&prog);
    return 1;
}


int dispatch(Envi* p){
    int flag = 1;
    int winNum = -1;
    int parent = -1;
    int ta = 1;
    XEvent event;
    while (flag) {
        XCheckWindowEvent(p->dpy, p->main_win, (ExposureMask | KeyPressMask | StructureNotifyMask | KeyReleaseMask |
           FocusChangeMask), &event);
        switch (event.type) {
            break;
            case KeyPress:
                if(event.xkey.keycode == XKeysymToKeycode(p->dpy,_XK_ESCAPE)){
   
                }
            break;
            case ButtonPress:
            
            break;
            default:
                if (ta){ 
              
                ta=0;
                }
            break;
    }
    printf("1");
  }
}
