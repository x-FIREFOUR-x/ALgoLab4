#pragma once
#include "Graph.h"
#include <vector>
#include<algorithm>
using namespace std;
class Algorithm
{
private:

	int chance_mutation = 50;				// шанс мутації в процентах
	vector<vector<int>> cliques;			// вектор клік в популяції (кліка булевий вектор з 1(є вершина) і 0(нема вершини)) 
	vector<int> sizes_cliques;				// вектор розмірів клік (кількість 1 в кліках)
public:
	void genetic_algo(Graph& graph, int& count_iter);				// генетичний алгоритм для задачі кліка

private:
	void start_cliques(Graph& graph);				// генеруєм початкові кліки (стартову популяцію) всі можливі кліки з розміром 1
	bool is_clique(Graph& graph, vector<int> clq);
	void sort_cliques();

	pair<vector<int>, int> crossing_one_point(Graph& graph, int pr1, int pr2);

	bool mutation1(Graph& graph, pair<vector<int>, int>& child);				// 1 різновид мутації (заміна випадкового 0 гена на 1 )

	int calculate_size_clique(vector<int>& clq);								// підрахунок кількості вершин в кліці (clq)
	int search_best_child(Graph& graph, vector<int>& sizes_childrens);			// пошук індикса найкращого сина по кількості їх вершин (sizes_childrens)
public:
	
	int get_amount_cliques();						// отримати кількість клік (персон в популяції)
	vector<int> get_clique(int number);				// отримати кліку з номером number
	int get_size_clique(int number);				// отримати розмір кліки(кількість вершин) з номером number



};

