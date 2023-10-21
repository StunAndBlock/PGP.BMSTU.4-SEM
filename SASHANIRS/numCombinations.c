#include "combinations.h"
#include <stdio.h>
#include <stdlib.h>

unsigned char control(Window win, winEnv *env, ODH *num) {
  if (win != env->exit) {

  } else {
    return 0;
  }
  return 1;
}

void keycontrol(unsigned int keycode, winEnv *env, ODH *num) {
  switch (keycode) {
  case K_ESC:

    break;
  case ALT:
    break;
  default:
    break;
  }
}
