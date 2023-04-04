
#include <stdio.h>
#include <stdlib.h>

void inform(const char *str, char status) {
  switch (status) {
  case 1:
    fprintf(stderr, "%s", str);
    break;
  case -1:
    fprintf(stderr, "%s", str);

    exit(status);
  default:
    break;
  }
}
