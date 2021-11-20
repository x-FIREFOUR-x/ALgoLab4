#include "Algorithm.h"
#include <numeric>

void Algorithm::genetic_algo(Graph& graph, int& count_iter, int num_crossing, int num_mutation, int num_local_up)
{
	if (count_iter == 0)
	{
		start_cliques(graph);
		count_iter++;
	}
	else
	{
		int parent1 = 0;
		int parent2 = rand() % (cliques.size() - 1) + 1;

		pair<vector<int>, int> child;
		switch (num_crossing)
		{
			case 1:
				child = crossing_one_point(graph, parent1, parent2);
				break;
			case 2:

				break;
			case 3:

				break;
		}

		if (!child.first.empty())
		{
			int mut_will = rand() % 100;
			if (mut_will < chance_mutation)
			{
				switch (num_mutation)
				{
				case 0:
					break;
				case 1:
					mutation1(graph, child);
					break;
				case 2:
					mutation2(graph, child);
					break;
				case 3:
					mutation3(graph, child);
					break;
				}
				
			}

			switch (num_local_up)
			{
			case 0:
				break;
			case 1:
				local_upgrade1(graph, child);
				break;
			case 2:
				
				break;
			}

			if (sizes_cliques[sizes_cliques.size() - 1] < child.second)
			{
				cliques[cliques.size() - 1] = child.first;
				sizes_cliques[sizes_cliques.size() - 1] = child.second;
			}

			sort_cliques();
		}

		count_iter++;
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

pair<vector<int>,int> Algorithm::crossing_one_point(Graph& graph, int pr1, int pr2)
{
	int n_lines = 1 + 1;     // одноточковий дає два відрізка 
	int n_pr = 2;			//кількість батьків

	vector<int> pr;			// індикси батьків
	pr.push_back(pr1);
	pr.push_back(pr2);

	int point = rand() % (graph.get_size()+1);
	

	vector<int>points;						// точки поділу відрізка (begin, point, end) 
	points.push_back(0);
	points.push_back(point);
	points.push_back(graph.get_size());

	vector<vector<int>> childrens;			// нащадки
	vector<int> sizes_childrens;

	for (int i = 0; i < n_pr; i++)      // батько першого відрізка
	{
		for (int j = 0; j < n_pr; j++)			// батько другого выдрызка
		{
			if (i != j)
			{	
				vector<int> numb_parentr;						// номери батьків (0 або 1) в pr з яких буде братися k-ий відрізок
				numb_parentr.push_back(i);
				numb_parentr.push_back(j);

				vector<int> child;
				for (int k = 0; k < n_lines; k++)		// номер відрізка
				{
					int in_parent = pr[numb_parentr[k]];		// індекс батька
					vector<int> line;				// вирізаєм k-ий відрізок в першого чи другого батька

					auto it_l1_begin = line.begin();
					auto it_pr_begin = cliques[in_parent].begin() + points[k];
					auto it_pr_p = cliques[in_parent].begin() + points[k+1];
					line.insert(it_l1_begin, it_pr_begin, it_pr_p);

					child.insert(child.end(), line.begin(), line.end());	//вставляєм відрізок k-ий в сина
				}

				int amount_ver = calculate_size_clique(child);
				if (is_clique(graph, child) && amount_ver > 0)		// перевіряєм чи син є клікою
				{
					childrens.push_back(child);
					sizes_childrens.push_back(amount_ver);
				}
			}
		}
	}

	if (sizes_childrens.size() > 0)
	{
		int index = search_best_child(graph, sizes_childrens);
		pair<vector<int>, int> best_child(childrens[index], sizes_childrens[index]);
		return best_child;
	}
	{
		pair<vector<int>, int> best_child;
		return best_child;
	}
	
}

bool Algorithm::mutation1(Graph& graph, pair<vector<int>, int>& child)
{
	bool success_mutation = true;

	vector<int> mutat_child = child.first;
	int size_mutat_child = child.second;

	int gene1 = rand() % graph.get_size();
	int gene2 = rand() % graph.get_size();

	int buf = mutat_child[gene1];
	mutat_child[gene1] = mutat_child[gene2];
	mutat_child[gene2] = buf;

	success_mutation = is_clique(graph, mutat_child);
	
	if (success_mutation)
	{
		child.first = mutat_child;
		child.second = size_mutat_child;
	}

	return success_mutation;
}

bool Algorithm::mutation2(Graph& graph, pair<vector<int>, int>& child)
{
	bool success_mutation = true;

	vector<int> mutat_child = child.first;
	int size_mutat_child = child.second;

	int in_gene = rand() % graph.get_size();
		
	if (mutat_child[in_gene] == 0)
	{
		mutat_child[in_gene] = 1;
		size_mutat_child++;
	}
	else
	{
		mutat_child[in_gene] = 0;
		size_mutat_child--;
	}
	success_mutation = is_clique(graph, mutat_child);

	if (success_mutation)
	{
		child.first = mutat_child;
		child.second = size_mutat_child;
	}

	return success_mutation;
}

bool Algorithm::mutation3(Graph& graph, pair<vector<int>, int>& child)
{
	bool success_mutation = true;
	int chanse_inv_gene = 20;
	vector<int> mutat_child = child.first;
	int size_mutat_child = child.second;

	for (int i = 0; i < graph.get_size(); i++)
	{
		int will_inv_gene = rand() % 100;
		if (will_inv_gene < chanse_inv_gene)
		{
			if (mutat_child[i] == 0)
			{
				mutat_child[i] = 1;
				size_mutat_child++;
			}
			else
			{
				mutat_child[i] = 0;
				size_mutat_child--;
			}
		}
		
	}
	
	success_mutation = is_clique(graph, mutat_child);

	if (success_mutation)
	{
		child.first = mutat_child;
		child.second = size_mutat_child;
	}

	return success_mutation;
}

bool Algorithm::local_upgrade1(Graph& graph, pair<vector<int>, int>& child)
{
	bool success_local_up = true;

	vector<int> up_child = child.first;
	int size_up_child = child.second;

	vector<int> index_0_genes;
	for (int i = 0; i < up_child.size(); i++)
	{
		if (up_child[i] == 0)
			index_0_genes.push_back(i);
	}

	if (!index_0_genes.empty())
	{
		int rand_0_gene = rand() % index_0_genes.size();
		int in_gene = index_0_genes[rand_0_gene];

		up_child[in_gene] = 1;
		size_up_child++;

		success_local_up = is_clique(graph, up_child);
	}
	else
	{
		success_local_up = false;
	}

	if (success_local_up)
	{
		child.first = up_child;
		child.second = size_up_child;
	}

	return success_local_up;
}

int Algorithm::calculate_size_clique(vector<int>& clq)
{
	int s = 0;
	for (int i = 0; i < clq.size(); i++)
	{
		s += clq[i];
	}
	return s;
}

int Algorithm::search_best_child(Graph& graph,vector<int>& sizes_childrens)
{
	int min = graph.get_size() + 1;
	int index;
	for (int i = 0; i < sizes_childrens.size(); i++)
	{
		if (min > sizes_childrens[i])
		{
			min = sizes_childrens[i];
			index = i;
		}
	}
	return index;
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
