#ifndef COMBINATIONS_H_
#define COMBINATIONS_H_
#include <X11/Xlib.h>
#define CELL_COUNT 3
#define CELL_SIZE_FORM 120
// BASE SIZE + BORDER SIZE + OFFSET;
#define OFFSET 5
#define WIN_W 400
#define WIN_H CELL_SIZE_FORM*CELL_COUNT+OFFSET*(CELL_COUNT+1)
#define K_ESC 9
#define ALT 64
typedef struct env {
  Display *dpy;
  Window root;
  Window viewform;
  Window forms[3];
  GC gc[2];
  XRectangle cell;
  Window exit;
} winEnv;

typedef struct ODH { // BINARY OCTAL DEC HEX
  unsigned char bin[CELL_COUNT][1];
  unsigned char *hexOctDec;
  unsigned char len;
} ODH;

void dispatch(winEnv *, ODH *num);
void createEnv(winEnv *);
void freeEnv(winEnv *);
void convertToHexOct(ODH *, unsigned char);
void constructODH(winEnv *, ODH *);
void convertToDec(ODH *);
void eraseConvert(winEnv *env, ODH *num, char);
void invertBit(unsigned char, winEnv *, ODH *);
unsigned char control(Window, winEnv *, ODH *);
unsigned char _pow(unsigned char);
void fill(winEnv *, ODH *);
void keycontrol(unsigned int, winEnv *, ODH *);
#endif /*W07_H_*/