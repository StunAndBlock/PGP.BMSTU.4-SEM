#ifndef W_ENVIRONMENT_DEFINITIONS
#define W_ENVIRONMENT_DEFINITIONS
#include "./g_environment-class.h"

void prepare(Envi* p);
// void configurateFonts(Envi*);
void configurateColors(Envi*);
void configurateWindows(Envi*);
void configuratePixmap(Envi*);
int findWindow(Window*, int, Window);
void paint(Display* dpy, Window* drawable, GC gc, XRectangle pos);
void freeEnvironment(Envi*);
XRectangle move_in_helix(Envi*);
void create_orb(Envi* p, int, int);
XRectangle move_on_click(Envi* p, XRectangle);
void destroyOrb(Envi*);
#endif //END OF W_ENVIRONMENT_SETUP_DEFINITIONS