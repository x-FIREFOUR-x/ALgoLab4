#include "Algorithm.h"
#include <numeric>

void Algorithm::genetic_algo(Graph& graph, int& count_iter, int num_crossing, int num_mutation, int num_local_up)
{
	if (count_iter == 0)
	{
		//start_cliques(graph);
		start_rand_n_cliques(graph);
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
				child = crossing_two_point(graph, parent1, parent2);
				break;
			case 3:
				child = uniform_crossing(graph, parent1, parent2);
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
				local_upgrade2(graph, child);
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

void Algorithm::start_rand_n_cliques(Graph& graph)
{
	vector<int> index_ver;
	for (int i = 0; i < graph.get_size(); i++)
	{
		index_ver.push_back(i);
	}
	random_shuffle(index_ver.begin(), index_ver.end());

	for (int i = 0; i < n_start_cliques && i < graph.get_size(); i++)
	{
		vector<int> buf(graph.get_size(), 0);
		buf[index_ver[i]] = 1;
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
	int n_lines = 1 + 1;     // ???????????? ??? ??? ???????? 
	int n_pr = 2;			//????????? ???????

	vector<int> pr;			// ??????? ???????
	pr.push_back(pr1);
	pr.push_back(pr2);

	int point = rand() % (graph.get_size()+1);
	

	vector<int>points;						// ????? ?????? ???????? (begin, point, end) 
	points.push_back(0);
	points.push_back(point);
	points.push_back(graph.get_size());

	vector<vector<int>> childrens;			// ???????
	vector<int> sizes_childrens;

	for (int i = 0; i < n_pr; i++)      // ?????? ??????? ????????
	{
		for (int j = 0; j < n_pr; j++)			// ?????? ??????? ????????
		{
			if (i != j)
			{	
				vector<int> numb_parentr;						// ?????? ??????? (0 ??? 1) ? pr ? ???? ???? ??????? k-?? ????????
				numb_parentr.push_back(i);
				numb_parentr.push_back(j);

				vector<int> child;
				for (int k = 0; k < n_lines; k++)		// ????? ????????
				{
					int in_parent = pr[numb_parentr[k]];		// ?????? ??????
					vector<int> line;				// ???????? k-?? ???????? ? ??????? ?? ??????? ??????

					auto it_l1_begin = line.begin();
					auto it_pr_begin = cliques[in_parent].begin() + points[k];
					auto it_pr_p = cliques[in_parent].begin() + points[k+1];
					line.insert(it_l1_begin, it_pr_begin, it_pr_p);

					child.insert(child.end(), line.begin(), line.end());	//????????? ???????? k-?? ? ????
				}

				int amount_ver = calculate_size_clique(child);
				if (is_clique(graph, child) && amount_ver > 0)		// ?????????? ?? ??? ? ??????
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

pair<vector<int>, int> Algorithm::crossing_two_point(Graph& graph, int pr1, int pr2)
{
	int n_lines = 2 + 1;     // ??????????? ??? ??? ???????? 
	int n_pr = 2;			//????????? ???????

	vector<int> pr;			// ??????? ???????
	pr.push_back(pr1);
	pr.push_back(pr2);

	int point = rand() % (graph.get_size() + 1);
	int point1;
	int point2 = -1;
	while (point2 == -1)
	{
		point1 = rand() % (graph.get_size() + 1);
		if (point > point1)
		{
			point2 = point;
		}
		else
			if (point < point1)
			{
				point2 = point1;
				point1 = point;
			}
	}

	vector<int>points;						// ????? ?????? ???????? (begin, point, end) 
	points.push_back(0);
	points.push_back(point1);
	points.push_back(point2);
	points.push_back(graph.get_size());

	vector<vector<int>> childrens;			// ???????
	vector<int> sizes_childrens;

	for (int i = 0; i < n_pr; i++)      // ?????? ??????? ????????
	{
		for (int j = 0; j < n_pr; j++)			// ?????? ??????? ????????
		{
			for (int t = 0; t < n_pr; t++)
			{
				if (i != j || i != t)
				{
					vector<int> numb_parentr;						// ?????? ??????? (0 ??? 1) ? pr ? ???? ???? ??????? k-?? ????????
					numb_parentr.push_back(i);
					numb_parentr.push_back(j);
					numb_parentr.push_back(t);

					vector<int> child;
					for (int k = 0; k < n_lines; k++)		// ????? ????????
					{
						int in_parent = pr[numb_parentr[k]];		// ?????? ??????
						vector<int> line;				// ???????? k-?? ???????? ? ??????? ?? ??????? ??????

						auto it_l1_begin = line.begin();
						auto it_pr_begin = cliques[in_parent].begin() + points[k];
						auto it_pr_p = cliques[in_parent].begin() + points[k + 1];
						line.insert(it_l1_begin, it_pr_begin, it_pr_p);

						child.insert(child.end(), line.begin(), line.end());	//????????? ???????? k-?? ? ????
					}

					int amount_ver = calculate_size_clique(child);
					if (is_clique(graph, child) && amount_ver > 0)		// ?????????? ?? ??? ? ??????
					{
						childrens.push_back(child);
						sizes_childrens.push_back(amount_ver);
					}
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

pair<vector<int>, int> Algorithm::uniform_crossing(Graph& graph, int pr1, int pr2)
{
	vector<int> pr;			// ??????? ???????
	pr.push_back(pr1);
	pr.push_back(pr2);

	vector<vector<int>> childs;
	vector<int> sizes_childs;
	

	for (int k = 0; k < 10; k++)
	{
		vector<int> child;
		for (int i = 0; i < graph.get_size(); i++)
		{
			int n_parent = rand() % 2;

			int gene = cliques[pr[n_parent]][i];
			child.push_back(gene);
		}
		if (is_clique(graph, child))
		{
			int size = calculate_size_clique(child);
			childs.push_back(child);
			sizes_childs.push_back(size);
		}
	}
	
	if (!childs.empty())
	{
		int index = search_best_child(graph, sizes_childs);
		return  pair<vector<int>, int>(childs[index], sizes_childs[index]);
	}
	else
	{
		return pair<vector<int>, int>();
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

bool Algorithm::local_upgrade2(Graph& graph, pair<vector<int>, int>& child)
{
	bool success_local_up = true;

	vector<int> up_child = child.first;
	int size_up_child = child.second;

	vector<int> index_1_genes;
	for (int i = 0; i < up_child.size(); i++)
	{
		if (up_child[i] == 1)
			index_1_genes.push_back(i);
	}

	if (!index_1_genes.empty())
	{
		int rand_0_gene = rand() % index_1_genes.size();
		int in_gene = index_1_genes[rand_0_gene];

		int in_gene_adj = rand() % graph.get_size();
		while (graph.get_element(in_gene, in_gene_adj) == 0 || up_child[in_gene_adj] == 1)
		{
			in_gene_adj = rand() % graph.get_size();
		}

		up_child[in_gene_adj] = 1;
		size_up_child++;

		success_local_up = is_clique(graph, up_child);
	}
	else
	{
		success_local_up = false;
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
	int max = 0;
	int index;
	for (int i = 0; i < sizes_childrens.size(); i++)
	{
		if (max < sizes_childrens[i])
		{
			max = sizes_childrens[i];
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
