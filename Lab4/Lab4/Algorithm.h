#pragma once
#include "Graph.h"
#include <vector>
#include<algorithm>
using namespace std;
class Algorithm
{
private:
	vector<vector<int>> cliques;			// ������ ��� � ��������� (���� ������� ������ � 1(� �������) � 0(���� �������)) 
	vector<int> sizes_cliques;				// ������ ������ ��� (������� 1 � �����)
public:
	void genetic_algo(Graph& graph, int& count_iter);				// ���������� �������� ��� ������ ����

private:
	void start_cliques(Graph& graph);				// ������� �������� ���� (�������� ���������) �� ������ ���� � ������� 1
	bool is_clique(Graph& graph, vector<int> clq);
	void sort_cliques();

public:
	
	int get_amount_cliques();						// �������� ������� ��� (������ � ���������)
	vector<int> get_clique(int number);				// �������� ���� � ������� number
	int get_size_clique(int number);				// �������� ����� ����(������� ������) � ������� number



};

