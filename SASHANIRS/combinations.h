#ifndef COMBINATIONS_H_
#define COMBINATIONS_H_
#include <X11/Xlib.h>
#define CELL_COUNT 3
#define CELL_SIZE_FORM 190
// BASE SIZE + BORDER SIZE + OFFSET;
#define OFFSET 5
#define WIN_W 400
#define WIN_H CELL_SIZE_FORM*CELL_COUNT+OFFSET*(CELL_COUNT+1)
#define K_ESC 9
#define ALT 64
typedef struct Form {
  Window win;
  XRectangle m;
  XRectangle n;
  XRectangle brace_1;
  XRectangle brace_2;
  XRectangle C;
  
} Form;



typedef struct env {
  Display *dpy;
  Window root;
  Window viewform;
  Form forms[3];
  GC gc_C;
  GC gc_Num;
  Window exit;
} winEnv;

typedef struct Combination_base {
  int n;
  int m;
  char* n_str;
  char* m_str;
  size_t n_len;
  size_t m_len;
  char* C;
  char* brace_1;
  char* brace_2;
} Cb;

void dispatch(winEnv *,Cb*);
void createEnv(winEnv *);
void freeEnv(winEnv *);

void invertBit(unsigned char, winEnv *);
unsigned char control(Window, winEnv *);
unsigned char _pow(unsigned char);

void keycontrol(unsigned int, winEnv *);
void arrangeForm(winEnv *,Cb*);
void convertString(Cb*);
void configFonts(winEnv *,Cb* );
#endif /*W07_H_*/