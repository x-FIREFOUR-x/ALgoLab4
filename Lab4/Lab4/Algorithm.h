#pragma once
#include "Graph.h"
#include <vector>
#include<algorithm>
using namespace std;
class Algorithm
{
private:

	int chance_mutation = 50;				// ���� ������� � ���������
	vector<vector<int>> cliques;			// ������ ��� � ��������� (���� ������� ������ � 1(� �������) � 0(���� �������)) 
	vector<int> sizes_cliques;				// ������ ������ ��� (������� 1 � �����)
public:
	void genetic_algo(Graph& graph, int& count_iter);				// ���������� �������� ��� ������ ����

private:
	void start_cliques(Graph& graph);				// ������� �������� ���� (�������� ���������) �� ������ ���� � ������� 1
	bool is_clique(Graph& graph, vector<int> clq);
	void sort_cliques();

	pair<vector<int>, int> crossing_one_point(Graph& graph, int pr1, int pr2);

	bool mutation1(Graph& graph, pair<vector<int>, int>& child);				// 1 ������� ������� (����� ����������� 0 ���� �� 1 )

	int calculate_size_clique(vector<int>& clq);								// ��������� ������� ������ � ���� (clq)
	int search_best_child(Graph& graph, vector<int>& sizes_childrens);			// ����� ������� ���������� ���� �� ������� �� ������ (sizes_childrens)
public:
	
	int get_amount_cliques();						// �������� ������� ��� (������ � ���������)
	vector<int> get_clique(int number);				// �������� ���� � ������� number
	int get_size_clique(int number);				// �������� ����� ����(������� ������) � ������� number



};

