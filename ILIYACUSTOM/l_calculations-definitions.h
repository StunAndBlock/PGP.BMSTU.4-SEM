#ifndef L_CALCULATIONS_DEFINITIONS_H
#define L_CALCULATIONS_DEFINITIONS_H
#include "./g_configurations.h"
#include "./g_environment-class.h"
#include "math.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "time.h"
#define _USE_MATH_DEFINES       //LEGACY
#define RAD_STEP (DEGREE_STEP*M_PI/180)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#define rand_degree() ((rand() % (360 - 0 + 1)) + 0)
#define SINV(bit) ((bit)==('1')) ? ('0') : ('1'); 
void calculateTraces(Envi*);
int limit_exceded(int);
int is_collision(XRectangle*);
XRectangle special_next_trace(XRectangle, XRectangle);
XRectangle default_next_trace(XRectangle, double );

#endif //END OF L_CALCULATIONS-DEFINITIONS_H