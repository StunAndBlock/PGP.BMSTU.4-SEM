#include "W02.h"
#include "W02keycodes.h"
#include <stdio.h>

unsigned long palette[(NCOLOR + 1)];

int paletteMapCreate(Display *dpy) {
  Colormap cmap = DefaultColormap(dpy, DefaultScreen(dpy)); /* color map */
  XColor rgb; /* Structure for color allocation */
  int i;      /* color index */
  static char *spector[] = {
      "#ff0000", /* red */
      "#00ff00", /* green */
      "#0000ff"  /* blue */
  };             /* color spector */
  for (i = 0; i < (NCOLOR); i++) {
    XParseColor(dpy, cmap, spector[i], &rgb);
    XAllocColor(dpy, cmap, &rgb);
    palette[i] = rgb.pixel;

  } /* for */

  return (0);
}

/*typedef struct pos {
  short i;
  short j;
} pos;
pos findWin(arrayOfWinAndColors **cells, Window current,
            fieldParametres nParam) {
  pos finded;
  for (unsigned short i = 0; i < nParam.arr[1]; i++)
    for (unsigned short j = 0; j < nParam.arr[0]; j++)
      if (cells[i][j].win == current) {
        finded.i = i;
        finded.j = j;
        return finded;
      }
  return finded;
}
void changeColor_legacy(Display *dpy, Window current, winHandl *field) {
  pos finded = findWin(field->cells, current, field->nParam);
  field->cells[finded.i][finded.j].backgroundColor++;
  if (field->cells[finded.i][finded.j].backgroundColor == 3)
    field->cells[finded.i][finded.j].backgroundColor = 0;
  XSetWindowBackground(
      dpy, current, palette[field->cells[finded.i][finded.j].backgroundColor]);
  XClearWindow(dpy, current);
} */ /*legacy*/

void changeColor(Display *dpy, Window current, byte color) {

  XSetWindowBackground(dpy, current, palette[color]);
  XClearWindow(dpy, current);
}

void changeColorAll(Display *dpy, winHandl *field, byte color) {
  for (unsigned short i = 0; i < field->nParam.arr[NY_F]; i++)
    for (unsigned short j = 0; j < field->nParam.arr[NX_F]; j++)
      changeColor(dpy, field->cells[i][j].win, color);
}

void mouseDrive(Display *dpy, XEvent *ev) {
  switch (ev->xbutton.button) {
  case M_BUTTON_LEFT:
    changeColor(dpy, ev->xbutton.window, 0);
    break;
  case M_BUTTON_MIDDLE:

    changeColor(dpy, ev->xbutton.window, 1);
    break;
  case M_BUTTON_RIGT:
    changeColor(dpy, ev->xbutton.window, 2);
    break;
  default:
    /// fprintf(stderr, "M_BUTTON :%d ", ev->xbutton.button);
    break;
  }
}

void kbDrive(Display *dpy, XEvent *ev, winHandl *field, byte *flag) {

  switch (ev->xkey.keycode) {
  case K_ESC:
    *flag = 0;
    break;
  case K_Rr:

    changeColorAll(dpy, field, 0);
    break;
  case K_Gg:

    changeColorAll(dpy, field, 1);
    break;
  case K_Bb:
    changeColorAll(dpy, field, 2);
    break;
  default:
    // fprintf(stderr, "R_KEY: %d", ev->xkey.keycode);
    break;
  }
}
