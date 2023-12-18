#include "./g_environment-class.h"
#include "./w_environment-definitions.h"
#include "./l_calculations-definitions.h"
#include "stdio.h"
int dispatch(Envi*);

int main(){
    Envi prog;
    prepare(&prog);
    calculateTraces(&prog);
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
    int count=0;
    XEvent event;
    while (flag) {
        event.type = 0;
        XCheckWindowEvent(p->dpy, p->main_win, (ExposureMask | KeyPressMask | StructureNotifyMask | KeyReleaseMask |
           FocusChangeMask), &event);
        // XNextEvent(p->dpy,&event);
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
    if(count == VELOCITY_PSEUDO){
    XClearWindow(p->dpy,p->main_win);
    move_in_helix(p);
    count=0;
    } else {
        count++;
    }

  }
  
}
