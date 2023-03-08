#include "W02.h"
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>

void destroy(const char *errstr) {
  fprintf(stderr, "%s", errstr);
  exit(-1);
}
void allocField(winHandl *field) {
  field->row = (Window *)calloc(field->nParam.arr[NY_F], sizeof(unsigned long));
  field->cells = (arrayOfWinAndColors **)calloc(field->nParam.arr[NY_F],
                                                sizeof(arrayOfWinAndColors *));
  if (field->cells == NULL || field->row == NULL)
    destroy("error allocating memory! {global}");
  for (short i = 0; i < field->nParam.arr[NY_F]; i++) {
    field->cells[i] = (arrayOfWinAndColors *)calloc(
        field->nParam.arr[NX_F], sizeof(arrayOfWinAndColors));

    if (field->cells[i] == NULL)
      destroy("error allocating memory! {local}");
  }
}
void createField(winHandl *field, Display *dpy) {
  allocField(field);

  short i, j;
  int x, y;                  /* windows' location */
  unsigned w, h;             /* windows' size */
  int dx, dy;                /* interwindow distance */
  int src;                   /* screen number */
  int depth;                 /* screen depth */
  XSetWindowAttributes attr; /* created Window attributes */
  XSizeHints hint;
  src = DefaultScreen(dpy);
  depth = DefaultDepth(dpy, src);

  w = field->nParam.arr[NX_F] * field->nParam.arr[CELL_HW];
  h = field->nParam.arr[NY_F] * field->nParam.arr[CELL_HW];
  attr.override_redirect = False;
  attr.background_pixel = WhitePixel(dpy, src);
  x = 0;
  y = 0;
  field->root = XCreateWindow(dpy, DefaultRootWindow(dpy), 0, 0, w, h, 0, depth,
                              InputOutput, CopyFromParent,
                              (CWOverrideRedirect | CWBackPixel), &attr);
  hint.flags = (PMinSize | PMaxSize | PPosition);
  hint.min_width = hint.max_width = w;
  hint.min_height = hint.max_height = h;
  hint.x = x;
  hint.y = y;
  XSetNormalHints(dpy, field->root, &hint);

  attr.override_redirect = True;
  attr.background_pixel = WhitePixel(dpy, src);
  w = field->nParam.arr[NX_F] * field->nParam.arr[CELL_HW];
  h = field->nParam.arr[CELL_HW];
  x = 0;
  dy = h;
  for (i = 0, y = 0; i < field->nParam.arr[NY_F]; i++, y += dy)
    field->row[i] = XCreateWindow(dpy, field->root, x, y, w, h, 0, depth,
                                  InputOutput, CopyFromParent,
                                  (CWOverrideRedirect | CWBackPixel), &attr);

  attr.override_redirect = True;
  attr.event_mask = (ButtonPressMask | KeyPressMask);
  attr.background_pixel = 0xFF0000;
  w = field->nParam.arr[CELL_HW];
  h = field->nParam.arr[CELL_HW];
  dx = w;
  for (i = 0, y = 0; i < field->nParam.arr[NY_F]; i++)
    for (j = 0, x = 0; j < field->nParam.arr[NX_F]; j++, x += dx) {
      // field->cells[i][j].backgroundColor = 0; legacy function
      field->cells[i][j].win = XCreateWindow(
          dpy, field->row[i], x, y, w, h, 0, depth, InputOutput, CopyFromParent,
          (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
    }
  /* Display windows */
  XMapWindow(dpy, field->root);
  XMapSubwindows(dpy, field->root);
  for (i = 0; i < field->nParam.arr[NY_F]; i++)
    XMapSubwindows(dpy, field->row[i]);

  XStoreName(dpy, field->root, "W02");
}

/*short getValue(byte i){ //i==0 ->X i==2->Y;i==4-> size of cell;
    if (nParam.arr[i+1])
    return nParam.arr[i+1];

    return nParam.arr[i]+nParam.arr[i+1]*256;
}*/

fieldParametres parseFieldParametres(Display *dpy, const char *fieldPar,
                                     const char *cellPar) {
  fieldParametres nParam;
  unsigned int params[] = {16, 4, 32, 32}; // X Y BX BY
  byte error = 0;
  byte a;
  unsigned int *Z0 = (unsigned int *)malloc(sizeof(unsigned int));

  if (XParseGeometry(fieldPar, Z0, Z0, params, params + 1) != 12) {
    fprintf(stderr, "\tWARNING: UNABLE TO CORRECTLY PARSE GEOMETRY OF FIELD OR "
                    "IT IS NOT GIVEN\n");
    error = 1;
  }
  if ((a = XParseGeometry(cellPar, Z0, Z0, params + 2, params + 3)) == 0) {
    fprintf(stderr, "\tWARNING: UNABLE TO CORRECTLY PARSE GEOMETRY OF CELL OR "
                    "IT IS NOT GIVEN\n");
    error++;
  } else if (a == 4) {
    *(params + 3) = *(params + 2);
  } else if (a == 8) {
    *(params + 2) = *(params + 3);
  }
  free(Z0);
  if (!(params) || !*(params + 1) || !*(params + 2) || !*(params + 3)) {
    fprintf(stderr, "\tWARNING: ZERO VALUE\n");
    error = 1;
  }
  if (*(params + 2) != *(params + 3)) {
    fprintf(stderr, "\tWARNING: CELL MUST BE SQUARE! X=Y\n");
    error = 1;
  }
  if (*(params) * (*(params + 2)) > DisplayWidth(dpy, DefaultScreen(dpy)) ||
      *(params + 1) * (*(params + 3)) >
          DisplayHeight(dpy, DefaultScreen(dpy))) {
    fprintf(stderr,
            "\tWARNING: SCREEN SIZE %dx%d\n\t\t FIELD IS BIGGER THEN SCEEN\n",
            DisplayHeight(dpy, DefaultScreen(dpy)),
            DisplayWidth(dpy, DefaultScreen(dpy)));
    error = 1;
  }
  if (error) {
    fprintf(stderr, "WARNINGS WERE FIND WHILE BUILDING THE FIELD\nDEFAULT "
                    "SETTING WILL BE ");
    params[0] = 16;
    params[1] = 4;
    params[2] = 32;
    params[3] = 32;
  }
  fprintf(stderr, "APPLIED:\n");
  for (byte i = 1; i < 5; i++) {
    if (i < 4)
      nParam.arr[i - 1] = params[i - 1];
    if (i != 1)
      (i % 2) ? fprintf(stderr, "\tFIELD\n") : fprintf(stderr, "x");
    fprintf(stderr, "%d", params[i - 1]);
  }
  fprintf(stderr, "\tCELL\n");
  return nParam;
}

void freeField(winHandl *field) {
  /* row index */
  for (unsigned short i = 0; i < field->nParam.arr[NY_F]; i++) {
    free(field->cells[i]);
  } /* for */
  free(field->cells);
  free(field->row);
} /* dealloc */