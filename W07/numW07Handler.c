#include "W07.h"
#include <stdio.h>
#include <stdlib.h>
void constructODH(winEnv *env, ODH *num) {
  for (unsigned char i = 0; i < CELL_COUNT; i++) {
    num->bin[i][0] = 0 + '0';
  }
}

void eraseConvert(winEnv *env, ODH *num, char i) {
  convertToDec(num);
  XDrawString(env->dpy, env->info[3], env->gc[i], env->cell.x - (num->len * 2),
              env->cell.y, num->hexOctDec, num->len);
  free(num->hexOctDec);
  convertToHexOct(num, 3);
  XDrawString(env->dpy, env->info[1], env->gc[i], env->cell.x - (num->len * 2),
              env->cell.y, num->hexOctDec, num->len);
  free(num->hexOctDec);
  convertToHexOct(num, 4);
  XDrawString(env->dpy, env->info[5], env->gc[i], env->cell.x - (num->len * 2),
              env->cell.y, num->hexOctDec, num->len);
  free(num->hexOctDec);
}

void convertToHexOct(ODH *num, unsigned char base) {
  unsigned int part = 0;
  unsigned int addition = 0;
  int j = 1;
  unsigned int hexOctMapSize = 0;
  if (CELL_COUNT % base == 0) {
    hexOctMapSize = CELL_COUNT / base;
    addition = 0;
  } else {
    hexOctMapSize = CELL_COUNT / base + 1;
    addition = base - CELL_COUNT % base;
  }
  num->len = hexOctMapSize;
  num->hexOctDec = malloc(hexOctMapSize * sizeof(unsigned char));
  int k = hexOctMapSize - 1;
  for (unsigned int i = 1; i <= CELL_COUNT + addition; i++, j++) {
    if (i <= CELL_COUNT) {
      if (num->bin[CELL_COUNT - i][0] == '1')
        part += _pow((i - 1) % base);
    } else {
      part += 0;
    }
    if (i % base == 0) {
      // fprintf(stderr, "(%d)", part);
      if (part >= 0 && part <= 9) {
        num->hexOctDec[k--] = part + '0';
      } else {
        num->hexOctDec[k--] = part % 10 + 'A';
      }

      part = 0;
    }
  }
}

unsigned char _pow(unsigned char exp) { return 1 << exp; }

void convertToDec(ODH *num) {
  unsigned char sum = 0;
  for (unsigned char i = 0; i < CELL_COUNT; i++) {
    if (num->bin[i][0] == '1') {
      sum += _pow(CELL_COUNT - 1 - i);
    }
  }
  unsigned char temp = sum;
  unsigned char i = 0;

  if (sum) {
    while (temp != 0) {
      temp /= 10;
      i++;
    }
    num->len = i;
    num->hexOctDec = (unsigned char *)malloc(sizeof(unsigned char) * num->len);
    while (sum != 0) {
      num->hexOctDec[i - 1] = sum % 10 + '0';
      sum /= 10;
      if (i)
        i--;
    }
  } else {
    num->len = 1;
    num->hexOctDec = (unsigned char *)malloc(sizeof(unsigned char) * num->len);
    num->hexOctDec[0] = 0 + '0';
  }
}
unsigned char find(Window win, winEnv *env) {
  for (unsigned char i = 0; i < CELL_COUNT; i++) {
    if (win == env->cellArr[i]) {
      return i;
    }
  }
}

void invertBit(unsigned char i, winEnv *env, ODH *num) {
  XDrawString(env->dpy, env->cellArr[i], env->gc[1], env->cell.x, env->cell.y,
              num->bin[i], 1);
  if (num->bin[i][0] == '0') {
    num->bin[i][0] = 1 + '0';
  } else {
    num->bin[i][0] = 0 + '0';
  }
  // fprintf(stderr, "%d", num->bin[i][0]);
  XDrawString(env->dpy, env->cellArr[i], env->gc[0], env->cell.x, env->cell.y,
              num->bin[i], 1);
}

void fillZero(winEnv *env, ODH *num) {
  for (unsigned char i = 0; i < CELL_COUNT; i++) {
    XDrawString(env->dpy, env->cellArr[i], env->gc[0], env->cell.x, env->cell.y,
                num->bin[i], 1);
  }
}

void fill(winEnv *env, ODH *num) {
  const char *infoPanel[] = {"OCT:", "DEC:", "HEX:"};
  fillZero(env, num);
  for (unsigned char i = 0; i < 6; i++) {
    if (!(i % 2))
      XDrawString(env->dpy, env->info[i], env->gc[0], env->cell.x - 10,
                  env->cell.y, infoPanel[i / 2], 4);
  }
  XDrawString(env->dpy, env->exit, env->gc[0], env->cell.x - 11, env->cell.y,
              "Exit", 4);
}

unsigned char control(Window win, winEnv *env, ODH *num) {
  if (win != env->exit) {
    unsigned char i = find(win, env);
    eraseConvert(env, num, 1);
    invertBit(i, env, num);
    eraseConvert(env, num, 0);
  } else {
    return 0;
  }
  return 1;
}

void keycontrol(unsigned int keycode, winEnv *env, ODH *num) {
  switch (keycode) {
  case K_ESC:
    eraseConvert(env, num, 1);
    for (unsigned char i = 0; i < CELL_COUNT; i++) {
      XDrawString(env->dpy, env->cellArr[i], env->gc[1], env->cell.x,
                  env->cell.y, num->bin[i], 1);
    }
    constructODH(env, num);
    fillZero(env, num);
    eraseConvert(env, num, 0);
    break;
  case ALT:
    eraseConvert(env, num, 1);
    for (unsigned char i = 0; i < CELL_COUNT; i++) {
      invertBit(i, env, num);
    }
    eraseConvert(env, num, 0);
    break;
  default:
    break;
  }
}
