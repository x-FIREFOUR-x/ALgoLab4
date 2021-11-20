#pragma once
#include "Graph.h"
#include <vector>
#include<algorithm>
using namespace std;
class Algorithm
{
private:
	vector<vector<int>> cliques;			// вектор кл≥к в попул€ц≥њ (кл≥ка булевий вектор з 1(Ї вершина) ≥ 0(нема вершини)) 
	vector<int> sizes_cliques;				// вектор розм≥р≥в кл≥к (к≥льк≥сть 1 в кл≥ках)
public:
	void genetic_algo(Graph& graph, int& count_iter);				// генетичний алгоритм дл€ задач≥ кл≥ка

private:
	void start_cliques(Graph& graph);				// генеруЇм початков≥ кл≥ки (стартову попул€ц≥ю) вс≥ можлив≥ кл≥ки з розм≥ром 1
	bool is_clique(Graph& graph, vector<int> clq);
	void sort_cliques();

public:
	
	int get_amount_cliques();						// отримати к≥льк≥сть кл≥к (персон в попул€ц≥њ)
	vector<int> get_clique(int number);				// отримати кл≥ку з номером number
	int get_size_clique(int number);				// отримати розм≥р кл≥ки(к≥льк≥сть вершин) з номером number



};

