#include "./g_environment-class.h"
#include "./w_environment-definitions.h"
#include "./l_calculations-definitions.h"
#include "stdio.h"
int dispatch(Envi*);

int main(){
    Envi prog;
    prepare(&prog);
    refill(prog.bin_str);
    updateComplement(prog.bin_str,prog.complementbin_str);
    configurateFonts(&prog);
    configurateColors(&prog);
    configurateWindows(&prog);
    dispatch(&prog);

}









int dispatch(Envi* p){
    int flag = 1;
    int winNum = -1;
    XEvent event;
    while (flag) {
        XNextEvent(p->dpy, &event);
        switch (event.type) {
            break;
            case KeyPress:
            flag = 0;
            break;
            case ButtonPress:
            if(event.xbutton.window == p->exit_win){
                flag = 0;
            } else if ((winNum = findWindow(p->binrow_wins,event.xbutton.window))>-1){
                XDrawString(p->dpy,p->binrow_wins[winNum],p->erase_gc,p->font_aligns.x,p->font_aligns.y,&p->bin_str[winNum],1);
                p->bin_str[winNum]=SINV(p->bin_str[winNum]);
                XDrawString(p->dpy,p->binrow_wins[winNum],p->paint_gc,p->font_aligns.x,p->font_aligns.y,&p->bin_str[winNum],1);
                for(int i = 0; i < BIT_WINDOW_AMOUNT; i++){
                XDrawString(p->dpy,p->complementbinrow_wins[i],p->erase_gc,p->font_aligns.x,p->font_aligns.y,&p->complementbin_str[i],1);
                }
                updateComplement(p->bin_str,p->complementbin_str);
                for(int i = 0; i < BIT_WINDOW_AMOUNT; i++){
                XDrawString(p->dpy,p->complementbinrow_wins[i],p->paint_gc,p->font_aligns.x,p->font_aligns.y,&p->complementbin_str[i],1);
                }
            }
            default:
            for(int i = 0; i < BIT_WINDOW_AMOUNT; i++){
                XDrawString(p->dpy,p->binrow_wins[i],p->paint_gc,p->font_aligns.x,p->font_aligns.y,&p->bin_str[i],1);
                XDrawString(p->dpy,p->complementbinrow_wins[i],p->paint_gc,p->font_aligns.x,p->font_aligns.y,&p->complementbin_str[i],1);
            }
            break;
    }
  }
}
