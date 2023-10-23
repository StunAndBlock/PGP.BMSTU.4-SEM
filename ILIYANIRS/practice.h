#ifndef PRACTICE_H_
#define PRACTICE_H_

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <iostream>
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include <algorithm>
#define SCALE 80
#define DOT_SCALE SCALE*2
#define ARC_SCALE SCALE/2
#define LINE_WIDTH 2

#define DESMOS_SCALE 5					//0<=x<=3 + 2 extra space x=leftborded-0,0-1,1-2,2-3,3-rightborder

#define DRAW_FIELD_WIDTH DOT_SCALE*DESMOS_SCALE
#define OPTION_FIELD_WIDTH 200
#define WIN_WIDTH DRAW_FIELD_WIDTH+OPTION_FIELD_WIDTH+2
#define BUTTON_WIDTH OPTION_FIELD_WIDTH

#define DRAW_FIELD_HEIGHT DOT_SCALE*DESMOS_SCALE
#define WIN_HEIGHT DRAW_FIELD_HEIGHT+2
#define OPTION_FILED_HEIGHT WIN_HEIGHT
#define BUTTON_HEIGHT 50
class Vertices{
public:
	XPoint* points;
	XArc* external_arcs;
	XArc* blank_arcs;
	XArc* internal_arcs;
	std::vector<std::string> vertices_numbers_str_arr;
};

class Graph {
private:
	std::vector<size_t> * adjacency_matrix; // матрица смежности
	size_t number_of_vertices; // количество вершин
	size_t number_of_ribs; // количество ребер
	bool * vertex_label; // массив меток
	std::vector<std::vector<size_t>> tree;
public:
	explicit Graph(const std::string & str); // конструктор (аргумент - имя файла)
	~Graph(); // деструктор
	void algorithmBFS();
	size_t get_num_of_ribs();
	size_t get_num_of_vertices();
	std::vector<size_t>* get_adjacency_matrix();
	std::vector<std::vector<size_t>> get_tree();
};


class Environment : public Graph{
private:
	Display* dpy;
	Window main_win;
	Window option_field_win;
	Window draw_button_win;
	Window draw_field_win;
	GC gc_white;
	GC gc_black;
	GC gc_red;
	XFontStruct* fn;
	int scr;
	int depth;
	Vertices vertices;
	std::vector<std::vector<double> >graph_template;
public:
	Environment(const std::string & str );
	~Environment();
	void dispatch(size_t);
	void prepareGraph(size_t);
	void drawGraph(size_t);
	void drawTree(size_t);
};


std::vector<std::vector<double> > get_template(size_t);

#endif