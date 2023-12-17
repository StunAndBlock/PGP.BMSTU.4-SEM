#include "./g_environment-class.h"
#include "./g_configurations.h"
#include "X11/Xutil.h"
#include "stdio.h"
#include "string.h"

void prepare(Envi* p){
    p->dpy = XOpenDisplay(NULL);
    int scr = DefaultScreen(p->dpy);
    p->depth = DefaultDepth(p->dpy,scr);
    p->paint_gc = DefaultGC(p->dpy,scr);
    p->erase_gc = XCreateGC(p->dpy,RootWindow(p->dpy,scr),0,NULL);
    p->main_pix = XCreatePixmap(p->dpy,RootWindow(p->dpy,scr),MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT,p->depth);
}

// void configurateFonts(Envi* p){
//     XFontStruct *fn;
//     char fontname_C[150] = "-bitstream-courier 10 pitch-medium-r-normal--";
//     char font_suff[] = "-0-0-0-m-0-iso10646-1";
//     size_t length_x = snprintf( NULL, 0, "%d", FONT_SIZE );
//     char fs[length_x+1];
//     snprintf( fs, length_x+1, "%d", FONT_SIZE );
//     strcat(fontname_C,fs);
//     strcat(fontname_C,font_suff);
//     if ((fn = XLoadQueryFont(p->dpy, fontname_C)) == NULL)
//     return;
//     XSetFont(p->dpy, p->paint_gc, fn->fid);
//     XSetFont(p->dpy, p->erase_gc, fn->fid);
//     p->font_aligns.width = fn->max_bounds.width;
//     p->font_aligns.height = fn->max_bounds.ascent + fn->max_bounds.descent;
//     p->font_aligns.x = (BIT_WINDOW_WIDTH - p->font_aligns.width)/2;
//     p->font_aligns.y = BIT_WINDOW_HEIGHT / 2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;
//     p->font_aligns_exit.width =  fn->max_bounds.width * EXIT_BUTTON_TEXT_LENGTH;
//     p->font_aligns_exit.height = fn->max_bounds.ascent + fn->max_bounds.descent;
//     p->font_aligns_exit.x = (EXIT_WINDOW_WIDTH - p->font_aligns_exit.width)/2;
//     p->font_aligns_exit.y = EXIT_WINDOW_HEIGHT /2 + (fn->max_bounds.ascent - fn->max_bounds.descent) / 2;
//     XFreeFont(p->dpy,fn);

// }



void configurateColors(Envi* p){
    XGCValues v;
    v.foreground= PAINT_COLOR;
    XChangeGC(p->dpy,p->paint_gc,(GCForeground),&v);
    v.foreground = ERASE_COLOR;
    XChangeGC(p->dpy,p->erase_gc,(GCForeground),&v);
}


void configuratePixmap(Envi* p){
    XFillRectangle(p->dpy, p->main_pix, p->erase_gc, 0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    int r = HELIX_RADIUS;
    int old_r = 0;
    // XDrawLine(p->dpy, p->main_pix, p->paint_gc, MAIN_WINDOW_WIDTH/2, 0, MAIN_WINDOW_WIDTH/2, MAIN_WINDOW_HEIGHT);
    // XDrawLine(p->dpy, p->main_pix, p->paint_gc, 0, MAIN_WINDOW_HEIGHT/2, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT/2);
    int x = MAIN_WINDOW_WIDTH/2;
    int y = MAIN_WINDOW_HEIGHT/2 - r;
    XDrawArc(p->dpy, p->main_pix, p->paint_gc, x, y, r*2, r*2,0, -180*64);
    int state = 1;
    for(int i = 0; i < HELIX_ARCS; i++, state = -state){
    old_r = r;
    r+=ARC_DELTA;
    if(!(i%2)){
        x = x + 2 * (old_r - r);
    }
    y = MAIN_WINDOW_HEIGHT/2 - r;
    XDrawArc(p->dpy, p->main_pix, p->paint_gc, x, y, r*2, r*2,0, state * 180*64);
    }
    state = -state;
    old_r = r;
    r+=ARC_DELTA;
    x = x + 2 * (old_r - r);
    y = MAIN_WINDOW_HEIGHT/2 - r;
    XDrawArc(p->dpy, p->main_pix, p->paint_gc, x, y, r*2, r*2,90*64, state * 90*64);

}

void configurateWindows(Envi* p){
    XSetWindowAttributes attr; /* created Window attributes */
    XSizeHints hint;
    attr.background_pixmap = p->main_pix;
    attr.override_redirect = False;
    attr.event_mask = (ExposureMask | KeyPressMask);
    p->main_win = XCreateWindow(p->dpy ,DefaultRootWindow(p->dpy) ,0 ,0 ,MAIN_WINDOW_WIDTH ,MAIN_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent, (CWOverrideRedirect | CWBackPixmap | CWEventMask), &attr);
    
    hint.flags = (PMinSize | PMaxSize);
    hint.min_width = hint.max_width = MAIN_WINDOW_WIDTH;
    hint.min_height = hint.max_height = MAIN_WINDOW_HEIGHT;
    XSetNormalHints(p->dpy,p->main_win,&hint);
    XMapWindow(p->dpy,p->main_win);
    XMapSubwindows(p->dpy,p->main_win);

}

int findWindow(Window* where, int n, Window source){
    int i = 0;
    for(i = 0; i<n; i++){
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

