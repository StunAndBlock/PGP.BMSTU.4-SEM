#include "W21.h"
#include "stdio.h"

unsigned char checkForOverlap(Window root, Window win, Display *dpy) {
  Window parent;
  Window *children;
  unsigned nchildren;
  if (!XQueryTree(dpy, root, &root, &parent, &children, &nchildren)) {
    inform("Failed to query top level windows list\n", 1);
    return 1;
  }
  // sfprintf(stderr, "=%d=", nchildren);
  for (unsigned short i = 0; i < nchildren; i++) {
    if (win == children[i]) {
      fprintf(stderr, "=%d=", i);
    }
  }
  return 16;
}