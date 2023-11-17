#ifndef L_CALCULATIONS_DEFINITIONS_H
#define L_CALCULATIONS_DEFINITIONS_H
#include "./g_configurations.h"

#define SINV(bit) ((bit)==('1')) ? ('0') : ('1'); 
void refill(char[BIT_WINDOW_AMOUNT]);
void updateComplement(char[BIT_WINDOW_AMOUNT],char[BIT_WINDOW_AMOUNT]);
void updateBinary(char source[BIT_WINDOW_AMOUNT],char binary[BIT_WINDOW_AMOUNT]);

#endif //END OF L_CALCULATIONS-DEFINITIONS_H