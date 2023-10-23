#include "practice.h"

int main() {
	std::string str;
	std::cout << "Введите файл с реализацией графа в виде списка ребер: ";
	std::cin >> str;
	Environment g(str);
	g.algorithmBFS();
	std::vector<std::vector<size_t>> puk = g.get_tree();
	g.prepareGraph(g.get_num_of_vertices());
	g.dispatch(g.get_num_of_vertices());
	return 0;
}