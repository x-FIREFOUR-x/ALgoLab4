#include "Algorithm.h"
#include <numeric>

void Algorithm::genetic_algo(Graph& graph, int& count_iter)
{
	if (count_iter == 0)
	{
		start_cliques(graph);
		count_iter++;
	}
	else
	{
		count_iter++;
		sort_cliques();
	}
	
}

void Algorithm::start_cliques(Graph& graph)
{
	for (int i = 0; i < graph.get_size(); i++)
	{
		vector<int> buf(graph.get_size(), 0);
		buf[i] = 1;
		sizes_cliques.push_back(1);
		cliques.push_back(buf);
	}
}

bool Algorithm::is_clique(Graph& graph, vector<int> clq)
{
	bool is_clq = true;
	vector<int> vertices;

	for (int  i = 0; i < clq.size(); i++)
	{
		if (clq[i] == 1)
		{
			vertices.push_back(i);
		}
	}

	for (int i = 0; i < vertices.size() && is_clq; i++)
	{
		for (int j = 0; j < vertices.size() && is_clq; j++)
		{
			if (vertices[i] != vertices[j])
			{
				int edje = graph.get_element(vertices[i], vertices[j]);
					if (edje != 1)
					{
						is_clq = false;
					}
			}
		}
	}

	return is_clq;
}

void Algorithm::sort_cliques()
{
	vector<int> indexs(cliques.size());
	iota(indexs.begin(), indexs.end(), 0);

	sort(indexs.begin(), indexs.end(), [&](int a, int b) {return sizes_cliques[a] > sizes_cliques[b]; });

	vector<vector<int>> buf = move(cliques);
	cliques.resize(buf.size());
	for (int i = 0; i < buf.size(); i++)
	{
		cliques[i] = move(buf[indexs[i]]);
	}
	sort(sizes_cliques.begin(), sizes_cliques.end(), [](int a, int b) { return a > b ; });
}

int Algorithm::get_amount_cliques()
{
	return cliques.size();
}

vector<int> Algorithm::get_clique(int number)
{
	return cliques[number];
}

int Algorithm::get_size_clique(int number)
{
	return sizes_cliques[number];
}
