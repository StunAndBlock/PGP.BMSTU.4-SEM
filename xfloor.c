/* Chain Arm Ring background */

#include <X11/Xlib.h>
#include <stdlib.h>
#define WIDTH 580
#define HEIGHT 550
#define MAP_WIDTH WIDTH / 6   /* repeat element width */
#define MAP_HEIGHT HEIGHT / 4 /* repeat element height */
#define KEY_q 24
int main(int argc, char* argv[]) {
    Display* dpy;              /* display structure */
    int src;                   /* screen number */
    GC gc;                     /* graphic context */
    int depth;                 /* bit per color pixel */
    Window root;               /* screen root window */
    Pixmap pix;                /* Pixel map for ring */
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
    /* Pixmap block */
    XSetLineAttributes(dpy, gc, 2, LineSolid, CapNotLast, JoinMiter);
    XPoint* points = malloc(sizeof(XPoint) * 7);
    points[0].x = MAP_WIDTH / 2;
    points[0].y = 0;
    points[1].x = MAP_WIDTH;
    points[1].y = HEIGHT / 4 / 3;
    points[2].x = MAP_WIDTH;
    points[2].y = HEIGHT / 4 / 3 * 2;
    points[3].x = MAP_WIDTH / 2;
    points[3].y = HEIGHT / 4;
    points[4].x = 0;
    points[4].y = HEIGHT / 4 / 3 * 2;
    points[5].x = 0;
    points[5].y = HEIGHT / 4 / 3;
    points[6].x = MAP_WIDTH / 2;
    points[6].y = 0;
    pix = XCreatePixmap(dpy, root, MAP_WIDTH, MAP_HEIGHT, depth);
    // XSetBackground(dpy, gc, WhitePixel(dpy,src));
    XSetForeground(dpy, gc, WhitePixel(dpy, src));
    XFillRectangle(dpy, pix, gc, 0, 0, WIDTH, HEIGHT);
    XSetForeground(dpy, gc, BlackPixel(dpy, src));
    // XDrawArc(dpy, pix, gc, 0, 0, WIDTH, HEIGHT, 0, 90*64);
    XDrawLines(dpy, pix, gc, points, 7, CoordModeOrigin);
    /* Window block */

    mask = (CWOverrideRedirect | CWBackPixmap);
    attr.override_redirect = False;
    attr.background_pixmap = pix;
    win = XCreateWindow(dpy, root, 0, 0, WIDTH, HEIGHT, 1, depth, InputOutput, CopyFromParent, mask, &attr);
    mask = (ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask | KeyPressMask);
    XSelectInput(dpy, win, mask);
    XMapRaised(dpy, win);
    XSetFunction(dpy, gc, GXinvert); /* XSetFunction(dpy, gc, GXcopyInverted); */

    /* Dispatch block */

    while (done != KEY_q) {
        XNextEvent(dpy, &event);
        switch (event.type) {
            case ButtonPress:
            case ButtonRelease:
                XCopyArea(dpy, pix, pix, gc, 0, 0, MAP_WIDTH, MAP_HEIGHT, 0, 0);
                XSetWindowBackgroundPixmap(dpy, win, pix);
                XClearWindow(dpy, win);
                break;
            case KeyPress:
                done = event.xkey.keycode;
                break;
            default:
                break;
        } /* switch */
    }     /* while */

    /* X-Exit block */
    free(points);
    XFreePixmap(dpy, pix);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    return (done);
} /* main */
