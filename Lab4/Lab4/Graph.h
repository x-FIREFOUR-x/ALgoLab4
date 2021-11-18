#pragma once
#include <vector>
using namespace std;
class Graph
{
	int size;								// к≥льк≥сть вершин
	int** matrix_graph;						// матриц€ сум≥жност≥ графа (1 Ї ребро, 0 - нема ребра)

public:
	Graph();
	Graph(int in_size);
	Graph(const Graph& obj);
	~Graph();

	void set_element(int row, int column, int elem);					// встановити елемент в матрицю 			
	int get_element(int row, int column);								// отримати елемент з матриц≥
	void set_size(int insize);											// встановити к≥льк≥сть вершин
	int get_size();														// отримати к≥льк≥сть вершин
	int count_edge(int number_node);									// к≥льк≥сть дуг вершини

	bool generation(int min_adj_edge, int max_adj_edge);				// генерац≥€ випадкового графа
	bool check_correct_symetric();										// перев≥рка симетричност≥ ≥ дуги на 0 графа
	bool check_correct_num_edge(int min_adj_edge, int max_adj_edge);	// перев≥рка к≥лькост≥ ребер в граф≥
	int count_avarege_edge();											// середнЇ значенн€ ребер в граф≥
};

