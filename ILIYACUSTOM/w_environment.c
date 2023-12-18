#include "./g_environment-class.h"
#include "./g_configurations.h"
#include "X11/Xutil.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

void prepare(Envi* p){
    p->special = 0;
    p->in_Helix.is_determined=1;
    p->in_Helix.trajectory = (XRectangle*)malloc(sizeof(XRectangle)*DOTS);
    p->orb_count = 1;
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
    // XDrawLine(p->dpy, p->main_pix, p->paint_gc, MAIN_WINDOW_WIDTH/2, 0, MAIN_WINDOW_WIDTH/2, MAIN_WINDOW_HEIGHT);
    // XDrawLine(p->dpy, p->main_pix, p->paint_gc, 0, MAIN_WINDOW_HEIGHT/2, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT/2);
    int state = -1;
    for(int i = 0; i <=HELIX_ARCS; i++, state = -state){
    XDrawArc(p->dpy, p->main_pix, p->paint_gc, p->hx[i].pos.x, p->hx[i].pos.y, p->hx[i].width, p->hx[i].height,0, state * 180*64);
    }
    state = -state;
    XDrawArc(p->dpy, p->main_pix, p->paint_gc, p->hx[HELIX_ARCS+1].pos.x, p->hx[HELIX_ARCS+1].pos.y, p->hx[HELIX_ARCS+1].width, p->hx[HELIX_ARCS+1].height,90*64, state * 90*64);

}

void paint(Display* dpy, Window drawable, GC gc, XRectangle pos){
    XDrawArc(dpy,drawable,gc,pos.x-HELIX_ORB_RADIUS,pos.y - HELIX_ORB_RADIUS, HELIX_ORB_RADIUS*2,HELIX_ORB_RADIUS*2,0,360*64);
}


XRectangle move_on_click(Envi* p, XRectangle dest){  

    //paint(p->dpy,p->main_win,p->erase_gc,p->in_Helix.trajectory[i-1]);
    paint(p->dpy,p->main_win,p->paint_gc,dest);
    return dest;
}



XRectangle move_in_helix(Envi* p){  
    static int i = 1;
    //paint(p->dpy,p->main_win,p->erase_gc,p->in_Helix.trajectory[i-1]);
    paint(p->dpy,p->main_win,p->paint_gc,p->in_Helix.trajectory[i]);
    i++;
    if(i == DOTS){
        i=1;
    }
    return p->in_Helix.trajectory[i];
}

void configurateWindows(Envi* p){
    XSetWindowAttributes attr; /* created Window attributes */
    XSizeHints hint;
    attr.background_pixmap = p->main_pix;
    attr.override_redirect = False;
    attr.event_mask = (ExposureMask | KeyPressMask | ButtonPressMask);

    p->main_win = XCreateWindow(p->dpy ,DefaultRootWindow(p->dpy) ,0 ,0 ,MAIN_WINDOW_WIDTH ,MAIN_WINDOW_HEIGHT ,0 ,
                                p->depth, InputOutput, CopyFromParent, (CWOverrideRedirect | CWBackPixmap | CWEventMask ), &attr);
    
    hint.flags = (PMinSize | PMaxSize);
    hint.min_width = hint.max_width = MAIN_WINDOW_WIDTH;
    hint.min_height = hint.max_height = MAIN_WINDOW_HEIGHT;
    // XSetNormalHints(p->dpy,p->main_win,&hint);
    XMapWindow(p->dpy,p->main_win);
    XMapSubwindows(p->dpy,p->main_win);

}

void create_orb(Envi* p, int x, int y ){
    p->on_click.trajectory=(XRectangle*)malloc(sizeof(XRectangle) * 2);
    // printf("%d %d",ev->xbutton.x,ev->xbutton.y);
    p->on_click.trajectory[0].x=x;
    p->on_click.trajectory[0].y=y;
    p->orb_count+=1;
}
void destroyOrb(Envi* p){
    p->special = (p->special) ? 0 : 0;
    p->orb_count-=1;
    free(p->on_click.trajectory);
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


void freeEnvironment(Envi* p){
    free(p->in_Helix.trajectory);
    if (p->orb_count == 2){
        free(p->on_click.trajectory);
    }
    XFreeGC(p->dpy,p->erase_gc);
    XCloseDisplay(p->dpy);
}

