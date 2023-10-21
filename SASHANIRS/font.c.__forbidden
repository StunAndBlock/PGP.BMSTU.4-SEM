#include "X11/Xlib.h"
#include "stdio.h"





int main(){
    Display * dpy = XOpenDisplay(NULL);

    int ttt=0;
    char** names = XListFonts(dpy, "*--0-0-0-0-*",200,&ttt);
    for(int i=0;i<200;i++){
        printf("%s\n",names[i]);
    }
}