#include "./g_environment-class.h"
#include "./w_environment-definitions.h"
#include "./l_calculations-definitions.h"
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
        XNextEvent(p->dpy, &event);
        switch (event.type) {
            break;
            case KeyPress:
                if(event.xkey.keycode == XKeysymToKeycode(p->dpy,_XK_ESCAPE)){
                    paint(p->dpy,p->binrow_wins,p->bin_str,p->erase_gc,BIT_WINDOW_AMOUNT,p->font_aligns);
                    refill(p->bin_str);
                    paint(p->dpy,p->binrow_wins,p->bin_str,p->paint_gc,BIT_WINDOW_AMOUNT,p->font_aligns);
                    paint(p->dpy,p->complementbinrow_wins,p->complementbin_str,p->erase_gc,BIT_WINDOW_AMOUNT,p->font_aligns);
                    refill(p->complementbin_str);
                    paint(p->dpy,p->complementbinrow_wins,p->complementbin_str,p->paint_gc,BIT_WINDOW_AMOUNT,p->font_aligns);
                }
            break;
            case ButtonPress:
            if(event.xbutton.window == p->exit_win){
                flag = 0;
            } else if ((winNum = findWindow(p->binrow_wins,event.xbutton.window))!=-1){
                    paint(p->dpy,&p->binrow_wins[winNum],&p->bin_str[winNum],p->erase_gc,1,p->font_aligns);
                    p->bin_str[winNum]=SINV(p->bin_str[winNum]);
                    paint(p->dpy,&p->binrow_wins[winNum],&p->bin_str[winNum],p->paint_gc,1,p->font_aligns);
                    paint(p->dpy,p->complementbinrow_wins,p->complementbin_str,p->erase_gc,BIT_WINDOW_AMOUNT,p->font_aligns);
                    updateComplement(p->bin_str,p->complementbin_str);
                    paint(p->dpy,p->complementbinrow_wins,p->complementbin_str,p->paint_gc,BIT_WINDOW_AMOUNT,p->font_aligns);
                } 
            else if ((winNum = findWindow(p->complementbinrow_wins,event.xbutton.window))!=-1){
                    paint(p->dpy,&p->complementbinrow_wins[winNum],&p->complementbin_str[winNum],p->erase_gc,1,p->font_aligns);
                    p->complementbin_str[winNum]=SINV(p->complementbin_str[winNum]);
                    paint(p->dpy,&p->complementbinrow_wins[winNum],&p->complementbin_str[winNum],p->paint_gc,1,p->font_aligns);
                    paint(p->dpy,p->binrow_wins,p->bin_str,p->erase_gc,BIT_WINDOW_AMOUNT,p->font_aligns);
                    updateBinary(p->complementbin_str,p->bin_str);
                    paint(p->dpy,p->binrow_wins,p->bin_str,p->paint_gc,BIT_WINDOW_AMOUNT,p->font_aligns);
                } 
            
            default:
                if (ta){ 
                paint(p->dpy,p->binrow_wins,p->bin_str,p->paint_gc,BIT_WINDOW_AMOUNT,p->font_aligns);
                paint(p->dpy,p->complementbinrow_wins,p->complementbin_str,p->paint_gc,BIT_WINDOW_AMOUNT,p->font_aligns);
                XFillRectangle(p->dpy ,p->exit_win ,p->erase_gc ,X_OFFSET ,Y_OFFSET,EXIT_WINDOW_WIDTH - X_OFFSET * 2, EXIT_WINDOW_HEIGHT - Y_OFFSET);
                XDrawString(p->dpy, p->exit_win, p->paint_gc ,p->font_aligns_exit.x ,p->font_aligns_exit.y ,EXIT_BUTTON_TEXT,EXIT_BUTTON_TEXT_LENGTH);
                ta=0;
                }
            break;
    }
  }
}
