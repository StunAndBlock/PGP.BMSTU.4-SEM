#include "./g_environment-class.h"
#include "./g_configurations.h"
#include "X11/Xutil.h"


void prepare(Envi* p){
    p->dpy = XOpenDisplay(NULL);
    int scr = DefaultScreen(p->dpy);
    p->depth = DefaultDepth(p->dpy, scr);
    p->paint_gc = DefaultGC(p->dpy,scr);
    p->erase_gc = XCreateGC(p->dpy,RootWindow(p->dpy,scr),0,NULL);
   
}

void configurateFonts(Envi* p){
    XFontStruct *fn;
    const char fontname_C[] = "-bitstream-courier 10 pitch-medium-r-normal--50-0-0-0-m-0-iso10646-1";
    if ((fn = XLoadQueryFont(p->dpy, fontname_C)) == NULL)
    return;
    XSetFont(p->dpy, p->paint_gc, fn->fid);
    XSetFont(p->dpy, p->erase_gc, fn->fid);
    p->font_aligns.width = fn->max_bounds.width;
    p->font_aligns.height = fn->max_bounds.ascent + fn->max_bounds.descent;
    p->font_aligns.x = (BIT_WINDOW_WIDTH - p->font_aligns.width)/2;
    p->font_aligns.y = BIT_WINDOW_WIDTH / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;
    XFreeFont(p->dpy,fn);

}

void configurateColors(Envi* p){
    XGCValues v;
    v.foreground= PAINT_COLOR;
    XChangeGC(p->dpy,p->paint_gc,(GCForeground),&v);
    v.foreground = ERASE_COLOR;
    XChangeGC(p->dpy,p->erase_gc,(GCForeground),&v);
}

void configurateWindows(Envi* p){
    XSetWindowAttributes attr; /* created Window attributes */
    XSizeHints hint;
    attr.background_pixel = BGCM;
    attr.override_redirect = False;
    attr.event_mask = (ExposureMask);
    p->main_win = XCreateWindow(p->dpy ,DefaultRootWindow(p->dpy) ,0 ,0 ,MAIN_WINDOW_WIDTH ,MAIN_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
    attr.background_pixel = COLOR_BLACK_HEX;
    attr.override_redirect = False;
    attr.event_mask = (ButtonPressMask);
    p->rowsblock_win = XCreateWindow(p->dpy, p->main_win ,X_OFFSET ,Y_OFFSET ,BIT_ROW_WINDOW_WIDTH ,BIT_ROW_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
    p->complementbinrowblock_win = XCreateWindow(p->dpy, p->main_win ,X_OFFSET ,Y_OFFSET*2 + BIT_ROW_WINDOW_HEIGHT ,BIT_ROW_WINDOW_WIDTH ,BIT_ROW_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent ,0 , NULL);
    
    attr.background_pixel = BGCB;
    attr.override_redirect = False;
    attr.event_mask = (ButtonPressMask);
    for(int i = 0; i < BIT_WINDOW_AMOUNT; i++){
        p->binrow_wins[i] = XCreateWindow(p->dpy, p->rowsblock_win ,(X_OFFSET+BIT_WINDOW_WIDTH)*i ,Y_OFFSET ,BIT_WINDOW_WIDTH ,BIT_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
    }
    for(int i = 0; i < BIT_WINDOW_AMOUNT; i++){
        p->complementbinrow_wins[i] = XCreateWindow(p->dpy, p->complementbinrowblock_win ,(X_OFFSET+BIT_WINDOW_WIDTH)*i ,Y_OFFSET ,BIT_WINDOW_WIDTH ,BIT_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
    }                                     
    XMapWindow(p->dpy,p->main_win);
    XMapSubwindows(p->dpy,p->main_win);
    XMapSubwindows(p->dpy,p->rowsblock_win);
    XMapSubwindows(p->dpy,p->complementbinrowblock_win);
}

int findWindow(Window* where,Window source){
    for(int i = 0; i<BIT_WINDOW_AMOUNT; i++){
        if(where[i]==source){
            return i;
        }
    }
    return -1;
}