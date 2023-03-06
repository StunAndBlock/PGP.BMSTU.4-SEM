#ifndef W02_H_
#define W02_H_
#include <X11/Xlib.h>    /* X Display */
static GC gc[2];         /* Graphic Context */
static Window root;      /* Main root window */
static Window** box;     /* box (NYxNX) window array address */
static Window* row;      /* NY row window  box containe array  */ 
static unsigned** pos;   /* Marker position NYx2 array address */
static int X0=0;         /* main root wintow x-location */
static int Y0=0;         /* main root wintow y-location */
static unsigned NX=16;   /* Default Boxes' number in each row */
static unsigned NY=4;    /* Default Row's number in game desk */
static XRectangle cell;             /* Box cell */





#endif /* W02_H_ */