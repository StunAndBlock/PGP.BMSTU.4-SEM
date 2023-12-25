#include "./gi_class.hpp"

Genv::Genv(){
    dpy = XOpenDisplay(NULL);
    scr = DefaultScreen(dpy);
    depth = DefaultDepth(dpy, scr);
    root = RootWindow(dpy, scr);
}

void Genv::windows_init(float offset_np){
    scale = static_cast<int>(offset_np * MIN_DRAW_FIELD_WIDTH);
     if (scale <= 1){
         scale = 2;
     }
    XSetWindowAttributes attr;
    attr.override_redirect = False;
    attr.event_mask = (KeyPressMask| ButtonPressMask);
    attr.background_pixel = ERASE_COLOR;
    main = XCreateWindow(dpy,DefaultRootWindow(dpy),0,0,MIN_DRAW_FIELD_WIDTH+scale,MIN_DRAW_FIELD_WIDTH+scale,0,depth,InputOutput,CopyFromParent,(CWOverrideRedirect|CWEventMask|CWBackPixel),&attr);
    attr.background_pixmap = hilbert_pix;
    attr.event_mask = (KeyPressMask| ButtonPressMask);
    draw_field = XCreateWindow(dpy,main,scale,scale,MIN_DRAW_FIELD_WIDTH,MIN_DRAW_FIELD_WIDTH,0,depth,InputOutput,CopyFromParent,(CWOverrideRedirect | CWEventMask| CWBackPixmap),&attr); 
    XMapWindow(dpy,main);
    XMapWindow(dpy,draw_field);  
}

void Genv::graphics_init(){
    XGCValues scheme;
    scheme.foreground = ERASE_COLOR;
    erase = XCreateGC(dpy,root,(GCForeground),&scheme);
    scheme.foreground = PAINT_COLOR;
    paint = XCreateGC(dpy,root,(GCForeground),&scheme);
    hilbert_pix = XCreatePixmap(dpy,root,MIN_DRAW_FIELD_WIDTH,MIN_DRAW_FIELD_HEIGHT,depth);
}

void Genv::draw_hilbert(const int N, int K,uint16_t(* curve)[2]){
    XFillRectangle(dpy,hilbert_pix,erase,0,0,MIN_DRAW_FIELD_WIDTH,MIN_DRAW_FIELD_HEIGHT);
    for (size_t i=0; i<(1U<<N*K)-1; i++){
        XDrawLine(dpy,hilbert_pix,paint,curve[i][0]*scale,curve[i][1]*scale,curve[i+1][0]*scale,curve[i+1][1]*scale);
    }
}

Genv::~Genv(){
    XFreeGC(dpy,paint);
    XFreeGC(dpy,erase);
    XCloseDisplay(dpy);
}