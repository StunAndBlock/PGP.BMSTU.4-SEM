#ifndef W07_H_
#define W07_H_
#include <X11/Xlib.h>
#define CELL_COUNT 16
#define CELL_SIZE 32
 // BASE SIZE + BORDER SIZE + OFFSET;
#define OFFSET 4
#define WIN_W CELL_SIZE*CELL_COUNT + OFFSET*CELL_COUNT
#define WIN_H CELL_SIZE+2+4
typedef struct env {
Display* dpy;
Window root;
Window* cellArr;

} winEnv;




void dispatch(winEnv*);
void createEnv(winEnv*);
void freeEnv(winEnv* );
#endif /*W07_H_*/