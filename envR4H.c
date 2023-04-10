#include "R4.h"
#include "X11/Xutil.h"

void createEnv(winHandl *newEnv) {
  newEnv->dpy = XOpenDisplay(NULL);
  newEnv->rectanglesCount = 0;
  int scr = DefaultScreen(newEnv->dpy);
  int depth = DefaultDepth(newEnv->dpy, scr);
  dArr rootWindowSize;
  rootWindowSize.box[X] = DisplayWidth(newEnv->dpy, scr);
  rootWindowSize.box[Y] = DisplayHeight(newEnv->dpy, scr);
  newEnv->gc = DefaultGC(newEnv->dpy, scr);
  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(newEnv->dpy, scr);
  attr.event_mask =
      (ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | KeyPressMask);
  newEnv->root =
      XCreateWindow(newEnv->dpy, DefaultRootWindow(newEnv->dpy), 0, 0,
                    rootWindowSize.box[X] - 300, rootWindowSize.box[Y] - 300, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  hint.flags = (PMinSize | PMaxSize | PPosition);
  hint.min_width = hint.max_width = rootWindowSize.box[X] - 300;
  hint.min_height = hint.max_height = rootWindowSize.box[Y] - 300;
  hint.x = 0;
  hint.y = 0;
  XSetNormalHints(newEnv->dpy, newEnv->root, &hint);

  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(newEnv->dpy, scr);
  // attr.background_pixmap=pix;
  // attr.bit_gravity=SouthEastGravity;
  attr.event_mask = (VisibilityChangeMask | KeyPressMask);
  newEnv->selection = XCreateWindow(
      newEnv->dpy, newEnv->root, 0, 0, 10, 10, 0, depth, InputOutput,
      CopyFromParent, (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
  XMapWindow(newEnv->dpy, newEnv->root);

  
  XSetLineAttributes(newEnv->dpy, newEnv->gc, 2, LineOnOffDash, CapNotLast,
                     JoinMiter);

  XStoreName(newEnv->dpy, newEnv->root, "R4 BERKOVICH E.S");
}

void freeEnv(unsigned char state, winHandl *newEnv) {
  if (state)
    free(newEnv->rectangles);
}

void parseColor(winHandl* newEnv,int argc,char** argv){
    Colormap cmap;                
	XColor rgb, exact;
  XrmDatabase rbd;         
	int i;                      
	static XrmOptionDescRec rtab[] = 
	{ 
		{"-bg ", ".background", XrmoptionSepArg, NULL}
		{"-xrm ", NULL, XrmoptionResArg, NULL}
	}; 
  XrmInitialize();                         
	rdb = XrmGetFileDatabase(".xdb");                     
	XrmParseCommand(&rdb, rtab, 2+1, "r4", &argc, argv); 
for(i=0; i < NGC; i++) 
	{
		if(XrmGetResource(rdb, rname[i], NULL, &rtype, rval) == False)
			rval->addr = rdef[i];
		if(XParseColor(dpy, cmap, rval->addr, &rgb) == 0)
			if(XLookupColor(dpy, cmap, (rval->addr = rdef[i]), &rgb, &exact) == 0)
				memcpy(&rgb, &exact, sizeof(XColor));
		printf("%s(%s): %s\n", rname[i], rtab[i].option, rval->addr); /* Echo */
		fflush(stdout);
		XAllocColor(dpy, cmap, &rgb);
		gc[i] = XCreateGC(dpy, root, 0, 0);
		XSetForeground(dpy, gc[i], rgb.pixel);
	} 

}
