#include "./g_environment-class.h"
#include "./w_environment-definitions.h"
#include "./l_calculations-definitions.h"
#include "stdio.h"
int dispatch(Envi*);

int main(){
    srand(time(NULL));
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
    XRectangle trace;
    XRectangle collision[2];
    while (flag) {
        event.type = 0;
        XCheckWindowEvent(p->dpy, p->main_win, (ExposureMask | KeyPressMask | StructureNotifyMask | ButtonPressMask |
           FocusChangeMask), &event);
        // XNextEvent(p->dpy,&event);
        switch (event.type) {
            break;
            case KeyPress:
                if(event.xkey.keycode == XKeysymToKeycode(p->dpy,_XK_ESCAPE)){
                    flag = 0;
                }
            break;
            case ButtonPress:
                if(!limit_exceded(p->orb_count)){
                    if(event.xbutton.button == Button2){
                        p->special = 1;
                        
                    }
                    p->on_click.direction = (rand_degree()*M_PI/180);
                    
                    create_orb(p,event.xbutton.x,event.xbutton.y);
                    collision[1] = move_on_click(p,p->on_click.trajectory[0]);
                }
            break;
            default:
            break;
        }
    if(count == VELOCITY_PSEUDO){
    XClearWindow(p->dpy,p->main_win);
    collision[0] = move_in_helix(p);
    fprintf(stderr,"helix:(%d %d)\n",collision[0].x,collision[0].y);
    if(p->orb_count==ORB_LIMIT){
        if (p->special){
            trace = special_next_trace(collision[1],collision[0]);
        } else {
            trace = default_next_trace(collision[1], p->on_click.direction);
        }
        collision[1]=move_on_click(p,trace);
        fprintf(stderr,"rad generated: {%lf}\n",p->on_click.direction);
        fprintf(stderr,"custom:(%d %d)\n",collision[1].x,collision[1].y );    
        if(is_collision(collision)){
            fprintf(stderr,"!!!!colided (%d %d) (%d %d)\n",collision[0].x,collision[0].y,collision[1].x,collision[1].y );
            destroyOrb(p);
    }
    }

    count=0;
    } else {
        count++;
    }
    
  }
  
}
