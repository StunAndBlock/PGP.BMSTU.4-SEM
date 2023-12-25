#ifndef GI_CLASS_DECL_HPP
#define GI_CLASS_DECL_HPP
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "./unlock.hpp"

#define DRAW_FIELD_BACKGROUND_COLOR_HEX     0xFFFFFF
#define DFB                                 DRAW_FIELD_BACKGROUND_COLOR_HEX

#define ERASE_COLOR                         DRAW_FIELD_BACKGROUND_COLOR_HEX
#define PAINT_COLOR                         0x000000

#define MIN_DRAW_FIELD_WIDTH                RESOLUTION
#define MIN_DRAW_FIELD_HEIGHT               RESOLUTION

#define CUSTOM_INTERNAL_BORDER_WIDTH        16
#define CUSTOM_INTERNAL_BORDER_HEIGHT       16
#define CIBW                                CUSTOM_INTERNAL_BORDER_WIDTH
#define CIBH                                CUSTOM_INTERNAL_BORDER_HEIGHT

#define _XK_ESCAPE 0xff1b
class Genv {
    public:
    Genv();
    ~Genv();
    void graphics_init();
    void windows_init(float);
    int dispatch();
    void draw_hilbert(const int , int ,uint16_t(*)[2]);
    private:
    Display* dpy;
    int scr;
    int depth;
    Window root;
    
    Window main;
    Window draw_field;
    Pixmap hilbert_pix;
    int scale;
    GC paint;
    GC erase;
};











#endif /*GI_CLASS_DECL_HPP END <--*/