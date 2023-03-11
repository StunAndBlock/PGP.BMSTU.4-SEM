#include "W07.h"


int main(void){
 winEnv newEnv;
 createEnv(&newEnv);
    dispatch(&newEnv);
    XDestroySubwindows(newEnv.dpy,newEnv.root);
    freeEnv(&newEnv);    
    XDestroyWindow(newEnv.dpy,newEnv.root);
    XCloseDisplay(newEnv.dpy);





}


void dispatch(winEnv* env){
unsigned char flag=1;
XEvent event;

while(flag){
    XNextEvent(env->dpy, &event);
    switch(event.type){
            case KeyPress:
            flag=0;
            break;


        default:
        break;
    }

}
}
