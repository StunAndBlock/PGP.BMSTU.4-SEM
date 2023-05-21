#ifndef M_H_
#define M_H_
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#define NPOINTS 3
#define DA (M_PI / 360)
#define C_DOT_RADIUS 50
#define DELAY (1 << 14)
/*структура стрелы*/
typedef struct {
  float A[NPOINTS];
  float dA;
  XPoint c;
  int R[NPOINTS];
} XArrow;
/* Spiral Implementation function */
int configure_arrow(XArrow *, int, int, int);
int reconfigure(XArrow *, int, int);
int redraw(XEvent *, GC, XArrow *);
int reset(XArrow *, int);
int amod2pi(XArrow *);
int draw_arrow(Display *, Window, GC, XArrow *);
int reverse(int, XArrow *);
int key_check(XEvent *ev);
int rep5355(Display *, int);

#endif // 1M_H