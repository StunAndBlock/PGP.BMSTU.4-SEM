
#include <X11/Xlib.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
    Display* dpy;              /* display structure */
    int src;                   /* screen number */
    GC gc;                     /* graphic context */
    int depth;                 /* bit per color pixel */
    Window root;               /* screen root window */
//    Pixmap pix;                /* Pixel map for ring */
    Window win;                /* Main window */
    XSetWindowAttributes attr; /* window attributes */
    unsigned long mask;        /* event mask */
    XEvent event;              /* Event structure */
    unsigned int done = 0;     /* exit code */

    /* X init */

    dpy = XOpenDisplay(NULL);
    src = DefaultScreen(dpy);
    depth = DefaultDepth(dpy, src);
    root = DefaultRootWindow(dpy);
    gc = DefaultGC(dpy, src);
    /* */
    mask = (CWOverrideRedirect);
    attr.override_redirect = False;
 //   attr.background_pixmap = pix;
    int i=600;
    win = XCreateWindow(dpy, root, 0, 0, 600, 600, 1, depth, InputOutput, CopyFromParent, mask, &attr);
    mask = (ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask | KeyPressMask);
    XSelectInput(dpy, win, mask);
    XMapRaised(dpy, win);
   // XSetFunction(dpy, gc, GXinvert); /* XSetFunction(dpy, gc, GXcopyInverted); */
 mask = (CWOverrideRedirect);
    /* Dispatch block */
    while (done != 24) {
        XNextEvent(dpy, &event);
        switch (event.type) {
            case ButtonPress:
            case ButtonRelease:
                XClearWindow(dpy, win);
                XDestroyWindow(dpy, win);
                win = XCreateWindow(dpy, root, 0, 0, i+50, i+50, 1, depth, InputOutput, CopyFromParent, mask, &attr);
                XMapRaised(dpy, win);
                break;
            case KeyPress:
                done = event.xkey.keycode;
                break;
            default:
                break;
        } /* switch */
    }     /* while */

    /* X-Exit block */
    
    XCloseDisplay(dpy);
    return (done);
} /* main */