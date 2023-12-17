#ifndef W_ENVIRONMENT_DEFINITIONS
#define W_ENVIRONMENT_DEFINITIONS
#include "./g_environment-class.h"

void prepare(Envi* p);
// void configurateFonts(Envi*);
void configurateColors(Envi*);
void configurateWindows(Envi*);
void configuratePixmap(Envi*);
int findWindow(Window*, int, Window);
void paint(Display* ,Window* ,char* ,GC ,int ,XRectangle);
void freeEnvironment(Envi*);

#endif //END OF W_ENVIRONMENT_SETUP_DEFINITIONS