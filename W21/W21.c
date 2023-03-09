#include "W21.h"
#include <stdio.h>
#include <stdlib.h>

int main(unsigned short argc, char *argv[]) {
  if (argc < 2) {
    inform("no boxes inputted\nEXMAPLE: ./<programm_name> 14x23 143x10\n", -1);
  }
    winHandl newEnv;
    createEnv(&newEnv);
  return 0;
}

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