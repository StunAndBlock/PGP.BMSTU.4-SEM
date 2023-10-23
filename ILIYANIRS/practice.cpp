#include "practice.h"
#include "figures.hpp"

Graph::Graph(const std::string & str) { // конструктор (аргумент - имя файла)
	std::ifstream fin;
	fin.open(str);
	if (!fin.is_open()) { // проверка на открытие файла
		std::cout << "Файл " << str << " не удалось открыть!" << std::endl;
		exit(EXIT_FAILURE);
	}
	fin >> number_of_vertices;
	fin >> number_of_ribs;
	size_t u, v;
	adjacency_matrix = new std::vector<size_t>[number_of_vertices];
	for (size_t i = 0; i < number_of_ribs; ++i) {
        fin >> u >> v; // ребро между вершинами u и v
        adjacency_matrix[u].push_back(v);
        adjacency_matrix[v].push_back(u); // добавляем обратное ребро для неориентированного графа
    }
    vertex_label = new bool[number_of_vertices];
    for (size_t i = 0; i < number_of_vertices; ++i)
    	vertex_label[i] = false;
	fin.close();
}

Graph::~Graph() { // деструктор
	delete[] adjacency_matrix;
	delete[] vertex_label;
}

Environment::~Environment() { // деструктор
	delete[] vertices.blank_arcs;
	delete[] vertices.external_arcs;
    delete[] vertices.internal_arcs;
    delete[] vertices.points;
    XFreeGC(dpy,gc_black);
    XFreeGC(dpy,gc_white);
    XFreeGC(dpy,gc_red);
    XFreeFont(dpy,fn);
    XCloseDisplay(dpy);
}

void Graph::algorithmBFS() {
	srand(time(NULL));
	size_t start = rand() % number_of_vertices; // определяем корень
	std::queue<size_t> q;
    std::vector<size_t> temp;
    q.push(start);
    vertex_label[start] = true; // помечаем корень
    while (!q.empty()) {
        size_t current_vertex = q.front();
        q.pop();
        for (size_t i = 0; i < adjacency_matrix[current_vertex].size(); ++i) { // идем по смежным вершинам
            size_t next = adjacency_matrix[current_vertex][i]; 
            if (!vertex_label[next]) {
                q.push(next);
                vertex_label[next] = true;
                temp.push_back(current_vertex);
                temp.push_back(next);
                tree.push_back(temp);
                temp.clear();
                //std::copy(temp.begin(),temp.end(),std::back_inserter(tree));
                std::cout << current_vertex << " " << next << std::endl; // добавляем ребро в дерево 
            }
        }
    }
}

size_t Graph::get_num_of_ribs(){
    return number_of_ribs;
}

size_t Graph::get_num_of_vertices(){
    return number_of_vertices;
}
std::vector<size_t>* Graph::get_adjacency_matrix(){
    return adjacency_matrix;
}
std::vector<std::vector<size_t>> Graph::get_tree(){
    return tree;
}

std::vector<std::vector<double> > get_template(size_t number_of_vertices){
    switch (number_of_vertices)
    {
    case 4:
        return tetrahedron_arr;
        break;
    case 6:
        return octahedron_arr;
        break;
    case 8:
        return cube_arr;
        break;
    case 12:
        return icosahedron_arr;
        break;
    case 20:
    return dodecahedron_arr;
        break;
    default:
        break;
    }
    return tetrahedron_arr;
}


void Environment::prepareGraph(size_t number_of_vertices){
    graph_template = get_template(number_of_vertices);
    vertices.points = new XPoint[number_of_vertices];
    vertices.external_arcs = new XArc[number_of_vertices];
    vertices.blank_arcs = new XArc[number_of_vertices];
    vertices.internal_arcs = new XArc[number_of_vertices];
    vertices.vertices_numbers_str_arr = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20"};
        for(size_t i = 0; i<number_of_vertices; i++){
            vertices.points[i].x=graph_template[i][0]*DOT_SCALE;
            vertices.points[i].y=graph_template[i][1]*DOT_SCALE;
            vertices.external_arcs[i].height=ARC_SCALE;
            vertices.external_arcs[i].width=ARC_SCALE;
            vertices.external_arcs[i].x = vertices.points[i].x - vertices.external_arcs[i].height/2;
            vertices.external_arcs[i].y = vertices.points[i].y - vertices.external_arcs[i].width/2;
            vertices.external_arcs[i].angle1=0;
            vertices.external_arcs[i].angle2=360*64;
            vertices.blank_arcs[i].height=vertices.external_arcs[i].height-LINE_WIDTH;
            vertices.blank_arcs[i].width=vertices.external_arcs[i].width-LINE_WIDTH;
            vertices.blank_arcs[i].x = vertices.points[i].x - vertices.blank_arcs[i].height/2;
            vertices.blank_arcs[i].y = vertices.points[i].y - vertices.blank_arcs[i].width/2;
            vertices.blank_arcs[i].angle1=vertices.external_arcs[i].angle1;
            vertices.blank_arcs[i].angle2=vertices.external_arcs[i].angle2;
            vertices.internal_arcs[i].height=vertices.external_arcs[i].height*0.8;
            vertices.internal_arcs[i].width=vertices.external_arcs[i].width*0.8;
            vertices.internal_arcs[i].x = vertices.points[i].x - vertices.internal_arcs[i].height/2;
            vertices.internal_arcs[i].y = vertices.points[i].y - vertices.internal_arcs[i].width/2;
            vertices.internal_arcs[i].angle1=vertices.external_arcs[i].angle1;
            vertices.internal_arcs[i].angle2=vertices.external_arcs[i].angle2;

        }
        
}






