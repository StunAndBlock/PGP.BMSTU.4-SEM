#include "./g_environment-class.h"
#include "./g_configurations.h"
#include "X11/Xutil.h"
#include "stdio.h"
#include "string.h"

void prepare(Envi* p){
    p->dpy = XOpenDisplay(NULL);
    int scr = DefaultScreen(p->dpy);
    p->depth = DefaultDepth(p->dpy, scr);
    p->paint_gc = DefaultGC(p->dpy,scr);
    p->erase_gc = XCreateGC(p->dpy,RootWindow(p->dpy,scr),0,NULL);
   
}

void configurateFonts(Envi* p){
    XFontStruct *fn;
    char fontname_C[150] = "-bitstream-courier 10 pitch-medium-r-normal--";
    char font_suff[] = "-0-0-0-m-0-iso10646-1";
    size_t length_x = snprintf( NULL, 0, "%d", FONT_SIZE );
    char fs[length_x+1];
    snprintf( fs, length_x+1, "%d", FONT_SIZE );
    strcat(fontname_C,fs);
    strcat(fontname_C,font_suff);
    if ((fn = XLoadQueryFont(p->dpy, fontname_C)) == NULL)
    return;
    XSetFont(p->dpy, p->paint_gc, fn->fid);
    XSetFont(p->dpy, p->erase_gc, fn->fid);
    p->font_aligns.width = fn->max_bounds.width;
    p->font_aligns.height = fn->max_bounds.ascent + fn->max_bounds.descent;
    p->font_aligns.x = (BIT_WINDOW_WIDTH - p->font_aligns.width)/2;
    p->font_aligns.y = BIT_WINDOW_HEIGHT / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;
    p->font_aligns_exit.width =  fn->max_bounds.width * EXIT_BUTTON_TEXT_LENGTH;
    p->font_aligns_exit.height = fn->max_bounds.ascent + fn->max_bounds.descent;
    p->font_aligns_exit.x = (EXIT_WINDOW_WIDTH - p->font_aligns_exit.width)/2;
    p->font_aligns_exit.y = EXIT_WINDOW_HEIGHT /2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;
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
    attr.event_mask = (ExposureMask | KeyPressMask);
    p->main_win = XCreateWindow(p->dpy ,DefaultRootWindow(p->dpy) ,0 ,0 ,MAIN_WINDOW_WIDTH ,MAIN_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
    attr.background_pixel = COLOR_BLACK_HEX;
    p->rowsblock_win = XCreateWindow(p->dpy, p->main_win ,X_OFFSET ,Y_OFFSET ,BIT_ROW_WINDOW_WIDTH ,BIT_ROW_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent,(CWBackPixel) , &attr);
    p->complementbinrowblock_win = XCreateWindow(p->dpy, p->main_win ,X_OFFSET ,Y_OFFSET*2 + BIT_ROW_WINDOW_HEIGHT ,BIT_ROW_WINDOW_WIDTH ,BIT_ROW_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent ,(CWBackPixel) ,&attr);
    
    attr.background_pixel = BGCB;
    attr.override_redirect = False;
    attr.event_mask = (ButtonPressMask);
    int dx = 0;
    for(int i = 0; i < BIT_WINDOW_AMOUNT; i++,dx+=(X_OFFSET+BIT_WINDOW_WIDTH)){
        if(i%4==0 && i){
            dx+=GAP;
        }
        p->binrow_wins[i] = XCreateWindow(p->dpy, p->rowsblock_win ,dx ,Y_OFFSET ,BIT_WINDOW_WIDTH ,BIT_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
    }
    dx = 0;
    for(int i = 0; i < BIT_WINDOW_AMOUNT; i++,dx+=(X_OFFSET+BIT_WINDOW_WIDTH)){
        if(i%4==0 && i){
            dx+=GAP;
        }
        p->complementbinrow_wins[i] = XCreateWindow(p->dpy, p->complementbinrowblock_win ,dx ,Y_OFFSET ,BIT_WINDOW_WIDTH ,BIT_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
    }
    attr.background_pixel = COLOR_BLACK_HEX;
    p->exit_win = XCreateWindow(p->dpy, p->main_win ,dx ,Y_OFFSET ,EXIT_WINDOW_WIDTH ,EXIT_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);                                      
    
    hint.flags = (PMinSize | PMaxSize);
    hint.min_width = hint.max_width = MAIN_WINDOW_WIDTH;
    hint.min_height = hint.max_height = MAIN_WINDOW_HEIGHT;
    XSetNormalHints(p->dpy,p->main_win,&hint);
    XMapWindow(p->dpy,p->main_win);
    XMapSubwindows(p->dpy,p->main_win);
    XMapSubwindows(p->dpy,p->rowsblock_win);
    XMapSubwindows(p->dpy,p->complementbinrowblock_win);
}

int findWindow(Window* where,Window source){
    int i = 0;
    for(i = 0; i<BIT_WINDOW_AMOUNT; i++){
        if(where[i]==source){
            return i;
        }
    }   
    return -1;
}

void paint(Display* dpy, Window* drawable,char* source,GC gc,int count,XRectangle pos){
    for(int i = 0; i < count; i++){
        XDrawString(dpy,drawable[i],gc,pos.x,pos.y,&source[i],1);
    }
}

void freeEnvironment(Envi* p){
    XFreeGC(p->dpy,p->erase_gc);
    XCloseDisplay(p->dpy);
}

