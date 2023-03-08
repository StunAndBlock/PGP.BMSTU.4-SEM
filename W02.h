#ifndef W02_H_
#define W02_H_
#include <X11/Xlib.h>
typedef unsigned char byte;  
#define NCOLOR 3
#define NX_F 0
#define NY_F 1
#define CELL_HW 2
typedef struct fieldParametres{
   unsigned short arr[3]; //[12][0][4][0][32][0] 12x4 32 if arr[6] type byte;
} fieldParametres;

typedef struct arrayOfWinAndColors{
    Window win;
    //byte backgroundColor; //legacy
} arrayOfWinAndColors;

typedef struct winHandl{
    arrayOfWinAndColors** cells;
    Window root; 
    Window *row;
    fieldParametres nParam;
} winHandl;



fieldParametres parseFieldParametres(Display* ,const char* ,const char* );
void createField(winHandl* ,Display* );
int paletteMapCreate(Display*);
void changeColor_legacy(Display*,Window,winHandl*); //legacy
void changeColor(Display*,Window,byte);
void changeColorAll(Display*, winHandl* ,byte ); 
void allocField(winHandl*);
void freeField(winHandl*);
void kbDrive(Display* ,XEvent*,winHandl* ,byte* );
void mouseDrive(Display* ,XEvent*);

#endif /* W02_H_ */