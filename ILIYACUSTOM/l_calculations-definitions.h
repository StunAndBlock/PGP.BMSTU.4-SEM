#ifndef L_CALCULATIONS_DEFINITIONS_H
#define L_CALCULATIONS_DEFINITIONS_H
#include "./g_configurations.h"
#include "./g_environment-class.h"
#include "./math.h"
#include "./stdio.h"
#define _USE_MATH_DEFINES
#define RAD_STEP (DEGREE_STEP*M_PI/180)

#define SINV(bit) ((bit)==('1')) ? ('0') : ('1'); 
void calculateTraces(Envi*);


#endif //END OF L_CALCULATIONS-DEFINITIONS_H