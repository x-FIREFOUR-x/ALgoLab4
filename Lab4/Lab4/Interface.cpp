#include "Interface.h"


void Interface::console_interface()
{

	int how;
	cout << "Input(1- read graph file, 2 - random graph): ";
	cin >> how;

	string name;
	cout << "Input name file: ";
	cin >> name;
	name = "file\\" + name;
	FileWorker file(name);


	if (how == 1)
	{
		Graph graph = file.read_graph();
		int amount_iter;
		int step;
		cout << "Input amount iteration: ";
		cin >> amount_iter;
		cout << "Input step iteration: ";
		cin >> step;

		write_graph(graph);
		
		Algorithm algo;
		int count_iter = 0;

		while (count_iter - 1 != amount_iter)
		{
			algo.genetic_algo(graph, count_iter);

			if (((count_iter - 1) % step) == 0)
			{
				cout << "_____________________________________________" << endl;
				cout << "Iteration¹ " << count_iter - 1 << endl;
				write_cliques(algo);
				
				cout << "----------------------------------------------" << endl;
			}
		}
	}
	else
	{
		int size;
		int min_adj;
		int max_adj;
		cout << "Input size graph: ";
		cin >> size;
		cout << "Input min count edje vertises's: ";
		cin >> min_adj;
		cout << "Input max count edje vertises's: ";
		cin >> max_adj;


		Graph graph(size);
		graph.generation(min_adj, max_adj);



		int amount_iter;
		int step;
		cout << "Input amount iteration: ";
		cin >> amount_iter;
		cout << "Input step iteration: ";
		cin >> step;

		write_graph(graph);

		Algorithm algo;
		int count_iter = 0;

		while (count_iter - 1 != amount_iter)
		{
			algo.genetic_algo(graph, count_iter);

			if (((count_iter - 1) % step) == 0)
			{
				cout << "_____________________________________________" << endl;
				cout << "Iteration# " << count_iter - 1 << endl;
				write_cliques(algo);

				cout << "----------------------------------------------" << endl;
			}
		}
		
		file.write_graph(graph);
	}


}

void Interface::write_graph(Graph graph)
{
	cout << graph.get_size() << endl;
	for (int i = 0; i < graph.get_size(); i++)
	{
		for (int j = 0; j < graph.get_size(); j++)
		{
			cout << graph.get_element(i, j) << " ";
		}
		cout << endl;
	}
}

void Interface::write_cliques(Algorithm algo)
{
	cout << "Cliques:" << endl;
	vector<int> clq;
	int count_ver;
	for (int i = 0; i < algo.get_amount_cliques(); i++)
	{
		clq = algo.get_clique(i);
		count_ver = algo.get_size_clique(i);
		for (int j = 0; j < clq.size(); j++)
		{
			cout << clq[j] << " ";
		}
		cout << " (" << count_ver << ")";
		cout << endl;
	}
}



