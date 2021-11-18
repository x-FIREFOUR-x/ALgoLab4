#include "Graph.h"
#include <algorithm>
#include <iostream>
Graph::Graph()
{
}

Graph::Graph(int in_size)
{
	size = in_size;
	matrix_graph = new int* [size];
	for (int i = 0; i < size; i++)
	{
		matrix_graph[i] = new int[size];
	}
}

Graph::Graph(const Graph& obj)
{
	size = obj.size;
	matrix_graph = new int* [size];
	for (int i = 0; i < size; i++)
	{
		matrix_graph[i] = new int[size];
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix_graph[i][j] = obj.matrix_graph[i][j];
		}

	}
}

Graph::~Graph()
{
	for (int i = 0; i < size; i++)
	{
		delete[] matrix_graph[i];
	}
	delete[] matrix_graph;
}


void Graph::set_element(int row, int column, int elem)
{
	matrix_graph[row][column] = elem;
}

int Graph::get_element(int row, int column)
{
	return matrix_graph[row][column];
}

void Graph::set_size(int insize)
{
	size = insize;
}

int Graph::get_size()
{
	return size;
}

int Graph::count_edge(int number_node)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		count += matrix_graph[number_node][i];

	}
	return count;
}

bool Graph::generation(int min_adj_edge, int max_adj_edge)
{
	if (min_adj_edge <= max_adj_edge && max_adj_edge <= size && min_adj_edge >= 0)
	{
		for (int i = 0; i < size; i++)				// обнуляєм матрицю
		{
			for (int j = 0; j < size; j++)
			{
				matrix_graph[i][j] = 0;

			}
		}

		vector<vector<int>> num_edge;			// вектор меж кількості дуг для кроку ітерації 
		num_edge.push_back(vector<int>());
		num_edge.push_back(vector<int>());
		for (int i = 0; i < size; i++)			// початкові межі
		{
			num_edge[0].push_back(min_adj_edge);
			num_edge[1].push_back(max_adj_edge);
		}

		for (int i = 0; i < size - 1; i++)		// визначення дуг в i тому рядку і стовпці			
		{
			vector<int> ver;					// вершини з якими i - вершина може бути з'єднана на цій ітерації (далі вона не буде приєднанана до жодної до цього до неї могли бути приєднані)
			for (int j = i + 1; j < size; j++)	// кладемо всі вершини що слідують після i
			{
				ver.push_back(j);
			}
			random_shuffle(ver.begin(), ver.end());		// тасуєм ці вершини в рандомному порядку

			int count_edge;					// число дуг отворених на цій ітерації
			max_adj_edge = num_edge[1][i];
			min_adj_edge = num_edge[0][i];

			// підбір числа дуг в залежності від уже згенерованих дуг (перевіряєм нові межі) і залишившихся вершин
			if (max_adj_edge == 0)
			{
				count_edge = 0;
			}
			else
				if (min_adj_edge == size - i - 1)
				{
					count_edge = min_adj_edge;
				}
				else
					if (max_adj_edge > size - i - 1)
					{
						count_edge = rand() % (size - i - 1 - min_adj_edge + 1) + min_adj_edge;
					}
					else
						if (max_adj_edge <= size - i - 1)
						{
							count_edge = rand() % (max_adj_edge - min_adj_edge + 1) + min_adj_edge;
						}



			for (int j = 0; j < count_edge; j++)     // проходи по ver і створюєм дуги від вершин і до ver[j] перших  count_edge вершин в var
			{
				matrix_graph[i][ver[j]] = 1;
				matrix_graph[ver[j]][i] = 1;

				if (num_edge[0][ver[j]] != 0)			// якщо вершина ver[j] добавлена то зменшуєм її межі дуг для ітерації на цій вершині 
					num_edge[0][ver[j]]--;
				if (num_edge[1][ver[j]] != 0)
					num_edge[1][ver[j]]--;
			}

		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Graph::check_correct_symetric()
{
	bool is_correct = true;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j && matrix_graph[i][j] != 0)
			{
				is_correct = false;
			}
			else
			{
				if (matrix_graph[i][j] != matrix_graph[j][i])
				{
					is_correct = false;
				}
			}
		}

	}
	return is_correct;
}

bool Graph::check_correct_num_edge(int min_adj_edge, int max_adj_edge)
{
	bool is_correct = true;
	int num;
	for (int i = 0; i < size; i++)
	{
		num = count_edge(i);
		if (num > max_adj_edge || num < min_adj_edge)
			is_correct = false;
	}
	return  is_correct;
}

int Graph::count_avarege_edge()
{
	int avarege = 0;

	for (int i = 0; i < size; i++)
	{
		avarege += count_edge(i);
	}
	avarege = avarege / size;

	return avarege;
}

