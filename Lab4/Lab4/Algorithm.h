#pragma once
#include "Graph.h"
#include <vector>
#include<algorithm>
using namespace std;
class Algorithm
{
private:
	int n_start_cliques = 15;
	int chance_mutation = 50;				// ���� ������� � ���������
	vector<vector<int>> cliques;			// ������ ��� � ��������� (���� ������� ������ � 1(� �������) � 0(���� �������)) 
	vector<int> sizes_cliques;				// ������ ������ ��� (������� 1 � �����)
public:
	void genetic_algo(Graph& graph, int& count_iter, int num_crossing, int num_mutation, int num_local_up);				// ���������� �������� ��� ������ ����

private:
	void start_cliques(Graph& graph);				// ������� �������� ���� (�������� ���������) �� ������ ���� � ������� 1
	void start_rand_n_cliques(Graph& graph);		// ������� ���������� n ���
	bool is_clique(Graph& graph, vector<int> clq);	// ��������� �� �������� � �����
	void sort_cliques();							// ����������� ���� �� �������� ������� ������

	pair<vector<int>, int> crossing_one_point(Graph& graph, int pr1, int pr2);		// ����������� �����������
	pair<vector<int>, int> crossing_two_point(Graph& graph, int pr1, int pr2);		// ���������� �����������
	pair<vector<int>, int> uniform_crossing(Graph& graph, int pr1, int pr2);		// �������� �����������

	bool mutation1(Graph& graph, pair<vector<int>, int>& child);				// 1 ������� ������� (����� ������ ��� ���������� ����)
	bool mutation2(Graph& graph, pair<vector<int>, int>& child);				// 2 ������� ������� (������� ����������� ����)
	bool mutation3(Graph& graph, pair<vector<int>, int>& child);				// 3 ������� ������� (�������� ��� � ������ � ��� �� ����)

	bool local_upgrade1(Graph& graph, pair<vector<int>, int>& child);				// 1 ������� ���������� ���������� (����� ����������� 0 ���� �� 1)
	bool local_upgrade2(Graph& graph, pair<vector<int>, int>& child);				// 2 ������� ���������� ���������� (��������� ������� � ���� �� �� ���� � �������� � ���� )

	int calculate_size_clique(vector<int>& clq);								// ��������� ������� ������ � ���� (clq)
	int search_best_child(Graph& graph, vector<int>& sizes_childrens);			// ����� ������� ���������� ���� �� ������� �� ������ (sizes_childrens)
public:
	
	int get_amount_cliques();						// �������� ������� ��� (������ � ���������)
	vector<int> get_clique(int number);				// �������� ���� � ������� number
	int get_size_clique(int number);				// �������� ����� ����(������� ������) � ������� number



};

