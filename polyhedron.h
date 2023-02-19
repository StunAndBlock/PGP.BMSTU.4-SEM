#ifndef POLYHEDRON_H_
#define POLYHEDRON_H_
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#define MB0 3       // 3       /* 4-угольная внешняя грань */
#define NF3 3       // 18       /* 4 3-угольные внутренние грани */
/* #define NF4 0 */ /* 0 4-угольных внутренних граней */
/* #define NF5 0 */ /* 0 5-угольных внутренних граней */
/* #define NF6 0 */ /* 0 6-угольных внутренних граней */
/* #define NF7 0 */ /* 0 7-угольных внутренних граней */
/* #define NF8 0 */ /* 0 8-угольных внутренних граней */
#define NCOLOR 4
#define DEFTONE 0 /* номер цвета грани по умолчанию */
#define VDOT 8    /* диаметр вершин графа */
#define EWIDTH 2  /* толщина ребер графа (<VDOT) */
#define NUNIT 18  /* диапазон градуировка схемы  %8=0*/
#define NFACE                                               \
    (NF3) /* (NF3+ NF4+ NF5                                 \
                      + NF6+ NF7+NF8)                       \
#define NEDGE ((3*NF3 + MB0)/2)  /* ((3*NF3 + 4*NF4         \
                                            + 5*NF5 + 6*NF6 \
                                            + 7*NF7 + 8*NF8 \
                                            + MB0)/2) */
#define NEDGE                                                             \
    ((3 * NF3 + MB0) / 2) /* ((3*NF3 + 4*NF4                              \
                                                          + 5*NF5 + 6*NF6 \
                                                          + 7*NF7 + 8*NF8 \
                                                          + MB0)/2) */

#define NVERT (NEDGE - (NFACE + 1) + 2)
typedef XPoint XVertex;
typedef XSegment XEdge;

typedef struct { /* Структура грани */
    XPoint* top; /* Адрес набора вершин */
    int Cn;      /* Число вершин */
    int tone;    /* Номер цвета */
    Region regi; /* Региональная зона */
} XFace;
typedef struct {     /* Структура многоугольного графа */
    XVertex* vertex; /* Адрес массива вершин */
    XEdge* edge;     /* Адрес массива ребер */
    XFace* face;     /* Адрес массива граней */
} XPolyGraph;

int assoc(XPolyGraph*);
GC congraph(Display*);
Window wingraph(Display*, char*);
int colorite(Display*);
int regraph(Display*, Window, GC, int);
int reset(Display*, Window, int);
int reface(Display*, Window, GC, int);
/*Дисплейный модуль (pyramid2) */
int relink(XPolyGraph*);
int retrace();
int resize(unsigned, unsigned);
int rescale(unsigned, unsigned);
int rebuild();
int reconf(unsigned, unsigned);
int zotone(int, int);
/*Контрольный модуль (pyramid0) */
int rekey(XEvent*);
int dispatch(Display*, Window, GC);
int main(int argc, char* argv[]);
Window canvas(Display* dpy);
#endif
